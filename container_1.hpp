#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 1 ////////////////////////////

std::vector<int> naive_container();
std::vector<int> optimized_container(); // Optimize


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(containers_iteration, naive_container, naive_container)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_iteration, optim_container, optimized_container)->Range(8, 8<<10);

BENCHMARK_CAPTURE(containers_insertion, naive_container, naive_container)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_insertion, optim_container, optimized_container)->Range(8, 8<<10);
