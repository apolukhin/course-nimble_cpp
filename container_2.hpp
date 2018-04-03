#include "util.hpp"

#include <vector>
#include <deque>
#include <list>

//////////////////////////// TASK 3 ////////////////////////////

static void naive_containers_erase(benchmark::State& state, int) {
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
    state.SetComplexityN(state.range(0));
}

static void optim_containers_erase(benchmark::State& state, int) {
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
    state.SetComplexityN(state.range(0));
}


//////////////////////////// DETAIL ////////////////////////////
BENCH(naive_containers_erase, naive_containers_erase, 0)->Range(8, 8<<8)->Complexity();
BENCH(optim_containers_erase, optim_containers_erase, 0)->Range(8, 8<<8)->Complexity();
