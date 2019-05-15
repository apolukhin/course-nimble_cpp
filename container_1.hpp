#include "util.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 1 ////////////////////////////

using naive_container = std::vector<int>;
using optimized_container = std::vector<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCH(iteration, naive_container_iteration, naive_container{})->Range(8, 8<<10);
BENCH(iteration, optim_container_iteration, optimized_container{})->Range(8, 8<<10);

BENCH(iteration_cold_cache, naive_no_cache_container_iteration, naive_container{})->Range(8, 8<<10);
BENCH(iteration_cold_cache, optim_no_cache_container_iteration, optimized_container{})->Range(8, 8<<10);

BENCH(insertion, naive_container_insertion, naive_container{})->Range(8, 8<<10);
BENCH(insertion, optim_container_insertion, optimized_container{})->Range(8, 8<<10);
