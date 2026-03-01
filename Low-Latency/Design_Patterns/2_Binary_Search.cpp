#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <numeric>

// ---------- Binary Search ----------
bool binarySearch(const std::vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return true;
        if (arr[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

// ---------- Ternary Search ----------
bool ternarySearch(const std::vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if (arr[mid1] == x || arr[mid2] == x) return true;
        if (x < arr[mid1]) r = mid1 - 1;
        else if (x > arr[mid2]) l = mid2 + 1;
        else { l = mid1 + 1; r = mid2 - 1; }
    }
    return false;
}

// ---------- Exponential Search ----------
bool exponentialSearch(const std::vector<int>& arr, int x) {
    if (arr.empty()) return false;
    if (arr[0] == x) return true;

    int i = 1;
    while (i < arr.size() && arr[i] <= x)
        i *= 2;
    return std::binary_search(arr.begin() + i/2, arr.begin() + std::min(i, (int)arr.size()), x);
}

// ---------- Multithreaded Binary Search ----------
bool parallelBinarySearch(const std::vector<int>& arr, int x) {
    int mid = arr.size() / 2;
    auto f1 = std::async(std::launch::async, [&]() {
        return std::binary_search(arr.begin(), arr.begin() + mid, x);
    });
    auto f2 = std::async(std::launch::async, [&]() {
        return std::binary_search(arr.begin() + mid, arr.end(), x);
    });
    return f1.get() || f2.get();
}


///////////////////////// BenchMark /////////////////////////////////
static void BM_BinarySearch(benchmark::State& state) {
    std::vector<int> data(state.range(0));
    std::iota(data.begin(), data.end(), 0);
    int target = data.back();
    for (auto _ : state) {
        benchmark::DoNotOptimize(binarySearch(data, target));
    }
}

static void BM_TernarySearch(benchmark::State& state) {
    std::vector<int> data(state.range(0));
    std::iota(data.begin(), data.end(), 0);
    int target = data.back();
    for (auto _ : state) {
        benchmark::DoNotOptimize(ternarySearch(data, target));
    }
}

static void BM_ExponentialSearch(benchmark::State& state) {
    std::vector<int> data(state.range(0));
    std::iota(data.begin(), data.end(), 0);
    int target = data.back();
    for (auto _ : state) {
        benchmark::DoNotOptimize(exponentialSearch(data, target));
    }
}

static void BM_ParallelBinarySearch(benchmark::State& state) {
    std::vector<int> data(state.range(0));
    std::iota(data.begin(), data.end(), 0);
    int target = data.back();
    for (auto _ : state) {
        benchmark::DoNotOptimize(parallelBinarySearch(data, target));
    }
}

////////////////// Register Benchmarks ///////////////////////////
BENCHMARK(BM_BinarySearch)->Arg(1<<10)->Arg(1<<15)->Arg(1<<20);
BENCHMARK(BM_TernarySearch)->Arg(1<<10)->Arg(1<<15)->Arg(1<<20);
BENCHMARK(BM_ExponentialSearch)->Arg(1<<10)->Arg(1<<15)->Arg(1<<20);
BENCHMARK(BM_ParallelBinarySearch)->Arg(1<<10)->Arg(1<<15)->Arg(1<<20);

BENCHMARK_MAIN();
