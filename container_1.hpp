#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 1 ////////////////////////////

using naive_container = std::vector<int>;
using optimized_container = std::vector<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_TEMPLATE(containers_iteration, naive_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(containers_iteration, optimized_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(containers_insertion, naive_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(containers_insertion, optimized_container)->Range(8, 8<<10);
