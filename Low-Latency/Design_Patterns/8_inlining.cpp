//inlining is a compiler optimization technique where the function body is expanded at the call site, instead of making a normal function call.
//1.most of the time use in small functions
//2.reduces function call overhead
#include <benchmark/benchmark.h>

int add(int a, int b) {
    return a + b;
}

inline int inline_add(int a, int b) {
    return a + b;
}

static void BM_WithoutInline(benchmark::State& state){
    for(auto _ : state){
        benchmark::DoNotOptimize(add(1, 2));
    }
}
BENCHMARK(BM_WithoutInline);

static void BM_WithInline(benchmark::State& state){
    for(auto _ : state){
        benchmark::DoNotOptimize(inline_add(1, 2));
    }
}
BENCHMARK(BM_WithInline);

BENCHMARK_MAIN();