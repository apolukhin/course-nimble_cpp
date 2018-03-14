#include "container_common.hpp"

#include <set>
#include <unordered_set>

#include <boost/container/set.hpp>
#include <boost/unordered_set.hpp>

//////////////////////////// TASK 6 ////////////////////////////

using naive_assoc_container = std::unordered_set<int>;
using optim_assoc_container = std::set<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_TEMPLATE(iteration, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(iteration, optim_assoc_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(search_assoc, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(search_assoc, optim_assoc_container)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(insertion_assoc, naive_assoc_container)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(insertion_assoc, optim_assoc_container)->Range(8, 8<<10);
