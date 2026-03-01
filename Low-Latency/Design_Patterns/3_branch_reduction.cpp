//1.Breanch_reduction:- (if, else, switch..) removal techniques
//predictable latency matters more than average latency.

//use:- Arithmetic operations
//   :- Bitwise operations
//   :- Ternary operators
//   :- Lookup tables
//   :- Masks
//   :- SIMD intrinsics

#include <benchmark/benchmark.h>
#include<iostream>
#include<vector>

using namespace std;

//////////Example//////////////////////////
int maxi(int a, int b){
  if(a > b) return a;
  return b;
}

int maxi_branch(int a, int b){
  return a + (a < b) * (b - a);
}

int maxi_branch2(int a, int b){
  int mask = -(a < b);
  return a ^ ((a^b) & mask);
}

/////////////Example2/////////////////
int loop(vector<int>& arr){
  for(int i=0; i<n; ++i){
    // if(arr[i] > 0){
    //   sum += arr[i]; 
    // }

    int x = arr[i];
    sum += x * (x > 0);
  }
}




////////////This is normally error checking setup
int errorCounterA = 0;

bool checkForErrorA() {
  // Produce an error once every 10 calls
  errorCounterA++;
  return (errorCounterA % 10) == 0;
}

bool checkForErrorB() {
  // Simulate some error check
  return false;
}

bool checkForErrorC() {
  // Simulate some error check
  return false;
}

void handleErrorA() {
  // Simulate some error handling
}

void handleErrorB() {
  // Simulate some error handling
}

void handleErrorC() {
  // Simulate some error handling
}

void executeHotpath() {
  // Simulate some hot path execution
}

static void Branching(benchmark::State& state) {
  errorCounterA = 0;  // reset the counter before benchmark run
  for (auto _ : state) {
    if (checkForErrorA())
      handleErrorA();
    else if (checkForErrorB())
      handleErrorB();
    else if (checkForErrorC())
      handleErrorC();
    else
      executeHotpath();
  }
}

/////////////// This is the methods for branch reduction
enum ErrorFlags {
  ErrorA = 1 << 0,
  ErrorB = 1 << 1,
  ErrorC = 1 << 2,
  NoError = 0
};

int errorCounterFlags = 0;

ErrorFlags checkErrors() {
  // Produce ErrorA once every 10 calls
  errorCounterFlags++;
  return (errorCounterFlags % 10) == 0 ? ErrorA : NoError;
}

void HandleError(ErrorFlags errorFlags) {
  // Simulate some error handling based on flags
  if (errorFlags & ErrorA) {
    handleErrorA();
  }
  // handle other errors similarly...
}

void hotpath() {
  // Simulate some hot path execution
}

static void ReducedBranching(benchmark::State& state) {
  errorCounterFlags = 0;  // reset the counter before benchmark run
  for (auto _ : state) {
    ErrorFlags errorFlags = checkErrors();
    if (errorFlags)
      HandleError(errorFlags);
    else
      hotpath();
  }
}

//////////////////////// BenchMark ///////////////////////////
BENCHMARK(Branching);
BENCHMARK(ReducedBranching);

BENCHMARK_MAIN();