#include "util.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 3 ////////////////////////////

static void naive_insertion(benchmark::State& state, int) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        std::vector<int> d;

        for (unsigned i = 0; i < elements_count; ++i) {
            d.push_back(i);
        }
        benchmark::DoNotOptimize(d);
    }
}

static void optim_insertion(benchmark::State& state, int) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        // TASK: Improve
        std::vector<int> d;

        for (unsigned i = 0; i < elements_count; ++i) {
            d.push_back(i);
        }
        benchmark::DoNotOptimize(d);
    }
}


//////////////////////////// DETAIL ////////////////////////////
BENCH(naive_insertion, naive_insertion, 0)->Range(8, 8<<10);
BENCH(optim_insertion, optim_insertion, 0)->Range(8, 8<<10);
