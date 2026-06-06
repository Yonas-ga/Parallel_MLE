"""
plot_mle.py  –  Publication-quality figures for the Parallel MLE report.

Usage
-----
    python plot_mle.py --seq sequential_results.csv --par "Parralel results.csv"

Both flags are optional.  All figures saved as 300 dpi PDFs in ./plots/.

CSV schemas
-----------
Sequential : N, p, d, runtime_h_us, runtime_g_us,
             mean_error_h, max_error_h, mean_error_g, max_error_g,
             mean_error_h_g, converged_h, converged_g

Parallel   : N, T, p, d, runtime_h_us, runtime_g_us,
             mean_error_h, max_error_h, mean_error_g, max_error_g,
             mean_error_h_g, converged_h, converged_g
"""

import argparse
import os
import warnings

import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
import pandas as pd
from scipy import stats

warnings.filterwarnings("ignore")
os.makedirs("plots", exist_ok=True)

# ══════════════════════════════════════════════════════════════════════════════
#  GLOBAL STYLE
# ══════════════════════════════════════════════════════════════════════════════
mpl.rcParams.update({
    "font.family":           "serif",
    "font.serif":            ["Computer Modern Roman", "DejaVu Serif"],
    "font.size":             11,
    "axes.titlesize":        12,
    "axes.labelsize":        11,
    "xtick.labelsize":       10,
    "ytick.labelsize":       10,
    "legend.fontsize":       9.5,
    "legend.title_fontsize": 9.5,
    "lines.linewidth":       1.6,
    "lines.markersize":      5,
    "axes.spines.top":       False,
    "axes.spines.right":     False,
    "axes.grid":             True,
    "grid.alpha":            0.35,
    "grid.linestyle":        "--",
    "grid.linewidth":        0.6,
    "figure.dpi":            150,
    "savefig.dpi":           300,
    "savefig.bbox":          "tight",
    "savefig.pad_inches":    0.05,
    "text.usetex":           False,
})

NEWTON_COLOR = "#2166ac"
GRAD_COLOR   = "#d6604d"
AGREE_COLOR  = "#555555"
PALETTE      = ["#2166ac", "#d6604d", "#4dac26", "#762a83",
                "#f1a340", "#1b7837", "#e08214", "#5aae61"]
MARKERS      = ["o", "s", "^", "D", "v", "P", "X", "h"]
NEWTON_LABEL = "Newton's method"
GRAD_LABEL   = "Gradient ascent"


# ══════════════════════════════════════════════════════════════════════════════
#  HELPERS
# ══════════════════════════════════════════════════════════════════════════════

def load(path):
    df = pd.read_csv(path, skipinitialspace=True)
    df.columns = df.columns.str.strip()
    return df


def savefig(name):
    path = os.path.join("plots", name)
    plt.savefig(path)
    print(f"  saved  {path}")


# ── Axis helpers ──────────────────────────────────────────────────────────────

def set_N_axis(ax, N_values):
    """
    Evenly-spaced N-axis ticks with a shared multiplier suffix on the label.

    Let matplotlib choose ~6 tick positions automatically (equal spacing),
    then relabel them as divided integers so numbers stay small.
    """
    N_arr = np.sort(np.unique(N_values))

    # Largest power-of-10 divisor such that the smallest value >= 1 after division
    for div in [1_000_000, 100_000, 10_000, 1_000, 100, 10, 1]:
        if N_arr.min() / div >= 1:
            break

    suffix = {1: "", 10: " (×10)", 100: " (×100)",
              1_000: " (×10³)", 10_000: " (×10⁴)",
              100_000: " (×10⁵)", 1_000_000: " (×10⁶)"}.get(div, f" (×{div})")

    # Automatic evenly-spaced ticks; formatter just divides the raw tick value
    ax.xaxis.set_major_locator(ticker.MaxNLocator(nbins=6, integer=False))
    ax.xaxis.set_major_formatter(
        ticker.FuncFormatter(lambda x, _: f"{int(round(x / div))}")
    )
    ax.set_xlabel(ax.get_xlabel() + suffix)


