///Part 2
/////////////////Programming for deterministic execution time
//////////// Cache ////////////////
//1.Minimise data cache misses(periodically poke data on a timer)
//-->Data locality + Align data on cachelines + Concurrency aspect + always vector + std::flat_set/flat_map + binary search
// 2.Minimise instruction cache misses (periodically run the hot path with dummy input/output)
// -->code layout/alignment + avoid branches + avoid virtual functions(variant + CRTP)
// 
//////////////CPU throtting /////////
//--->Due to overheating(spread thermal dissipation)
//--->Due to low activity(keep cpu busy with pause instructions)  

/////////////What not to do in the hot path /////////////////////////
//1.Dynamic memory allocations/deallocations
//2.blocking the thread
//3.I/O
//4.exceptions
//5.context switches /mode switches(user/kernal space)
//6.syscalls
//7.calling into unknown code
//8.loops without definite bounds
//9.algorithms > o(1), or with no statically known upper bound N

//////////////////////////1.Dynamic memory allocations/deallocations ////////////////////////
//Avoiding allocations:-
//Do not use data types that allocate
//Do not use algorithms that allocate
//Do not use data structure that allocate

//question:- Which standard algorithm allocate memory?
//--->stable_sort, stable_partition, inplace_merge (do not use in low-latency)

//for memory point of view
//use:- array, pair, tuple, optional, variant
//do not use:-any, function, vector, deque, list

//Allocators:-
//tcmalloc, rpmalloc:- are not good for ultra low latency and real time.

//Preallocate everything:-
//Monotonic allocators(std::pmr::monotonic_buffer_resource)
//Pool allocators(std::pmr::unsynchronised_pool_resource)
//Frame allocators
//Arena allocators
//Double-ended allocators

//Lock-free allocators:-

////////////Lambdas ///////////
void process(buffer& b){
    std::array a = {1, 2, 2, 3, 4, 5, 8, 9};

    //this will never allocate
    auto f = [=] {
        return std::accumulate(a.begin(), a.end(), 0);
    };
}

//Coroutines may perform dynamic allocation:-we can optimize this
//Don't use this in low-latency/real time


/////////////////Blocking the thread////////////////////
//Don't use mutex(blocking, unpredictable, slow)
//mutex/ timed_mutex/ shared_mutex/ scoped_lock/ unique_lock/ shared_lock/ condition_variable/ latch/ binary_semaphore/ barrier/ counting_semaphore
//
//
//atomic    == indivisible, race-free
//lock-free == at least one thread is guaranteed to make progress
//wait-free == all threads are guaranteed to make progress
//static_assert(std::atomic<float>::is_always_lock_free);-----> always use
//
//Wait-free concurrency:-
//Passing data to/from "hot path" thread--->wait-free queue(SCSP)
//Sharing data with "hot path" thread--->Hot path reads(try_lock/"spin-on-writ"/RCU)
//                               |------>Hot path writes(Double-buffering/SeqLock)
//double with atomic:- x86, x64, armv7, arm64--->apple clang v13


/// try_lock:-
//use with spin_lock not with mutex







