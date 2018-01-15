#include "algorithm_common.hpp"

//////////////////////////// TASK 1 ////////////////////////////

int naive_99th_perc(std::vector<int>& d) {
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + d.size() * 0.99);
}

int optimized_99th_perc(std::vector<int>& d) {
    // TASK: Improve
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + d.size() * 0.99);
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(algorithms, naive_99th_perc, naive_99th_perc, naive_99th_perc)->Range(8, 8<<10)->Complexity();
BENCHMARK_CAPTURE(algorithms, optim_99th_perc, optimized_99th_perc, naive_99th_perc)->Range(8, 8<<10)->Complexity();
