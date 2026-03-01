//1.Games(5-16ns) + HFT(100ns - 10 micros) + Audio + Automotive + Robotics
//Not about:- Embedded, Exotic architectures, GPU, Language design, c++ successor languages

//What is Low-Latency?-->very little delay.
//what is throughput?-->amount of work done per second.

//HFT-->You have to faster than every one. and you don't know how fast it is.
//Missing deadline--->lost money in HFT + drop video frame in Gaming + risk human life Embedded

//Ultra low latency + Real time programming(Efficiency)
//Efficiency:-To reduce the amount of work to perform certain task

//Hardware and server:- you have to build yourself


//Why c++ for low-latency?
//1.Manual memory management(To avoid allocation/deallocations)-->present in C
//2.Scalable zero-cost abstractions(algorithms, templates)------->present in Rust
//3.Huge body of existing libraries and frameworks(JUCE(audio), UnrealEngine(gaming))

//How to write in cpp?
//Efficient programming(part 1) + Deterministic execution time(part 2)



///////////////////////Profiling(measuring the performance of program)/////////////////////////
//1.CPU Profiling:-       (gprof, perf(linux), Instruments(mac))
//2.Memory Profiling:-    (Valgrind(memcheck))
//3.Microbenchingmarking:-(Google Bechmark, chrono)
//4.Cache misses:-        (perf stat, cachgrind)
//5.Branch mispredicts, syscalls, allocation:- ()
//6.Measure Performance of machine instruction on a particular CPU(llvm-mca)
//7.Inspect generated assembly:-  (compiler explorer)
//


//Part 1:-
//Efficient Code:-
//programming language + libraries + compiler(optimiser, ABI(microsoft))
//knowledge of the hardware architecture:-(CPU architecture + cache hierarchy + Prefetcher + Branch Predictor)

//Unnecessary work:- copies, function calls, 
//make as many decidions as possible at compile time(constexpr, template, lookuptable)
//Efficent mathematical expression:- fast approx, use powers of two,
//bit manipulation:- Object lifetime rules, aliasing rule, alignment rules, object representation, value representation, std::bit_cast, std::start_lifetime_as, implicit-lifetime types
//Optimiser and undefined behaviour:- memory related, data races, signed integer overflow, infinite loops with no side effect  
// 
// 
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


/////////// Lamda function
const std::vector<std::string> v = {"apple", "orange", "lemon", "mango"};
const std::string prefix = "foo";

auto result = std::find_if(v.begin(), v.end(), [&prefix](const std::string& s){return s == prefix + "bar";});
auto result = std::find_if(v.begin(), v.end(), [str = prefix + "bar"](const std::string& s){return s == str;});

if(result != v.end()){
    std::cout<< prefix <<"-something found!\n";
}

//////////simple reference thing
for(auto it: v){}
for(const auto& it: v){}

/////////assume(condition)
int process(int x){
    [[assume(x>0)]];
    return 100/x;
}

////////////CPU pipeline hazards//////////////////////////////
//Branch + Data + Hardware hazard

///////BranchLess Programming:-///////////////////
//avoid conditional branches (if, else, switch) and instead use arithmetic, bitwise, or SIMD operations to achieve the same logic without branching.
if(x || y) do_this();
if(bool(x) + bool(y)) do_this();


sum += cond ? expr1 : expr2;

bool expr[2] = {expr1, expr2};
sum += expr[bool(cond)];

//////////////[[likely]] and [[unlikely]]

///////////////Avoid data hazards:-///////////
unsigned atoui(const char* c){
    unsigned result = 0;
    while(*c >= '0' && *c <= '9'){ //one calculation here
        result = result * 10 + (*c - '0'); //then here
    }
    return result;
}

//////////////Hardware:-//////////////////
//limited amount of adders/shifters
//limited amount of load/store units
//Hardware bugs


//////////////////////SIMD(single instruction multiple data)////////
//How to use:- auto-vectorisation-->explicit vectorisation--->writing intrinsics-->writing assembly
//Auto-vectorisation:-
//dependent on compiler + only works with vectors/arrays + no consitions

int a[1000], b[1000], c[1000];
for(int i=0; i<1000; ++i){
    a[i] += b[i];
    b[i+1] += c[i];
}

//this is faster: vectorisation
a[0] += b[0];
for(int i=1; i<999; ++i){
    b[i+1] += c[i];
    a[i+1] += b[i+1];
}
b[999] += c[999];


////Explicit vectorisation libraries
/////If you know the exact target CPU: use arch compiler flags
