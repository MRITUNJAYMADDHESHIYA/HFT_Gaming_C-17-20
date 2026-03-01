#include<benchmark/benchmark.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<numeric>
#include<cmath>
#include<iostream>
using namespace std;

/////////////////////Read file //////////////////////////////
vector<double> readCSV(const string& filename){
    std::vector<double> prices;
    std::ifstream file(filename); //open file
    std::string line;

    std::getline(file, line); //skip the header line(first row)

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;

        while(std::getline(ss, value, ',')){
            row.push_back(value);
        }

        double adjClose = std::stod(row[5]); 
        prices.push_back(adjClose);
    }

    return prices;
}

//////////////// mean ///////////////////////////
__attribute__ ((noinline))  //when you use accurate microbenchmarks(include function call overhead)
double calc_mean(const std::vector<double>& v){
    double sum = 0.0;
    double sq_sum = 0.0;

    for(auto &s:v){
        sum += s;
        sq_sum += s*s;
    }
    return (sum / v.size());
}

//////////////// SD ///////////////////////////
__attribute__ ((noinline))
double calc_stddev(const std::vector<double>& v, double mean){
    double sum = 0.0;
    double sq_sum = 0.0;
    for(auto &s: v){
        sum += s;
        sq_sum += s*s;
    }
    return std::sqrt(sq_sum/v.size()-mean*mean);
}

///////////////Pair Trading //////////////////////////
void pairs_trading_strategy(const std::vector<double>& prices1, const std::vector<double>& prices2, size_t N){
    for(size_t i=N; i<prices1.size(); ++i){
        std::vector<double> spread(prices1.begin()+i-N, prices1.begin()+i);

        for(size_t j=0; j<N; ++j){
            spread[j] -= prices2[i-N+j];
        }

        double mean           = calc_mean(spread);
        double stddev         = calc_stddev(spread, mean);
        double current_spread = prices1[i] - prices2[i];
        double z_score        = (current_spread - mean)/stddev;

        if(z_score > 1.0){
            // counter++;
            // cout<<z_score<<endl;
            //short signal
            cout<<"short"<<endl;
        }else if(z_score < -1.0){
            //counter++;
            //long signal
            cout<<"long"<<endl;
        }else if(abs(z_score) < 0.8){
            //close positions
        }else{
            //counter++;
            //no signal
        }
    }
    //cout<<counter<<endl;
}

std::vector<double> prices1;
std::vector<double> prices2;

void read_prices(){
    string gs_file = "GS.csv";
    string ms_file = "MS.csv";

    prices1 = readCSV(gs_file);
    prices2 = readCSV(ms_file);
}

static void BM_PairsTradingStrategy(benchmark::State& state){
    if(prices1.empty() || prices2.empty()){
        read_prices();
    }
    for(auto _ : state){
        pairs_trading_strategy(prices1, prices2, 8);
    }
}

BENCHMARK(BM_PairsTradingStrategy);
BENCHMARK_MAIN();


// Benchmark                        Time             CPU   Iterations
// ------------------------------------------------------------------
// BM_PairsTradingStrategy    4501152 ns      2372155 ns          345