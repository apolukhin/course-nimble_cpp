#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////
//////////////////////////// DETAIL ////////////////////////////
////////////////////////////////////////////////////////////////
static void fill_container(std::vector<int>& c, std::size_t size) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    c.clear();
    c.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
        c.push_back(uniform_dist(e1));
    }
}

// Fills container with Range elements count, measures `f(d)` execution time, compares result with `ethalon(d)`.
template <class F, class Ethalon>
static void algorithms(benchmark::State& state, F f, Ethalon ethalon) {
    std::vector<int> d;

    for (auto _ : state) {
        state.PauseTiming();
        fill_container(d, state.range(0));
        state.ResumeTiming();

        const auto val = f(d); // Measuring this call

        state.PauseTiming();
        const auto ethalon_value = ethalon(d);
        if (ethalon_value != val) {
            throw std::logic_error("Values missmatch");
        }
        state.ResumeTiming();
    }
    state.SetComplexityN(state.range(0));
}
