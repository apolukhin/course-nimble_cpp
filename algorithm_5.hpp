#include "algorithm_common.hpp"

//////////////////////////// TASK 5 ////////////////////////////

int naive_10_perc_of_not_bankrupted(std::vector<int>& d) {
    std::stable_sort(d.begin(), d.end());
    auto it = std::lower_bound(d.begin(), d.end(), 0);
    auto end_of_10_perc = it + static_Cast<std::size_t>((d.end() - it) * 0.1);
    return *end_of_10_perc;
}

int optimized_10_perc_of_not_bankrupted(std::vector<int>& d) {
    // TASK: Improve
    std::stable_sort(d.begin(), d.end());
    auto it = std::lower_bound(d.begin(), d.end(), 0);
    auto end_of_10_perc = it + static_Cast<std::size_t>((d.end() - it) * 0.1);
    return *end_of_10_perc;
}


//////////////////////////// DETAIL ////////////////////////////
BENCH(algorithms, naive_10_perc_pos, naive_10_perc_of_not_bankrupted, naive_10_perc_of_not_bankrupted)->Range(8, 8 << 10)->Complexity();
BENCH(algorithms, optim_10_perc_pos, optimized_10_perc_of_not_bankrupted, naive_10_perc_of_not_bankrupted)->Range(8, 8 << 10)->Complexity();

