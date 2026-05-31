#include <vector>
#include <thread>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

struct Data_struct {
    int outcome;
    vector<double> x;
};

int d = 5;   // number of families
int p = 3;   // number of features per family

// takes one family and adds its part to gradient and hessian
void add_one_family(const Data_struct& fam, const vector<double>& theta,
                    vector<double>& gradient, vector<double>& H) {
    int P = p * (d - 1);

    vector<double> score(d, 0.0);
    double denom = 1.0;
    for (int j = 0; j < d - 1; j++) {
        for (int k = 0; k < p; k++) {
            score[j] = score[j] + fam.x[k] * theta[j * p + k];
        }
        denom = denom + exp(score[j]);
    }

    // probabilities for every group for hessian
    vector<double> prob(d, 0.0);
    for (int j = 0; j < d - 1; j++) {
        prob[j] = exp(score[j]) / denom;
    }
    prob[d - 1] = 1.0 / denom;

    // gradient
    for (int j = 0; j < d - 1; j++) {
        double indicator = 0.0;
        if (j == fam.outcome) {
            indicator = 1.0;
        }
        for (int k = 0; k < p; k++) {
            gradient[j * p + k] = gradient[j * p + k] + fam.x[k] * (indicator - prob[j]);
        }
    }

    // hessian
    for (int j = 0; j < d - 1; j++) {
        for (int l = 0; l < d - 1; l++) {
            double scal = 0.0;
            if (j == l) {
                scal = prob[j] * (1.0 - prob[j]);
            } else {
                scal = -prob[j] * prob[l];
            }
            for (int k1 = 0; k1 < p; k1++) {
                for (int k2 = 0; k2 < p; k2++) {
                    int row = j * p + k1;
                    int col = l * p + k2;
                    H[row * P + col] = H[row * P + col] + scal * fam.x[k1] * fam.x[k2];
                }
            }
        }
    }
}

// one core does all families
void compute_sequential(const vector<Data_struct>& data, const vector<double>& theta,
                        vector<double>& gradient, vector<double>& H) {
    int N = data.size();
    for (int i = 0; i < N; i++) {
        add_one_family(data[i], theta, gradient, H);
    }
}

// each worker does its part of families from start to end
void worker(const vector<Data_struct>& data, const vector<double>& theta,
            int start, int end, vector<double>& my_gradient, vector<double>& my_H) {
    for (int i = start; i < end; i++) {
        add_one_family(data[i], theta, my_gradient, my_H);
    }
}

// split families between T threads, then add up their gradients and hessians
void compute_parallel(const vector<Data_struct>& data, const vector<double>& theta, int T,
                      vector<double>& gradient, vector<double>& H) {
    int N = data.size();
    int P = p * (d - 1);

    // one gradient and one hessian for each thread, all start at zero
    vector<vector<double>> partial_grad(T);
    vector<vector<double>> partial_H(T);
    for (int t = 0; t < T; t++) {
        partial_grad[t].resize(P, 0.0);
        partial_H[t].resize(P * P, 0.0);
    }

    // start the threads
    vector<thread> threads;
    for (int t = 0; t < T; t++) {
        int start = t * N / T;
        int end = (t + 1) * N / T;
        threads.push_back(thread(worker, cref(data), cref(theta), start, end,
                                 ref(partial_grad[t]), ref(partial_H[t])));
    }

    // wait for all threads to finish
    for (int t = 0; t < T; t++) {
        threads[t].join();
    }

    // add all the partial gradients into one
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < P; k++) {
            gradient[k] = gradient[k] + partial_grad[t][k];
        }
    }
    // add all the partial hessians into one
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < P * P; k++) {
            H[k] = H[k] + partial_H[t][k];
        }
    }
}

int main() {
    int N = 1000000;   // a lot of families so the threads have work to do
    int P = p * (d - 1);

    // make random families
    vector<Data_struct> data(N);
    for (int i = 0; i < N; i++) {
        data[i].outcome = rand() % d;
        data[i].x.resize(p);
        for (int k = 0; k < p - 1; k++) {
            data[i].x[k] = (rand() % 2000 - 1000) / 1000.0;
        }
        data[i].x[p - 1] = 1.0;
    }

    vector<double> theta(P, 0.0);

    // sequential, timed
    vector<double> g_seq(P, 0.0);
    vector<double> H_seq(P * P, 0.0);
    auto t0 = chrono::steady_clock::now();
    compute_sequential(data, theta, g_seq, H_seq);
    auto t1 = chrono::steady_clock::now();
    double seq_time = chrono::duration<double>(t1 - t0).count();
    cout << "sequential: " << seq_time << " s" << endl;

    // parallel for 1, 2, 3, 4 threads
    for (int T = 1; T <= 4; T++) {
        vector<double> g_par(P, 0.0);
        vector<double> H_par(P * P, 0.0);

        auto a = chrono::steady_clock::now();
        compute_parallel(data, theta, T, g_par, H_par);
        auto b = chrono::steady_clock::now();
        double par_time = chrono::duration<double>(b - a).count();

        // biggest difference in the gradient
        double diff_g = 0.0;
        for (int k = 0; k < P; k++) {
            double diff = fabs(g_seq[k] - g_par[k]);
            if (diff > diff_g) {
                diff_g = diff;
            }
        }

        // biggest difference in the hessian
        double diff_H = 0.0;
        for (int k = 0; k < P * P; k++) {
            double diff = fabs(H_seq[k] - H_par[k]);
            if (diff > diff_H) {
                diff_H = diff;
            }
        }

        // how big are the hessian numbers themselves
        double biggest_H = 0.0;
        for (int k = 0; k < P * P; k++) {
            if (fabs(H_seq[k]) > biggest_H) {
                biggest_H = fabs(H_seq[k]);
            }
        }

        cout << T << " threads: " << par_time << " s";
        cout << " speedup: " << seq_time / par_time;

        if (diff_g < 1e-6 && diff_H < biggest_H * 1e-8) {
            cout << " match: YES" << endl;
        } else {
            cout << " match: NO" << endl;
        }
    }
    return 0;
}