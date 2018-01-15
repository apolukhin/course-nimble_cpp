#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 4 ////////////////////////////

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




std::vector<my_array> naive_array();
std::vector<my_array_opt> optimized_array();


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(containers_insertion, naive_array, naive_array)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_insertion, optim_array, optimized_array)->Range(8, 8<<10);
