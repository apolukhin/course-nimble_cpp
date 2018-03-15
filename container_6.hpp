#include "container_common.hpp"

#include <set>
#include <unordered_set>

#include <boost/container/set.hpp>
#include <boost/unordered_set.hpp>

//////////////////////////// TASK 6 ////////////////////////////

using naive_assoc_container = std::unordered_set<int>;
using optim_assoc_container = std::set<int>;


//////////////////////////// DETAIL ////////////////////////////
BENCH(iteration, naive_assoc_container_iteration, naive_assoc_container{})->Range(8, 8<<10);
BENCH(iteration, optim_assoc_container_iteration, optim_assoc_container{})->Range(8, 8<<10);

BENCH(search_assoc, naive_assoc_container_search, naive_assoc_container{})->Range(8, 8<<10);
BENCH(search_assoc, optim_assoc_container_search, optim_assoc_container{})->Range(8, 8<<10);

BENCH(insertion_assoc, naive_assoc_container_insertion, naive_assoc_container{})->Range(8, 8<<10);
BENCH(insertion_assoc, optim_assoc_container_insertion, optim_assoc_container{})->Range(8, 8<<10);
