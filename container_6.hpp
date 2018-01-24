#include "container_common.hpp"

#include <set>
#include <unordered_set>

#include <boost/container/set.hpp>
#include <boost/unordered_set.hpp>

//////////////////////////// TASK 6 ////////////////////////////

using naive_assoc_container = std::unordered_set<int>;
using optimized_assoc_container = std::set<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_TEMPLATE(containers_iteration, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(containers_iteration, optimized_assoc_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(containers_search_assoc, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(containers_search_assoc, optimized_assoc_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(containers_insertion_assoc, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(containers_insertion_assoc, optimized_assoc_container)->Range(8, 8<<10);
