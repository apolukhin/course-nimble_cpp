#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 1 ////////////////////////////

using naive_container = std::vector<int>;
using optimized_container = std::vector<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_TEMPLATE(iteration, naive_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(iteration, optimized_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(insertion, naive_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(insertion, optimized_container)->Range(8, 8<<10);
