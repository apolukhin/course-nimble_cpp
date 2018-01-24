#include "algorithm_common.hpp"

//////////////////////////// TASK 5 ////////////////////////////

struct  my_complex {
    int real, im;

    ~my_complex() {};
};


struct  my_complex_opt {
    int real, im;

    ~my_complex_opt() {};
};


template <class T>
static void measure_copy_speed(benchmark::State& state) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<T> d(elements_count);
        std::vector<T> dest(elements_count);
        state.ResumeTiming();

        std::copy(d.cbegin(), d.cend(), dest.begin());
        benchmark::DoNotOptimize(d);
        benchmark::DoNotOptimize(dest);
    }
}


//////////////////////////// DETAIL ////////////////////////////
BENCHMARK_TEMPLATE(measure_copy_speed, my_complex)->Range(8, 8<<10);
BENCHMARK_TEMPLATE(measure_copy_speed, my_complex_opt)->Range(8, 8<<10);

