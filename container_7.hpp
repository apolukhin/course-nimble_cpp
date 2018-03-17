#include "util.hpp"

#include <vector>
#include <string>


//////////////////////////// TASK 7 ////////////////////////////

using vs_type = std::vector<std::string>; // Do not modify

const std::string s_base {
    "A variable x whose name appears as a potentially-evaluated expression ex is odr-used by ex unless applying "
    "the lvalue-to-rvalue conversion (7.1) to x yields a constant expression (8.6) that does not invoke any non-trivial "
    "functions and, if x is an object, ex is an element of the set of potential results of an expression e, where "
    "either the lvalue-to-rvalue conversion (7.1) is applied to e, or e is a discarded-value expression (8.2)."
    ""
    "A structured binding is odr-used if it appears as a potentially-evaluated expression."
};

// Do not change
static vs_type generate_naive(std::size_t elements_count) {
    vs_type v;

    for (unsigned i = 0; i < elements_count; ++i) {
        std::string s {s_base};
        s += static_cast<char>(elements_count % 256);
        elements_count >>= 1;
        s += static_cast<char>(elements_count % 256);

        v.push_back(s);
    }

    return v;
}

static vs_type filter_naive(vs_type generated) {
    vs_type dest;
    dest.resize(generated.size());

    const auto it = std::copy_if(
        generated.begin(),
        generated.end(),
        dest.begin(),
        [](const std::string& v) { return std::hash<std::string>{}(v) & 1; }
    );

    dest.erase(it, dest.end());

    return dest;
}



static vs_type generate_optim(std::size_t elements_count) {
    vs_type v;

    for (unsigned i = 0; i < elements_count; ++i) {
        std::string s {s_base};
        s += static_cast<char>(elements_count % 256);
        elements_count >>= 1;
        s += static_cast<char>(elements_count % 256);

        v.push_back(s);
    }

    return v;
}

static vs_type filter_optim(vs_type generated) {
    vs_type dest;
    dest.resize(generated.size());

    const auto it = std::copy_if(
        generated.begin(),
        generated.end(),
        dest.begin(),
        [](const std::string& v) { return std::hash<std::string>{}(v) & 1; }
    );

    dest.erase(it, dest.end());

    return dest;
}

//////////////////////////// DETAIL ////////////////////////////

template <class Filter, class Generator>
static void mesure_generate_and_filter(benchmark::State& state, Filter filter, Generator generator) {
    const std::size_t elements_count = state.range(0);
    for (auto _ : state) {
        vs_type dest = filter(generator(elements_count));

        state.PauseTiming();
        if (filter != filter_naive && generator != generate_naive) {
            if(dest != filter_naive(generate_naive(elements_count))) {
                throw std::runtime_error("values missmatch");
            }
        }
        state.ResumeTiming();
        benchmark::DoNotOptimize(dest);
    }
}

BENCH(mesure_generate_and_filter, generate_and_filter_naive, &filter_naive, &generate_naive)->Range(8, 8<<10);
BENCH(mesure_generate_and_filter, generate_and_filter_optim, &filter_optim, &generate_optim)->Range(8, 8<<10);
