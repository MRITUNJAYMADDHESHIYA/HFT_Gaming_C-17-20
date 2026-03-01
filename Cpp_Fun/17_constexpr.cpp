//improved compile-time 
////The constexpr function doesn’t even run at runtime — the compiler just embeds 120 in the binary.
//This feature ensures that functions or expressions can be evaluated during compilation, resulting in optimized code with no runtime cost for certain operations

#include<iostream>
#include<chrono>

constexpr int factorial(int n){
    return (n<=1) ? 1 : (n* factorial(n-1));
}

int factorial2(int n){
    return (n<=1) ? 1 : (n*factorial2(n-1));
}

int main(){
// Compile-time computed
    constexpr int ans = factorial(5);
    std::cout << "Factorial (constexpr): " << ans << std::endl;

    // Measure runtime for non-constexpr version
    auto start = std::chrono::high_resolution_clock::now();
    int ans2 = factorial2(5);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> duration = end - start;

    std::cout << "Factorial (runtime): " << ans2 << std::endl;
    std::cout << "Execution time (runtime): " << duration.count() << " ns" << std::endl;
}
