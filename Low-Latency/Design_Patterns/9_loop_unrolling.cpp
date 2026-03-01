
#include<benchmark/benchmark.h>
#include<vector>
#include<string>
using namespace std;
static void BM_LoopUnrolling(benchmark::State& state){
    for(auto _ : state){
        int result = 0;
        for(int i=0; i<state.range(0); ++i){
            result += i;
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_LoopUnrolling)->Arg(1000);

static void BM_LoopWithUnrolling(benchmark::State& state){
    for(auto _ : state){
        int result = 0;
        for(int i=0; i<state.range(0); i +=4){
            result += i + (i+1) + (i+2) + (i+3);
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_LoopWithUnrolling)->Arg(1000);
BENCHMARK_MAIN();

// BM_LoopUnrolling/1000           83.6 ns         81.9 ns      8860537
// BM_LoopWithUnrolling/1000       64.2 ns         62.9 ns     11210233