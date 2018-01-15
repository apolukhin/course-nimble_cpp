#include "container_common.hpp"

#include <set>
#include <unordered_set>

#include <boost/container/set.hpp>
#include <boost/unordered_set.hpp>

//////////////////////////// TASK 6 ////////////////////////////

std::unordered_set<int> naive_assoc_container();
std::set<int> optimized_assoc_container();


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_CAPTURE(containers_iteration, naive_assoc_container, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_iteration, optim_assoc_container, optimized_assoc_container)->Range(8, 8<<10);

BENCHMARK_CAPTURE(containers_search_assoc, naive_assoc_container, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_search_assoc, optim_assoc_container, optimized_assoc_container)->Range(8, 8<<10);

BENCHMARK_CAPTURE(containers_insertion_assoc, naive_assoc_container, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_CAPTURE(containers_insertion_assoc, optim_assoc_container, optimized_assoc_container)->Range(8, 8<<10);
