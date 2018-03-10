#include "mt_common.hpp"

//////////////////////////// TASK 1 ////////////////////////////

struct wrong_shared_var_t { // Do not modify!
    int variable{0};

    int inc() {
        return ++variable;
    }

    int dec() {
        return --variable;
    }
} wrong_shared_var;


struct right_shared_var_t {
    int variable{0};

    int inc() {
        return ++variable;
    }

    int dec() {
        return --variable;
    }
} right_shared_var;


struct super_shared_var_t {
    int variable{0};

    int inc() {
        return ++variable;
    }

    int dec() {
        return --variable;
    }
} super_shared_var;

struct ultim_shared_var_t {
    int variable{0};

    int inc() {
        return ++variable;
    }

    int dec() {
        return --variable;
    }
} ultim_shared_var;

//////////////////////////// DETAIL ////////////////////////////


template <class Functor>
static void mt_inc_dec(benchmark::State& state, Functor& f) {
    const auto func = [&f]() {
        for (unsigned i = 0; i < ::mt::iteratrions_count / 2; ++i) {
            const int var = f.inc();
            benchmark::DoNotOptimize(var);
        }
        for (unsigned i = 0; i < ::mt::iteratrions_count / 2; ++i) {
            const int var = f.dec();
            benchmark::DoNotOptimize(var);
        }
    };

    for (auto _ : state) {
        func();
    }

    // std::cerr << "variable == " << f.variable << '\n';
}

BENCHMARK_CAPTURE(mt_inc_dec, wrong_shared_var, wrong_shared_var)->Unit(benchmark::kMicrosecond)->ThreadRange(1, 8);
BENCHMARK_CAPTURE(mt_inc_dec, right_shared_var, right_shared_var)->Unit(benchmark::kMicrosecond)->ThreadRange(1, 8);
BENCHMARK_CAPTURE(mt_inc_dec, super_shared_var, super_shared_var)->Unit(benchmark::kMicrosecond)->ThreadRange(1, 8);
BENCHMARK_CAPTURE(mt_inc_dec, ultim_shared_var, ultim_shared_var)->Unit(benchmark::kMicrosecond)->ThreadRange(1, 8);
