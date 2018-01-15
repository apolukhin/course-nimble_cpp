#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 2 ////////////////////////////

static void naive_containers_insertion(benchmark::State& state) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        std::vector<int> d;

        for (unsigned i = 0; i < elements_count; ++i) {
            d.push_back(i);
        }
        benchmark::DoNotOptimize(d);
    }
}

static void optim_containers_insertion(benchmark::State& state) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        // Optimize
        std::vector<int> d;

        for (unsigned i = 0; i < elements_count; ++i) {
            d.push_back(i);
        }
        benchmark::DoNotOptimize(d);
    }
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK(naive_containers_insertion)->Range(8, 8<<10);
BENCHMARK(optim_containers_insertion)->Range(8, 8<<10);
