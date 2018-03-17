#include "util.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 5 ////////////////////////////

struct  my_array {
    int data_[100];

    my_array() {};
    my_array(int v) {
        std::fill_n(data_, 100, v);
    }
    ~my_array() {};
};

struct  my_array_opt {
    int data_[100];

    my_array_opt() {};
    my_array_opt(int v) {
        std::fill_n(data_, 100, v);
    }
    ~my_array_opt() {};
};




using naive_array = std::vector<my_array>;
using optimized_array = std::vector<my_array_opt>;


//////////////////////////// DETAIL ////////////////////////////
BENCH(insertion, naive_array_ins, naive_array{})->Range(8, 8<<10);
BENCH(insertion, optim_array_ins, optimized_array{})->Range(8, 8<<10);
