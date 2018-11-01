#pragma once

#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <iomanip>


#ifndef COURSE_GLOBAL_ARGS
#   define COURSE_GLOBAL_ARGS()
#endif

#define BENCH(func, test_case_name, ...)                        \
  BENCHMARK_PRIVATE_DECLARE(func) =                             \
      (::benchmark::internal::RegisterBenchmarkInternal(        \
          new ::benchmark::internal::FunctionBenchmark(         \
              #test_case_name,                                  \
    [](::benchmark::State& st) { func(st, __VA_ARGS__); })))    \
    COURSE_GLOBAL_ARGS()




template <class T>
inline void fill_container_impl(T& c, std::size_t size) {
    std::minstd_rand e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    c.clear();
    for (std::size_t i = 0; i < size / 2; ++i) {
        c.insert(c.end(), uniform_dist(e1));
        c.insert(c.end(), uniform_dist(e1));
    }
}

template <class T>
inline void fill_container(T& c, std::size_t size) {
    fill_container_impl(c, size);
}

inline void fill_container(std::vector<int>& c, std::size_t size) {
    c.reserve(size);
    fill_container_impl(c, size);
}


// Fills container with Range elements count, measures `f(d)` execution time, compares result with `ethalon(d)`.
template <class F, class Ethalon>
inline void algorithms(benchmark::State& state, F f, Ethalon ethalon) {
    std::vector<int> d;

    for (auto _ : state) {
        state.PauseTiming();
        fill_container(d, state.range(0));
        state.ResumeTiming();

        const auto val = f(d); // Measuring this call
        benchmark::DoNotOptimize(val);

        state.PauseTiming();
        if (f != ethalon) {
            const auto ethalon_value = ethalon(d);
            if (ethalon_value != val) {
                throw std::logic_error("Values missmatch");
            }
        }
        state.ResumeTiming();
    }
    state.SetComplexityN(state.range(0));
}



template <class Type>
static void iteration(benchmark::State& state, const Type& /*container_type*/) {
    for (auto _ : state) {
        state.PauseTiming();
        Type d;
        fill_container(d, state.range(0));
        state.ResumeTiming();

        int sum = 0;
        for (auto v: d) {
            sum += v; // Measuring this call
        }
        benchmark::DoNotOptimize(sum);

    }
}

template <class Type>
static void insertion(benchmark::State& state, const Type& /*container_type*/) {
    std::minstd_rand e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    const std::size_t iterations_count = state.range(0);
    for (auto _ : state) {
        Type d;
        d.clear();
        for (std::size_t i = 0; i < iterations_count; ++i) {
            d.insert(d.end(), uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class Type>
static void insertion_assoc(benchmark::State& state, const Type& /*container_type*/) {
    std::minstd_rand e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    const std::size_t iterations_count = state.range(0);
    for (auto _ : state) {
        Type d;
        d.clear();
        for (std::size_t i = 0; i < iterations_count; ++i) {
            d.insert(uniform_dist(e1));
        }
        benchmark::DoNotOptimize(d);
    }
}

template <class Type>
static void search_assoc(benchmark::State& state, const Type& /*container_type*/) {
    Type d;
    std::minstd_rand e1;
    std::uniform_int_distribution<int> uniform_dist(-100000, 100000);

    d.clear();
    const std::size_t iterations_count = state.range(0);
    for (std::size_t i = 0; i < iterations_count; ++i) {
        d.insert(uniform_dist(e1));
    }

    for (auto _ : state) {
        for (auto it = d.begin(); it != d.end(); ++it) {
            auto v = *d.find(*it);
            benchmark::DoNotOptimize(v);
        }
    }
}
