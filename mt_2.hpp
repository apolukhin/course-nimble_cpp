#include "mt_common.hpp"

//////////////////////////// TASK 2 ////////////////////////////

struct naive_read_write_var_t {
    std::atomic<int> variable{0};

    int load() const {
        return variable;
    }

    void store(int i) {
        variable = i;
    }
} naive_read_write_var;


struct optim_read_write_var_t {
    std::atomic<int> variable{0};

    int load() const {
        return variable.load();
    }

    void store(int i) {
        variable.store(i);
    }
} optim_read_write_var;


//////////////////////////// DETAIL ////////////////////////////

enum class bench_t {
    LOAD, STORE, LOAD_STORE
};

template <class Functor>
static void mt_load_store(benchmark::State& state, bench_t t, Functor& f) {
    const std::size_t iteratrions_count = 8 << 10;
    const auto do_stores = [&f,iteratrions_count](){
        for (unsigned i = 0; i < iteratrions_count; ++i) {
            f.store(i);
        }
    };
    const auto do_loads = [&f,iteratrions_count](){
        for (unsigned i = 0; i < iteratrions_count; ++i) {
            const int val = f.load();
            benchmark::DoNotOptimize(val);
        }
    };

    switch (t) {
    case bench_t::LOAD: for (auto _ : state) {  do_loads();     do_loads(); do_loads();     do_loads();     }; break;
    case bench_t::STORE:for (auto _ : state) { do_stores();    do_stores(); do_stores();    do_stores();    }; break;
    default:            for (auto _ : state) {  do_loads();     do_loads(); do_loads();     do_stores();    }; break;
    }

}

BENCH(mt_load_store, naive_LOAD, bench_t::LOAD, naive_read_write_var)->ThreadRange(1, 8);
BENCH(mt_load_store, optim_LOAD, bench_t::LOAD, optim_read_write_var)->ThreadRange(1, 8);
BENCH(mt_load_store, naive_STORE, bench_t::STORE, naive_read_write_var)->ThreadRange(1, 8);
BENCH(mt_load_store, optim_STORE, bench_t::STORE, optim_read_write_var)->ThreadRange(1, 8);
BENCH(mt_load_store, naive_MIXED, bench_t::LOAD_STORE, naive_read_write_var)->ThreadRange(1, 8);
BENCH(mt_load_store, optim_MIXED, bench_t::LOAD_STORE, optim_read_write_var)->ThreadRange(1, 8);
