//1.constexpr:- evaluate at compile time
//use at:- variables/functions/constructors/class methods/if constexpr/algorithms

#include<iostream>
#include<benchmark/benchmark.h>

//1.//no memory access at runtime
constexpr int x = 10; 
//2.//evaluated at compile time
constexpr int square(int n){
    return n * n;
}
constexpr int y = square(x); 
//3.//constructed at compile time
struct Point{
    int x, y;
    constexpr Point(int x_val, int y_val) : x(x_val), y(y_val) {}
};
constexpr Point p(3, 4); 
//4.//removes unused branches entirely
template<typename T>
void print(T value){
    if constexpr (std::is_integral_v<T>){
        std::cout << "Integral: " << value << std::endl;
    } else {
        std::cout << "Non-Integral: " << value << std::endl;
    }
}

////////////////////// Use of constexpr in Benchmark //////////////////////
constexpr int factorial(int n){
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

int runtime_factorial(int n){
    return (n <= 1) ? 1 : (n * runtime_factorial(n - 1));
}

static void BM_ConstexprFactorial(benchmark::State& state) {
    for (auto _ : state) {
        int result = factorial(10);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_ConstexprFactorial);

static void BM_RuntimeFactorial(benchmark::State& state) {
    for (auto _ : state) {
        int result = runtime_factorial(10);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_RuntimeFactorial);

BENCHMARK_MAIN();