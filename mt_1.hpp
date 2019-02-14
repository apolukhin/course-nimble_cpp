#include "util.hpp"

//////////////////////////// TASK 1 ////////////////////////////

struct naive_shared_var_t { // Do not modify!
    std::mutex  m;
    int variable{0};

    int inc() {
        std::lock_guard<std::mutex> l{m};
        return ++variable;
    }

    int dec() {
        std::lock_guard<std::mutex> l{m};
        return --variable;
    }
} naive_shared_var;

struct wrong_shared_var_t { // Do not modify!
    int variable{0};

    int inc() {
        return ++variable;
    }

    int dec() {
        return --variable;
    }
} wrong_shared_var;

struct super_shared_var_t {
    std::mutex  m;
    int variable{0};

    int inc() {
        std::lock_guard<std::mutex> l{m};
        return ++variable;
    }

    int dec() {
        std::lock_guard<std::mutex> l{m};
        return --variable;
    }
} super_shared_var;

struct ultim_shared_var_t {
    std::mutex  m;
    int variable{0};

    int inc() {
        std::lock_guard<std::mutex> l{m};
        return ++variable;
    }

    int dec() {
        std::lock_guard<std::mutex> l{m};
        return --variable;
    }
} ultim_shared_var;

//////////////////////////// DETAIL ////////////////////////////


template <class Functor>
static void mt_inc_dec(benchmark::State& state, Functor& f) {
    const std::size_t iterations_count = state.range();
    const auto func = [&f, iterations_count]() {
        for (unsigned i = 0; i < iterations_count / 2; ++i) {
            const int var = f.inc();
            benchmark::DoNotOptimize(var);
        }
        for (unsigned i = 0; i < iterations_count / 2; ++i) {
            const int var = f.dec();
            benchmark::DoNotOptimize(var);
        }
    };

    for (auto _ : state) {
        func();
    }

    // std::cerr << "variable == " << f.variable << '\n';
}

BENCH(mt_inc_dec, naive_shared_var, naive_shared_var)->Unit(benchmark::kMicrosecond)->Arg(8 << 10)->ThreadRange(1, 8);
BENCH(mt_inc_dec, wrong_shared_var, wrong_shared_var)->Unit(benchmark::kMicrosecond)->Arg(8 << 10)->ThreadRange(1, 8);
BENCH(mt_inc_dec, super_shared_var, super_shared_var)->Unit(benchmark::kMicrosecond)->Arg(8 << 10)->ThreadRange(1, 8);
BENCH(mt_inc_dec, ultim_shared_var, ultim_shared_var)->Unit(benchmark::kMicrosecond)->Arg(8 << 10)->ThreadRange(1, 8);
