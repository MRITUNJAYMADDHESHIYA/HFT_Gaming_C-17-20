#include<iostream>
#include<fmt/core.h>
#include<array>
#include<map>
#include<tuple>
#include<utility>
#include<ignore>
#include<algorithm>

/////1.Print in python + c++
print(f"{(1, 2)}, this is {1+2}")

int main(){
    fmt::print("{} this is {}", std::tuple(1,2), 3);
}

////2.Container
print([1, 2, 3, 4])
print({1: 2, 3: 4}) 

fmt::print("{}\n", std::array{1, 2, 3, 4});
fmt::print("{}\n", std::map<int, int>{{1, 2}, {3, 4}});

/////3.for loop
for i in [1, 2, 3]:
    print(i)

for(auto i: std::array{1, 2, 3}){
    fmt::print("{}\n", i);
}

////4.enumerate(idx with value)
for idx, val in enumerate([10, 20, 30]):
    print(idx, val)

for(int i=0; auto val:std::array{10, 20, 30}){
    fmt::print("the value in idx {} is {}\n", i++, v);
}

////5.ignoring value
def foo(a,b):
    return a, b, a+b
_, _, c = foo(1, 2)


auto foo(auto a, auto b){
    return std::tuple{a, b, a+b};
}
int main(){
    int c;
    std::tie(std::ignore, std::ignore, c) = foo(1, 2);
    //or
    auto [_, __, c] = foo(1, 2);
}

/////6.random number in python and c++
import random
print([x if x>5 and x<9 else 0 for x in [random.uniform(0, 20)]*20])

auto odd = [](uint64_t x){return x%2 != 0;};
auto v   = std::views::iota(1, 30) | std::views::filter(odd) | std::views::take(10) | std::views::reverse;
fmt::print("{}\n", v);


//Why can't use python only\
//Numpy is really good for array operation and fast prototyping
//Always use modules that already in python
//learn the module in deep ways

//--slow
//--easier to make mistakes
//problems:-
def foo(a):
    return a+b
if __name__ == "__main__":
    b = 10
    print(foo(5))



















