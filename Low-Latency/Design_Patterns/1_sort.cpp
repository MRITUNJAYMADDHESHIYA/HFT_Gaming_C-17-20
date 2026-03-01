#include <algorithm>
#include <vector>
#include <random>
#include <benchmark/benchmark.h>


//////////// Generate random vector /////////////////////
std::vector<int> generate_random_vector(size_t n) {
    std::vector<int> v(n);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 1e9);
    for (auto &x : v) x = dist(rng);
    return v;
}


/////////////Bubble Sort (O(n²)) ///////////////////////
void bubble_sort(std::vector<int>& a) {
    size_t n = a.size();
    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


////////////////////Insertion Sort (O(n²))//////////////
void insertion_sort(std::vector<int>& a) {
    for (size_t i = 1; i < a.size(); i++) {
        int key = a[i];
        size_t j = i - 1;
        while (j < a.size() && a[j] > key) {
            a[j + 1] = a[j];
            if (j == 0) break;
            j--;
        }
        if (a[j] > key)
            a[j] = key;
        else
            a[j + 1] = key;
    }
}


////////////////////Merge Sort (O(n log n))/////////////
void merge(std::vector<int>& a, int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int i = 0; i < n2; i++) R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j] ? L[i++] : R[j++]);
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void merge_sort_rec(std::vector<int>& a, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    merge_sort_rec(a, l, mid);
    merge_sort_rec(a, mid + 1, r);
    merge(a, l, mid, r);
}

void merge_sort(std::vector<int>& a) {
    merge_sort_rec(a, 0, a.size() - 1);
}


//////////////////Quick Sort (O(n log n))/////////////////////
int partition(std::vector<int>& a, int low, int high) {
    int pivot = a[high];
    int i = low;
    for (int j = low; j < high; j++)
        if (a[j] <= pivot)
            std::swap(a[i++], a[j]);
    std::swap(a[i], a[high]);
    return i;
}

void quick_sort_rec(std::vector<int>& a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quick_sort_rec(a, low, pi - 1);
        quick_sort_rec(a, pi + 1, high);
    }
}

void quick_sort(std::vector<int>& a) {
    quick_sort_rec(a, 0, a.size() - 1);
}

/////////////////////////////////////////////
//////////////// Benchmark //////////////////
// Each benchmark generates the vector fresh,
// then copies it for fair comparison.
/////////////////////////////////////////////

static void BM_BubbleSort(benchmark::State& state) {
    auto base = generate_random_vector(state.range(0));
    for (auto _ : state) {
        auto v = base;
        bubble_sort(v);
    }
}
BENCHMARK(BM_BubbleSort)->RangeMultiplier(2)->Range(128, 2048);

static void BM_InsertionSort(benchmark::State& state) {
    auto base = generate_random_vector(state.range(0));
    for (auto _ : state) {
        auto v = base;
        insertion_sort(v);
    }
}
BENCHMARK(BM_InsertionSort)->RangeMultiplier(2)->Range(128, 4096);

static void BM_MergeSort(benchmark::State& state) {
    auto base = generate_random_vector(state.range(0));
    for (auto _ : state) {
        auto v = base;
        merge_sort(v);
    }
}
BENCHMARK(BM_MergeSort)->RangeMultiplier(2)->Range(128, 1 << 17);

static void BM_QuickSort(benchmark::State& state) {
    auto base = generate_random_vector(state.range(0));
    for (auto _ : state) {
        auto v = base;
        quick_sort(v);
    }
}
BENCHMARK(BM_QuickSort)->RangeMultiplier(2)->Range(128, 1 << 17);

static void BM_StdSort(benchmark::State& state) {
    auto base = generate_random_vector(state.range(0));
    for (auto _ : state) {
        auto v = base;
        std::sort(v.begin(), v.end());
    }
}
BENCHMARK(BM_StdSort)->RangeMultiplier(2)->Range(128, 1 << 17);

BENCHMARK_MAIN();
