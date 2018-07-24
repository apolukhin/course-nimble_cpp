#include "util.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 4 ////////////////////////////

class my_unique_ptr {
    int* data_ = nullptr;

public:
    my_unique_ptr() = default;

    my_unique_ptr(int v)
        : data_(new int{v})
    {}

    my_unique_ptr(const my_unique_ptr& p)
        : data_(p.data_ ? new int{*p.data_} : nullptr)
    {}

    my_unique_ptr(my_unique_ptr&& p)
        : data_(p.data_)
    {
        p.data_ = nullptr;
    }

    my_unique_ptr& operator=(const my_unique_ptr& p) {
        my_unique_ptr tmp(p);
        std::swap(tmp.data_, data_);
        return *this;
    }

    my_unique_ptr& operator=(my_unique_ptr&& p) {
        std::swap(data_, p.data_);
        return *this;
    }

    ~my_unique_ptr() {
        delete data_;
    }
};



class my_unique_ptr_opt {
    int* data_ = nullptr;

public:
    my_unique_ptr_opt() = default;
    my_unique_ptr_opt(int v)
        : data_(new int{v})
    {}

    my_unique_ptr_opt(const my_unique_ptr_opt& p)
        : data_(p.data_ ? new int{*p.data_} : nullptr)
    {}

    my_unique_ptr_opt(my_unique_ptr_opt&& p)
        : data_(p.data_)
    {
        p.data_ = nullptr;
    }

    my_unique_ptr_opt& operator=(const my_unique_ptr_opt& p) {
        my_unique_ptr_opt tmp(p);
        std::swap(p.data_, data_);
        return *this;
    }

    my_unique_ptr_opt& operator=(my_unique_ptr_opt&& p) {
        std::swap(data_, p.data_);
        return *this;
    }

    ~my_unique_ptr_opt() {
        delete data_;
    }
};



using naive_uptr = std::vector<my_unique_ptr>;
using optimized_uptr = std::vector<my_unique_ptr_opt>;


//////////////////////////// DETAIL ////////////////////////////
BENCH(insertion, naive_uptr_vec_insertion, naive_uptr{})->Range(8, 8<<10);
BENCH(insertion, optim_uptr_vec_insertion, optimized_uptr{})->Range(8, 8<<10);
