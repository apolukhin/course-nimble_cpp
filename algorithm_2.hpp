#include "algorithm_common.hpp"

//////////////////////////// TASK 2 ////////////////////////////

int naive_median(std::vector<int>& d) {
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + d.size() * 0.5);
}

int optimized_median(std::vector<int>& d) {
    // TASK: Improve
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + d.size() * 0.5);
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(algorithms, naive_median, naive_median, naive_median)->Range(8, 8<<10)->Complexity();
BENCHMARK_CAPTURE(algorithms, optim_median, optimized_median, naive_median)->Range(8, 8<<10)->Complexity();

