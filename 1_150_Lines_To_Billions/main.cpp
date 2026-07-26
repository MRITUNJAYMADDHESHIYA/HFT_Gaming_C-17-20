


//cache-line aligned lock-free data structure
struct alignas(64) PriceLevel{
    std::atomic<int64_t> price{0};
    std::atomic<int64_t> quantity{0};
    std::atomic<uint64_t> sequence{0};
};