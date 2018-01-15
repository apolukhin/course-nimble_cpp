#include "container_common.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 3 ////////////////////////////

static void naive_containers_erase(benchmark::State& state) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> d;
        fill_container(d, elements_count);
        state.ResumeTiming();

        while (!d.empty()) {
            d.erase(d.begin());
        }
        benchmark::DoNotOptimize(d);
    }
}

static void optim_containers_erase(benchmark::State& state) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> d;
        fill_container(d, elements_count);
        state.ResumeTiming();

        while (!d.empty()) {
            // Optimize
            d.erase(d.begin());
        }
        benchmark::DoNotOptimize(d);
    }
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK(naive_containers_erase)->Range(8, 8<<10);
BENCHMARK(optim_containers_erase)->Range(8, 8<<10);
