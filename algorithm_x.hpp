#include "algorithm_common.hpp"

//////////////////////////// TASK 3 ////////////////////////////

int naive_something(std::vector<int>& d) {
    std::stable_sort(d.begin(), d.end());
    // ...
    return *d.begin();
}

int optimized_something(std::vector<int>& d) {
    // TASK: Improve
    std::stable_sort(d.begin(), d.end());
    // ...
    return *d.begin();
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(algorithms, naive_something, naive_something, naive_something)->Range(8, 8<<10)->Complexity();
BENCHMARK_CAPTURE(algorithms, optim_something, optimized_something, naive_something)->Range(8, 8<<10)->Complexity();

