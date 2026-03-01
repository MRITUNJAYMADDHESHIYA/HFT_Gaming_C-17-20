#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <string>

/////////////1st Function inside the benchmark ////////
static void BM_SortVector(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v(state.range(0));
        std::generate(v.begin(), v.end(), std::rand);
        std::sort(v.begin(), v.end());
    }
}

///////////////2nd Function Outside the benchmark //////////////
void SomeFunction(size_t size){
    std::string s1(size, '-');
    std::string s2(size, '-');
    benchmark::DoNotOptimize(s1.compare(s2));
}

static void BM_SomeFunction(benchmark::State& state){
    for(auto _ :state){
        SomeFunction(state.range(0));
    }
}

// Register benchmark with input size 1<<10 (1024)
// Register benchmark with input size 1000, 2000, 3000
// Register
BENCHMARK(BM_SortVector)->Arg(1 << 10);
BENCHMARK(BM_SomeFunction)->Arg(1000)->Arg(2000)->Arg(3000);
BENCHMARK(BM_SomeFunction)->RangeMultiplier(2)->Range(1 << 10, 1 <<20);

// Run benchmarks
BENCHMARK_MAIN();


// ///////This is main function for benchmark execution /////////
// int main(int argc, char** argv) {
//     benchmark::Initialize(&argc, argv);
//     benchmark::RunSpecifiedBenchmarks();
// }


//g++ -std=c++20 -O3 benckmarktest.cpp -lbenchmark -pthread -o branch_bench
//./branch_bench