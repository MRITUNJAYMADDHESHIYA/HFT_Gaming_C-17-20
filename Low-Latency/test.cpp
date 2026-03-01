// ● General considerations
// ● Compile-time dispatch
// ● Constexpr
// ● Variadic templates
// ● Loop unrolling
// ● Expression short-circuiting
// ● Signed vs unsigned comparisons
// ● Mixing float and doubles
// ● Branch prediction/reduction
// ● Exceptions
// ● Slowpath removal
// ● Avoiding allocations
// ● Fast containers
// ● Lambda functions



constexpr n = 10000;
int array[n];

//71us, SD 1.5us
std::sort(array, array + n, [](int a, int b){return b<a;});

//223us, SD 7us
int comparer(const void* a, const void* b){
    return *(int* a) - *(int* b);
}
qsort(arr, n, sizeof(int), comparer);

