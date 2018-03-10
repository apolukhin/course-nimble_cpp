#pragma once

#include <mutex>
#include <atomic>
#include <iostream>

#include <benchmark/benchmark.h>

namespace mt {
    constexpr auto iteratrions_count = 8 << 10;
}
