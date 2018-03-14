#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include "algorithm_common.hpp"

#include "common.hpp"


////////////////////////////////////////////////////////////////
//////////////////////////// DETAIL ////////////////////////////
////////////////////////////////////////////////////////////////



template <class Type>
static void iteration(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Type d;
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

template <class Type>
static void insertion(benchmark::State& state) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    for (auto _ : state) {
        Type d;
        d.clear();
        for (std::size_t i = 0; i < state.range(0); ++i) {
            d.insert(d.end(), uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class Type>
static void insertion_assoc(benchmark::State& state) {
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    for (auto _ : state) {
        Type d;
        d.clear();
        for (std::size_t i = 0; i < state.range(0); ++i) {
            d.insert(uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class Type>
static void search_assoc(benchmark::State& state) {
    Type d;
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

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
