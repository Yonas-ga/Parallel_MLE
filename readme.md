# Parallelized Maximum Likelyhood Estimation

This project is an attempt to recreate the paper by C.A.SWANN, in which he parallelized each step of the Gradient Ascent when solving the MLE for multinomial logistic regression. 

To do so we implemented Gradient Ascent and Gradient Ascent using Newton's method sequentially, and then we parallelized it using multithreading and GPU parallelization.

## Software

- NVIDIA GPU
- Pandas and scikit python libraries

# Project Structure
```
Project/
├── main.cpp
├── data.hpp
├── parse_CSV.cpp
├── Sequential/
│   ├── GA_seq.cpp
│   └── newton_seq.cpp
├── parallel/
│ ├── GA_cpu_cv.cpp
│ ├── newton_cpu_cv.cpp
│ ├── GA_cpu_lazy.cu
│ ├── newton_cpu_lazy.cpp
│ ├── GA_gpu.cu
│ └── newton_gpu.cu
├── Data/
├── Plots/
├── Figure/
└── README.md
```

Main.cpp contains many different functions to test and use all the MLE implementations.

By changing the calls inside of the "main" function, one can execute any of these function using:

```/usr/local/cuda/bin/nvcc -arch=sm_60 main.cpp parse_CSV.cpp parallel/GA_cpu_lazy.cpp parallel/newton_cpu_lazy.cpp Sequential/GA_seq.cpp Sequential/newton_seq.cpp parallel/GA_gpu.cu parallel/newton_gpu.cu parallel/GA_cpu_cv.cpp parallel/newton_cpu_cv.cpp -o test```

You can change "/usr/local/cuda/bin/nvcc" to the location of your nvcc compiler.

To compile, and then 

```./test```

To execute.

If executing the ```loan()``` function, you will need to run the executable as follows: ```./test | tee smth.txt```.

# Recreate paper

When trying to recreate the paper, we gathered the data in the folder Data/

This Stata data was then parsed using "parse_stata_to_CSV.py" changing every occurance of "19.." to the years we had available. (ran using: ```$ python3 parse_stata_to_CSV.py```)

With this data preprocessing done, we can now recreate the results of the paper using "recreate_paper()" in main.cpp.

# Other real data

We also implemented the MLE of another real data set.

We do the data preprocessing by running $ python3 preprocess_loan.py

We then compile using:
```
nvcc -std=c++17 -O2 -arch=native \
  -I$CUDA_HOME/targets/x86_64-linux/include \
  -L$CUDA_HOME/targets/x86_64-linux/lib \
  main.cpp parse_CSV.cpp \
  Sequential/newton_seq.cpp Sequential/GA_seq.cpp \
  parallel/newton_cpu_lazy.cpp parallel/newton_cpu_cv.cpp \
  parallel/GA_cpu_lazy.cpp parallel/GA_cpu_cv.cpp \
  parallel/newton_gpu.cu parallel/GA_gpu.cu \
  -o loan_cuda
```

And then output using 
```'
$ ./loan_cuda | tee loan_full_test_output.txt
```