def shared_ylim(axes_list, pad=0.05):
    """Force identical y-limits across a list of Axes."""
    lo = min(ax.get_ylim()[0] for ax in axes_list)
    hi = max(ax.get_ylim()[1] for ax in axes_list)
    span = hi - lo
    for ax in axes_list:
        ax.set_ylim(lo - pad * span, hi + pad * span)


# ══════════════════════════════════════════════════════════════════════════════
#  SCALE REGISTRY
#  Collected after both sequential and parallel figures are drawn so that
#  paired figures (seq vs par) can share the same y-axis scale.
# ══════════════════════════════════════════════════════════════════════════════
_scale_registry = {}   # key → list of (fig, ax) pairs

def _register(key, fig, ax):
    _scale_registry.setdefault(key, []).append((fig, ax))

def apply_shared_scales():
    """
    After all figures are drawn, re-open each registered group,
    set shared y-limits, and re-save.
    """
    for key, entries in _scale_registry.items():
        lo = min(ax.get_ylim()[0] for _, ax in entries)
        hi = max(ax.get_ylim()[1] for _, ax in entries)
        span = hi - lo
        pad  = 0.05 * span
        for fig, ax in entries:
            ax.set_ylim(lo - pad, hi + pad)
            # Redraw and save (fig has the filename stored as fig._save_name)
            fig.tight_layout()
            path = os.path.join("plots", fig._save_name)
            fig.savefig(path, dpi=300, bbox_inches="tight")
            print(f"  re-saved (shared scale) {path}")
        plt.close("all")


def make_fig(save_name, scale_key=None, figsize=(5.2, 3.8)):
    """Create a figure and register it for shared-scale post-processing."""
    fig, ax = plt.subplots(figsize=figsize)
    fig._save_name = save_name
    if scale_key:
        _register(scale_key, fig, ax)
    return fig, ax


# ══════════════════════════════════════════════════════════════════════════════
#  SEQUENTIAL FIGURES
# ══════════════════════════════════════════════════════════════════════════════

