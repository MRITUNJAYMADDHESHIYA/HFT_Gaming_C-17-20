#include <benchmark/benchmark.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <cmath>
#include <array>
#include <immintrin.h>
#include <iostream>

using namespace std;

std::vector<double> stock1_prices;
std::vector<double> stock2_prices;

vector<double> readCSV(const string& filename) {
    std::vector<double> prices;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;
        while (std::getline(ss, value, ',')) row.push_back(value);
        if (row.size() > 5 && !row[5].empty())
            prices.push_back(std::stod(row[5]));
    }
    return prices;
}

void read_prices() {
    stock1_prices = readCSV("GS.csv");
    stock2_prices = readCSV("MS.csv");
}

template<size_t N>
void pairs_trading_strategy_optimized(const std::vector<double>& s1, const std::vector<double>& s2) {
    static_assert(N % 4 == 0, "N must be multiple of 4 for AVX2");
    if (s1.size() < N || s2.size() < N) return;

    std::array<double, N> spread;
    size_t spread_index = 0;

    for (size_t i = 0; i < N; ++i)
        spread[i] = s1[i] - s2[i];

    for (size_t i = N; i < s1.size(); ++i) {
        __m256d sum_vec = _mm256_setzero_pd();
        __m256d sq_sum_vec = _mm256_setzero_pd();

        for (size_t j = 0; j < N; j += 4) {
            __m256d spread_vec = _mm256_loadu_pd(&spread[j]);
            sum_vec = _mm256_add_pd(sum_vec, spread_vec);
            sq_sum_vec = _mm256_add_pd(sq_sum_vec, _mm256_mul_pd(spread_vec, spread_vec));
        }

        alignas(32) double temp[4];
        _mm256_store_pd(temp, sum_vec);
        double sum = temp[0] + temp[1] + temp[2] + temp[3];
        _mm256_store_pd(temp, sq_sum_vec);
        double sq_sum = temp[0] + temp[1] + temp[2] + temp[3];

        double mean = sum / N;
        double stddev = std::sqrt(sq_sum / N - mean * mean);

        double current_spread = s1[i] - s2[i];
        double z_score = (current_spread - mean) / stddev;
        spread[spread_index] = current_spread;

        // Trading decision logic (mock)
        if (z_score > 1.0) {
            // Long/Short
        } else if (z_score < -1.0) {
            // Short/Long
        } else if (std::abs(z_score) < 0.8) {
            // Close positions
        }

        spread_index = (spread_index + 1) % N;
    }
}

template<size_t N>
void BM_PairsTradingStrategyOptimized(benchmark::State& state) {
    if (stock1_prices.empty() || stock2_prices.empty())
        read_prices();
    for (auto _ : state)
        pairs_trading_strategy_optimized<N>(stock1_prices, stock2_prices);
}


BENCHMARK_TEMPLATE(BM_PairsTradingStrategyOptimized, 8);
BENCHMARK_MAIN();


// ------------------------------------------------------------------------------
// Benchmark                                    Time             CPU   Iterations
// ------------------------------------------------------------------------------
// BM_PairsTradingStrategyOptimized<8>      24026 ns        24010 ns        23810

//coding is important for you Mritunjay budy