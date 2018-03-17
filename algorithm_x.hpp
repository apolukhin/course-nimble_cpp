#include "util.hpp"

//////////////////////////// TASK 3 ////////////////////////////

int naive_something(std::vector<int>& d) {
    std::sort(d.begin(), d.end());
    // ...
    return *d.begin();
}

int optimized_something(std::vector<int>& d) {
    // TASK: Improve
    std::sort(d.begin(), d.end());
    // ...
    return *d.begin();
}


//////////////////////////// DETAIL ////////////////////////////
BENCH(algorithms, naive_something, naive_something, naive_something)->Range(8, 8<<10)->Complexity();
BENCH(algorithms, optim_something, optimized_something, naive_something)->Range(8, 8<<10)->Complexity();

