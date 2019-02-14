#pragma once

////////////////////////////////////////////////////////
/// You might want to disable the CPU frequency scaling while running the benchmark:
///
///     sudo apt-get install linux-tools-common             # sudo apt-get install linux-tools-3.19.0-80-generic
///     sudo cpupower frequency-set --governor performance
///     ./mybench
///     sudo cpupower frequency-set --governor powersave
///


////////////////////////////////////////////////////////
/// Those args will be applied to all the benchmarks runs.
/// Useful values are
///     ->Iterations(2000)
///     ->MinTime(0.1)
///     ->Unit(kMicrosecond)
///     ->Unit(kMillisecond)

#define COURSE_GLOBAL_ARGS() ->Iterations(50)


////////////////////////////////////////////////////////
/// Comment out following headers to disable benchmarks:


////////////////////////////// Section 1
#include "algorithm_1.hpp"
#include "algorithm_2.hpp"
#include "algorithm_3.hpp"
#include "algorithm_4.hpp"
#include "algorithm_5.hpp"
#include "algorithm_6.hpp"
#include "algorithm_x.hpp"

////////////////////////////// Section 2
#include "container_1.hpp"
#include "container_2.hpp"
#include "container_3.hpp"

////////////////////////////// Section 2, vector features
#include "container_4.hpp"
#include "container_5.hpp"

////////////////////////////// Section 2, associative
#include "container_6.hpp"
#include "container_7.hpp"


////////////////////////////// Section 3, multithreading
#include "mt_1.hpp"
#include "mt_2.hpp"
#include "mt_3.hpp"
