//1.The decision of which function or code path to call is made at compile time, not at runtime.
//Remove virtual function overhead
//Removes branches and dynamic checks
//Enables inlining

//use:- templates, constexpr


//1.Runtime dispatch:- use virtual functions + late binding
//2.Compile-time dispatch:- use templates + early binding

#include<benchmark/benchmark.h>

class Base{
    public:
        virtual ~Base() {}
        virtual int function() const = 0;
};

class Derived1 : public Base{
    public:
        int function() const override{
            return 1;
        }
};

class Derived2 : public Base{
    public:
        int function() const override{
            return 2;
        }
};

////////// Runtime dispatch ////////////////////////////
static void BM_RuntimeDispatch(benchmark::State& state){
    Base* obj;
    if(state.range(0) == 1){
        obj = new Derived1();
    }else{
        obj = new Derived2();
    }

    for(auto _ : state){
        benchmark::DoNotOptimize(obj->function()); //DoNotOptimize() prevents compiler from removing or inlining the call.
    }

    delete obj;
}
BENCHMARK(BM_RuntimeDispatch)->Arg(1)->Arg(2);


//////////////// Compile-time dispatch /////////////////////////
template<typename T>
static void BM_CompileTimeDispatch(benchmark::State& state){
    T obj;
    for(auto _ : state){
        benchmark::DoNotOptimize(obj.function());
    }
}
BENCHMARK_TEMPLATE(BM_CompileTimeDispatch, Derived1);
BENCHMARK_TEMPLATE(BM_CompileTimeDispatch, Derived2);
BENCHMARK_MAIN();


