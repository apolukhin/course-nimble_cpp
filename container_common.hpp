#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include "algorithm_common.hpp"

#include <benchmark/benchmark.h>


////////////////////////////////////////////////////////////////
//////////////////////////// DETAIL ////////////////////////////
////////////////////////////////////////////////////////////////

template <class T>
static void fill_container_simple(T& c, std::size_t size) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    c.clear();
    for (std::size_t i = 0; i < size; ++i) {
        c.insert(c.end(), uniform_dist(e1));
    }
}


template <class F>
static void containers_iteration(benchmark::State& state, F f) {
    decltype(f()) d;

    for (auto _ : state) {
        state.PauseTiming();
        fill_container_simple(d, state.range(0));
        state.ResumeTiming();

        for (unsigned i = 0; i < 10000; ++i) {
            int sum = 0;
            for (auto v: d) {
                sum += v; // Measuring this call
            }
            benchmark::DoNotOptimize(sum);
        }
    }
}

template <class F>
static void containers_insertion(benchmark::State& state, F f) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    for (auto _ : state) {
        decltype(f()) d;
        d.clear();
        for (std::size_t i = 0; i < state.range(0); ++i) {
            d.insert(d.end(), uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class F>
static void containers_insertion_assoc(benchmark::State& state, F f) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    for (auto _ : state) {
        decltype(f()) d;
        d.clear();
        for (std::size_t i = 0; i < state.range(0); ++i) {
            d.insert(uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class F>
static void containers_search_assoc(benchmark::State& state, F f) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    decltype(f()) d;
    d.clear();
    for (std::size_t i = 0; i < state.range(0); ++i) {
        d.insert(uniform_dist(e1));
    }

    for (auto _ : state) {
        for (auto it = d.begin(); it != d.end(); ++it) {
            auto v = *d.find(*it);
            benchmark::DoNotOptimize(v);
        }
    }
}
