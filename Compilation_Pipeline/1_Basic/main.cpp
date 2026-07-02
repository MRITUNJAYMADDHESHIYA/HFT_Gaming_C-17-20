//1.clang/LLVM, GCC

#include<vector>
#include<numeric>
#include<concepts>

template<std::integral T>
T sum_vector(const std::vector<T> &v){
    return std::accumulate(v.begin(), v.end(), T{0});
}

int main(){
    std::vector<int> data{1, 2, 3, 4, 5};
    return sum_vector(data);
}

//preprocessing(header inclusion)
//parsing(templates, concepts, stl)
//template instantiation for sum_vector<int>
//optimization(inlining std::accoumulate, loop unrolling, vectorization)
//linking against the c++ 