def figures_sequential(seq):
    print("\n── Sequential figures ──")

    p_val = seq["p"].mode()[0]
    d_val = 2 if 2 in seq["d"].values else seq["d"].mode()[0]
    sub_N = seq[(seq["p"] == p_val) & (seq["d"] == d_val)].copy()
    sub_N.sort_values("N", inplace=True)
    P_label = f"$p={p_val},\\ d={d_val}$"
    n_ref   = sub_N["N"].values.astype(float)

    # ── 1.  MAE vs N (seq) ────────────────────────────────────────────────────
    fig, ax = make_fig("MAE_wrt_N_seq.pdf", scale_key="MAE_vs_N")
    ax.plot(sub_N["N"], sub_N["mean_error_h"], color=NEWTON_COLOR,
            marker="o", label=NEWTON_LABEL)
    ax.plot(sub_N["N"], sub_N["mean_error_g"], color=GRAD_COLOR,
            marker="s", label=GRAD_LABEL)
    c = sub_N["mean_error_h"].iloc[-1] * np.sqrt(n_ref[-1])
    ax.plot(n_ref, c / np.sqrt(n_ref), color="gray", ls=":",
            lw=1.2, label=r"$O(N^{-1/2})$")
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel("Mean absolute error")
    ax.set_title(f"MAE vs. $N$ — sequential — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_N["N"].values)
    fig.tight_layout()
    savefig("MAE_wrt_N_seq.pdf")

    # ── 2.  MaxAE vs N (seq) ──────────────────────────────────────────────────
    fig, ax = make_fig("MaxAE_wrt_N_seq.pdf", scale_key="MaxAE_vs_N")
    ax.plot(sub_N["N"], sub_N["max_error_h"], color=NEWTON_COLOR,
            marker="o", label=NEWTON_LABEL)
    ax.plot(sub_N["N"], sub_N["max_error_g"], color=GRAD_COLOR,
            marker="s", label=GRAD_LABEL)
    c = sub_N["max_error_h"].iloc[-1] * np.sqrt(n_ref[-1])
    ax.plot(n_ref, c / np.sqrt(n_ref), color="gray", ls=":",
            lw=1.2, label=r"$O(N^{-1/2})$")
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel("Max absolute error")
    ax.set_title(f"Max AE vs. $N$ — sequential — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_N["N"].values)
    fig.tight_layout()
    savefig("MaxAE_wrt_N_seq.pdf")

    # ── 3.  Agreement vs N (seq) ──────────────────────────────────────────────
    fig, ax = make_fig("Agreement_wrt_N_seq.pdf", scale_key="Agreement_vs_N")
    ax.plot(sub_N["N"], sub_N["mean_error_h_g"], color=AGREE_COLOR,
            marker="D", label="|Newton − GA|")
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useMathText=True))
    ax.ticklabel_format(axis="y", style="sci", scilimits=(0, 0))
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel(r"Mean $|\hat\theta^{\rm N} - \hat\theta^{\rm GA}|$")
    ax.set_title(f"Estimator agreement — sequential — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_N["N"].values)
    fig.tight_layout()
    savefig("Agreement_wrt_N_seq.pdf")

    # ── 4 & 5.  vs P (need multiple d values) ────────────────────────────────
    d_vals = sorted(seq["d"].unique())
    if len(d_vals) > 1:
        sub_P = seq[seq["p"] == p_val].copy()
        sub_P["P"] = p_val * (sub_P["d"] - 1)
        N_rep = sub_P["N"].max()
        sub_P = sub_P[sub_P["N"] == N_rep].sort_values("P")

        for metric, col_h, col_g, ylabel, fname in [
            ("MAE",   "mean_error_h", "mean_error_g",
             "Mean absolute error", "MAE_wrt_P_seq.pdf"),
            ("MaxAE", "max_error_h",  "max_error_g",
             "Max absolute error",  "MaxAE_wrt_P_seq.pdf"),
        ]:
            fig, ax = plt.subplots(figsize=(5.2, 3.8))
            ax.plot(sub_P["P"], sub_P[col_h], color=NEWTON_COLOR,
                    marker="o", label=NEWTON_LABEL)
            ax.plot(sub_P["P"], sub_P[col_g], color=GRAD_COLOR,
                    marker="s", label=GRAD_LABEL)
            ax.set_xlabel("Number of parameters $P = p(d-1)$")
            ax.set_ylabel(ylabel)
            ax.set_title(f"{metric} vs. $P$ — $N={N_rep:,}$, $p={p_val}$")
            ax.legend()
            fig.tight_layout()
            savefig(fname)
            plt.close()
    else:
        print("  [skip] vs-P figures — need multiple d values in sequential CSV.")

    # ── 6.  Runtime vs N (seq, two panels) ───────────────────────────────────
    combos = seq[["p", "d"]].drop_duplicates().sort_values(["p", "d"])
    fig, axes = plt.subplots(1, 2, figsize=(10, 4))
    for idx, (_, row) in enumerate(combos.iterrows()):
        sub = seq[(seq["p"] == row["p"]) & (seq["d"] == row["d"])].sort_values("N")
        P_v = int(row["p"] * (row["d"] - 1))
        c, m = PALETTE[idx % len(PALETTE)], MARKERS[idx % len(MARKERS)]
        axes[0].plot(sub["N"], sub["runtime_h_us"] / 1e6,
                     color=c, marker=m, label=f"$P={P_v}$")
        axes[1].plot(sub["N"], sub["runtime_g_us"] / 1e6,
                     color=c, marker=m, label=f"$P={P_v}$")
    for ax, title in zip(axes, [NEWTON_LABEL, GRAD_LABEL]):
        ax.set_xlabel("Sample size $N$")
        ax.set_ylabel("Runtime (s)")
        ax.set_title(title)
        set_N_axis(ax, seq["N"].values)
        ax.legend(title="$P$", ncol=2, fontsize=8)
    fig.suptitle("Sequential runtime vs. $N$", y=1.01)
    fig.tight_layout()
    savefig("RT_wrt_N_seq.pdf")
    plt.close()

    # ── 7.  Runtime vs P (seq) ────────────────────────────────────────────────
    if len(d_vals) > 1:
        N_vals = sorted(seq["N"].unique())
        fig, axes = plt.subplots(1, 2, figsize=(10, 4))
        for idx, N_v in enumerate(N_vals):
            sub = seq[(seq["p"] == p_val) & (seq["N"] == N_v)].copy()
            sub["P"] = p_val * (sub["d"] - 1)
            sub.sort_values("P", inplace=True)
            c, m = PALETTE[idx % len(PALETTE)], MARKERS[idx % len(MARKERS)]
            axes[0].plot(sub["P"], sub["runtime_h_us"] / 1e6,
                         color=c, marker=m, label=f"$N={N_v:,}$")
            axes[1].plot(sub["P"], sub["runtime_g_us"] / 1e6,
                         color=c, marker=m, label=f"$N={N_v:,}$")
        for ax, title in zip(axes, [NEWTON_LABEL, GRAD_LABEL]):
            ax.set_xlabel("Number of parameters $P = p(d-1)$")
            ax.set_ylabel("Runtime (s)")
            ax.set_title(title)
            ax.legend(title="$N$", ncol=2, fontsize=8)
        fig.suptitle("Sequential runtime vs. $P$", y=1.01)
        fig.tight_layout()
        savefig("RT_wrt_P_seq.pdf")
        plt.close()

    # ── 8.  Trade-off speedup vs P ────────────────────────────────────────────
    if len(d_vals) > 1:
        trd = seq[seq["p"] == p_val].copy()
        trd["P"] = p_val * (trd["d"] - 1)
        trd["speedup"] = trd["runtime_g_us"] / trd["runtime_h_us"]
        trd_agg = (trd.groupby("P")["speedup"].mean()
                      .reset_index().sort_values("P"))
        fig, ax = plt.subplots(figsize=(5.2, 3.8))
        ax.plot(trd_agg["P"], trd_agg["speedup"],
                color=NEWTON_COLOR, marker="o")
        slope, intercept, *_ = stats.linregress(
            trd_agg["P"], trd_agg["speedup"])
        if slope < 0:
            crossover = -intercept / slope
            ax.axhline(1, color="gray", ls=":", lw=1.0)
            ax.annotate(f"crossover ≈ {crossover:.0f}",
                        xy=(crossover, 1),
                        xytext=(crossover * 0.6, 1.5),
                        arrowprops=dict(arrowstyle="->", color="gray"),
                        fontsize=9, color="gray")
        ax.set_xlabel("Number of parameters $P$")
        ax.set_ylabel("Speedup (GA / Newton)")
        ax.set_title("Newton speedup over gradient ascent vs. $P$")
        fig.tight_layout()
        savefig("Tradeoff_speedup.pdf")
        plt.close()


# ══════════════════════════════════════════════════════════════════════════════
#  PARALLEL FIGURES
# ══════════════════════════════════════════════════════════════════════════════

def figures_parallel(par):
    print("\n── Parallel figures ──")

    p_val = par["p"].mode()[0]
    d_val = 2 if 2 in par["d"].values else par["d"].mode()[0]
    sub   = par[(par["p"] == p_val) & (par["d"] == d_val)].copy()
    sub.sort_values(["T", "N"], inplace=True)

    T_vals = sorted(sub["T"].unique())
    T_seq  = T_vals[0]

    # ── MAE / MaxAE / Agreement vs N  (parallel, registered for shared scales) ─
    # Use the run with the most threads for the "parallel" error curves
    T_best  = T_vals[-2]
    sub_err = sub[sub["T"] == T_best].sort_values("N")
    n_ref   = sub_err["N"].values.astype(float)
    P_label = f"$p={p_val},\\ d={d_val},\\ T={T_best}$"

    fig, ax = make_fig("MAE_wrt_N_par.pdf", scale_key="MAE_vs_N")
    ax.plot(sub_err["N"], sub_err["mean_error_h"], color=NEWTON_COLOR,
            marker="o", label=NEWTON_LABEL)
    ax.plot(sub_err["N"], sub_err["mean_error_g"], color=GRAD_COLOR,
            marker="s", label=GRAD_LABEL)
    c = sub_err["mean_error_h"].iloc[-1] * np.sqrt(n_ref[-1])
    ax.plot(n_ref, c / np.sqrt(n_ref), color="gray", ls=":",
            lw=1.2, label=r"$O(N^{-1/2})$")
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel("Mean absolute error")
    ax.set_title(f"MAE vs. $N$ — parallel — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_err["N"].values)
    fig.tight_layout()
    savefig("MAE_wrt_N_par.pdf")

    fig, ax = make_fig("MaxAE_wrt_N_par.pdf", scale_key="MaxAE_vs_N")
    ax.plot(sub_err["N"], sub_err["max_error_h"], color=NEWTON_COLOR,
            marker="o", label=NEWTON_LABEL)
    ax.plot(sub_err["N"], sub_err["max_error_g"], color=GRAD_COLOR,
            marker="s", label=GRAD_LABEL)
    c = sub_err["max_error_h"].iloc[-1] * np.sqrt(n_ref[-1])
    ax.plot(n_ref, c / np.sqrt(n_ref), color="gray", ls=":",
            lw=1.2, label=r"$O(N^{-1/2})$")
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel("Max absolute error")
    ax.set_title(f"Max AE vs. $N$ — parallel — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_err["N"].values)
    fig.tight_layout()
    savefig("MaxAE_wrt_N_par.pdf")

    fig, ax = make_fig("Agreement_wrt_N_par.pdf", scale_key="Agreement_vs_N")
    ax.plot(sub_err["N"], sub_err["mean_error_h_g"], color=AGREE_COLOR,
            marker="D", label="|Newton − GA|")
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useMathText=True))
    ax.ticklabel_format(axis="y", style="sci", scilimits=(0, 0))
    ax.set_xlabel("Sample size $N$")
    ax.set_ylabel(r"Mean $|\hat\theta^{\rm N} - \hat\theta^{\rm GA}|$")
    ax.set_title(f"Estimator agreement — parallel — {P_label}")
    ax.legend()
    set_N_axis(ax, sub_err["N"].values)
    fig.tight_layout()
    savefig("Agreement_wrt_N_par.pdf")

    # ── Speedup vs N (one curve per T) ────────────────────────────────────────
    for rt_col, fname, title in [
        ("runtime_h_us", "Speedup_vs_N_Newton.pdf", NEWTON_LABEL),
        ("runtime_g_us", "Speedup_vs_N_GA.pdf",     GRAD_LABEL),
    ]:
        baseline = sub[sub["T"] == T_seq][["N", rt_col]].set_index("N")
        fig, ax  = plt.subplots(figsize=(5.8, 4.0))
        for idx, T_v in enumerate(T_vals):
            if T_v == T_seq:
                continue
            sub_T    = sub[sub["T"] == T_v].set_index("N")
            common_N = baseline.index.intersection(sub_T.index)
            spdup    = baseline.loc[common_N, rt_col] / sub_T.loc[common_N, rt_col]
            ax.plot(common_N, spdup.values,
                    color=PALETTE[idx % len(PALETTE)],
                    marker=MARKERS[idx % len(MARKERS)],
                    label=f"$T={T_v}$")
        for T_v in T_vals[1:]:
            ax.axhline(T_v, color="gray", ls=":", lw=0.8, alpha=0.5)
        ax.set_xlabel("Sample size $N$")
        ax.set_ylabel(f"Speedup vs. $T={T_seq}$")
        ax.set_title(f"Parallel speedup — {title}")
        ax.legend(title="Threads $T$")
        set_N_axis(ax, sub["N"].values)
        fig.tight_layout()
        savefig(fname)
        plt.close()

    # ── Speedup vs T (one curve per N) ────────────────────────────────────────
    N_vals   = sorted(sub["N"].unique())
    step     = max(1, len(N_vals) // 6)
    N_sample = N_vals[::step]

    for rt_col, fname, title in [
        ("runtime_h_us", "Speedup_vs_T_Newton.pdf", NEWTON_LABEL),
        ("runtime_g_us", "Speedup_vs_T_GA.pdf",     GRAD_LABEL),
    ]:
        fig, ax = plt.subplots(figsize=(5.2, 3.8))
        for idx, N_v in enumerate(N_sample):
            sub_N  = sub[sub["N"] == N_v].sort_values("T")
            t0_row = sub_N[sub_N["T"] == T_seq]
            if t0_row.empty:
                continue
            t0 = t0_row[rt_col].values[0]
            ax.plot(sub_N["T"], t0 / sub_N[rt_col].values,
                    color=PALETTE[idx % len(PALETTE)],
                    marker=MARKERS[idx % len(MARKERS)],
                    label=f"$N={N_v:,}$")
        T_range = np.array(T_vals, dtype=float)
        ax.plot(T_range, T_range / T_seq, color="gray", ls="--",
                lw=1.0, label="Ideal linear")
        ax.set_xlabel("Number of threads $T$")
        ax.set_ylabel(f"Speedup vs. $T={T_seq}$")
        ax.set_title(f"Speedup vs. thread count — {title}")
        ax.legend(title="$N$", fontsize=8, ncol=2)
        fig.tight_layout()
        savefig(fname)
        plt.close()

    # ── Runtime vs N (parallel, all T) ───────────────────────────────────────
    fig, axes = plt.subplots(1, 2, figsize=(10.5, 4.2))
    for ax, rt_col, title in zip(axes,
            ["runtime_h_us", "runtime_g_us"], [NEWTON_LABEL, GRAD_LABEL]):
        for idx, T_v in enumerate(T_vals):
            sub_T = sub[sub["T"] == T_v].sort_values("N")
            ax.plot(sub_T["N"], sub_T[rt_col] / 1e6,
                    color=PALETTE[idx % len(PALETTE)],
                    marker=MARKERS[idx % len(MARKERS)],
                    label=f"$T={T_v}$")
        ax.set_xlabel("Sample size $N$")
        ax.set_ylabel("Runtime (s)")
        ax.set_title(title)
        ax.legend(title="Threads")
        set_N_axis(ax, sub["N"].values)
    fig.suptitle("Parallel runtime vs. $N$", y=1.01)
    fig.tight_layout()
    savefig("RT_wrt_N_parallel.pdf")
    plt.close()

    # ── Parallel efficiency vs N ──────────────────────────────────────────────
    fig, axes = plt.subplots(1, 2, figsize=(10.5, 4.2), sharey=True)
    for ax, rt_col, title in zip(axes,
            ["runtime_h_us", "runtime_g_us"], [NEWTON_LABEL, GRAD_LABEL]):
        baseline = sub[sub["T"] == T_seq][["N", rt_col]].set_index("N")
        for idx, T_v in enumerate(T_vals):
            if T_v == T_seq:
                continue
            sub_T    = sub[sub["T"] == T_v].set_index("N")
            common_N = baseline.index.intersection(sub_T.index)
            eff      = (baseline.loc[common_N, rt_col]
                        / sub_T.loc[common_N, rt_col]) / T_v
            ax.plot(common_N, eff.values,
                    color=PALETTE[idx % len(PALETTE)],
                    marker=MARKERS[idx % len(MARKERS)],
                    label=f"$T={T_v}$")
        ax.axhline(1.0, color="gray", ls=":", lw=0.8)
        ax.set_xlabel("Sample size $N$")
        ax.set_ylabel("Parallel efficiency (speedup / $T$)")
        ax.set_title(title)
        ax.legend(title="Threads")
        set_N_axis(ax, sub["N"].values)
        ax.set_ylim(bottom=0)
    fig.suptitle("Parallel efficiency vs. $N$", y=1.01)
    fig.tight_layout()
    savefig("Efficiency_vs_N.pdf")
    plt.close()


# ══════════════════════════════════════════════════════════════════════════════
#  MAIN
# ══════════════════════════════════════════════════════════════════════════════

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--seq", default=None, help="Sequential results CSV")
    parser.add_argument("--par", default=None, help="Parallel results CSV")
    args = parser.parse_args()

    if args.seq:
        figures_sequential(load(args.seq))
    else:
        print("No sequential CSV — skipping sequential figures.")

    if args.par:
        figures_parallel(load(args.par))
    else:
        print("No parallel CSV — skipping parallel figures.")

    # Post-process: unify y-scales across seq/par pairs, then re-save
    apply_shared_scales()

    print("\nDone.  All figures saved to ./plots/")


if __name__ == "__main__":
    main()