//1. Implement A fixed-size memory pool allocator

////Question:-
//Design and implement a fixed-size memory pool that pre-allocates a large chunk of
//memory and serves fixed-size object allocation in O(1) time. The allocator must avoid 
//fragmentation and support deallocation. Discuss cache locality and alignment concerns.



//solution:-
//pre-allocate one large memory block
//split it into equal-sized chunks
//maintain a free list of available chunks
//allocation == pop from free list(O(1))
//deallocation == push back to free list(O(1))
//no extrnal fragmentation because every block has identical size


//Design:-
// memory pool
// ------------------------------------------------------
// |Block0 | block1 | block2 | block3 |...... | BlockN |
// ------------------------------------------------------
// 
// Free list
// head --> block0-->block1-->block2-->nullptr
//
//
//


#include<iostream>
#include<cstddef>
#include<new>
#include<cassert>


class MemoryPool{
    private:

        struct FreeBlock{FreeBlock* next;};

        void* memory_;  //stores large memory chunk
        FreeBlock* freeList_; //points to the first available block

        std::size_t blockSize_; //each block size
        std::size_t blockCount_; //total count

    public:
        MemoryPool(std::size_t blockSize, std::size_t blockCount) : memory(nullptr), freeList_(nullptr), blockSize_(blockSize), blockCount_(blockCount){
            //ensure every block can store a pointer
            blockSize_ = std::max(blockSize_, sizeof(FreeBlock));
            memory_    = ::operator new(blockSize_ * blockCount_);
            char* start = static_cast<char*>(memory_);  //moves exactly 32 bytes

            //create free list
            for(std::size_t i=0; i<blockCount_; i++){
                FreeBlock* block = reinterpret_cast<FreeBlock*>(start + i * blockSize_);
                block->next = freeList_;
                freeList_ = block;
            }
        }

        ~MemoryPool(){
            ::operator delete(memory_);
        }

        void* allocate(){
            if(!freeList_){
                throw std::bad_alloc();
            }

            FreeBlock* block = freeList_;
            freeList_ = freeList_->next;

            return block;
        }

        void deallocate(void* ptr){
            if(!ptr) return;

            FreeBlock* block = static_cast<FreeBlock*>(ptr);

            block->next = freeList_;
            freeList_ = block;
        }
};