#include "util.hpp"

//////////////////////////// TASK 6 ////////////////////////////

struct  naive_complex {
    int real, im;

    naive_complex() {}
    naive_complex(const naive_complex& nc)
        : real(nc.real)
        , im(nc.im)
    {}
    ~naive_complex(){}
};


struct  optim_complex { // TASK: Improve
    int real, im;

    optim_complex() {}
    optim_complex(const optim_complex& nc)
        : real(nc.real)
        , im(nc.im)
    {}
    ~optim_complex() {}
};


//////////////////////////// DETAIL ////////////////////////////

template <class T>
static void copy_speed(benchmark::State& state, const T& /*data_type*/) {
    const std::size_t elements_count = state.range();
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

BENCH(copy_speed, naive_copy_speed, naive_complex{})->Range(8, 8 << 10);
BENCH(copy_speed, optim_copy_speed, optim_complex{})->Range(8, 8 << 10);

