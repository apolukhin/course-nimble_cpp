#include "util.hpp"

//////////////////////////// TASK 1 ////////////////////////////

int naive_99th_perc(std::vector<int>& d) {
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + static_cast<std::size_t>(d.size() * 0.99));
}

int optimized_99th_perc(std::vector<int>& d) {
    // TASK: Improve
    std::stable_sort(d.begin(), d.end());
    return *(d.begin() + static_cast<std::size_t>(d.size() * 0.99));
}


//////////////////////////// DETAIL ////////////////////////////
BENCH(algorithms, naive_99th_perc, naive_99th_perc, naive_99th_perc)->Range(8, 8 << 10)->Complexity();
BENCH(algorithms, optim_99th_perc, optimized_99th_perc, naive_99th_perc)->Range(8, 8 << 10)->Complexity();
