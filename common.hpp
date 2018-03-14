#pragma once

#include <benchmark/benchmark.h>


#define BENCH(func, test_case_name, ...)     \
  BENCHMARK_PRIVATE_DECLARE(func) =                      \
      (::benchmark::internal::RegisterBenchmarkInternal( \
          new ::benchmark::internal::FunctionBenchmark(  \
              #test_case_name,                           \
    [](::benchmark::State& st) { func(st, __VA_ARGS__); })))

