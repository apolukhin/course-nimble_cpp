////////////////////////////////////////////////////////
/// You might want to disable the CPU frequency scaling while running the benchmark:
///
///     sudo apt-get install linux-tools-common             # sudo apt-get install linux-tools-3.19.0-80-generic
///     sudo cpupower frequency-set --governor performance
///     ./mybench
///     sudo cpupower frequency-set --governor powersave
///
///


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





//////////////////////////// DETAIL ////////////////////////////
#include <iostream>
#include <iomanip>

namespace benchmark {
    std::string GetBigOString(BigO complexity);
}

class SuiteComparingConsoleReporter: public ::benchmark::ConsoleReporter {
    struct measure_t {
        std::string         name;
        int                 time;
        ::benchmark::BigO   complexity;
    };

    struct bench_t {
        std::string             name;
        std::vector<measure_t>  measures;
    };
    std::vector<bench_t>   suite_;

    void PrintSuiteInfo() const {
        if (suite_.empty()) {
            return;
        }

        GetOutputStream() << "*** Results:\n";

        constexpr std::size_t gap_between_columns = 3; // Separate benchmark names by at least 3 whitespaces

        std::size_t first_column_width = sizeof("measure") - 1;
        for (const auto& m: suite_.front().measures) {
            first_column_width = (std::max)(first_column_width, m.name.size());
        }
        first_column_width += gap_between_columns;

        std::size_t max_column_width = 0;
        for (const auto& bench: suite_) {
            max_column_width = (std::max)(max_column_width, bench.name.size());
        }
        max_column_width += gap_between_columns;

        GetOutputStream() << std::setw(first_column_width) << std::left << "measure" << std::right;
        for (const auto& bench: suite_) {
            GetOutputStream() << std::setw(max_column_width) << bench.name;
        }

        GetOutputStream() << '\n';

        std::size_t min_measures = 99999;
        for (const auto& bench: suite_) {
            min_measures = (std::min)(min_measures, bench.measures.size());
        }

        for (unsigned i = 0; i < min_measures; ++i) {
            GetOutputStream() << std::setw(first_column_width) << std::left << suite_.front().measures[i].name  << std::right;

            for (const auto& bench: suite_) {
                const measure_t& measure = bench.measures[i];
                if (measure.complexity == benchmark::oNone) {
                    const double perc_from_initial =  measure.time * 1.0 / suite_.front().measures[i].time;
                    GetOutputStream() << std::setw(max_column_width) << std::setprecision(2) << perc_from_initial;
                } else {
                    GetOutputStream() << std::setw(max_column_width) << ::benchmark::GetBigOString(measure.complexity);
                }
            }
            GetOutputStream() << '\n';
        }

        GetOutputStream() << "***\n\n";
    }

    void AddNewBenchmarkToSuite(const std::string& benchmark_name) {
        suite_.emplace_back();
        suite_.back().name = benchmark_name.substr(0, benchmark_name.find('/'));
    }

    void StartNewSuite() {
        suite_.clear();
    }

    void AddTimeMeasureToLastBenchmark(const std::string& benchmark_name, int t) {
        auto pos = benchmark_name.find('/');
        if (pos != std::string::npos) {
            ++ pos;
        }

        suite_.back().measures.push_back(measure_t{
            benchmark_name.substr(pos),
            t,
            ::benchmark::oNone
        });
    }

    void AddBigOMeasureToLastBenchmark( ::benchmark::BigO big_o) {
        suite_.back().measures.push_back(measure_t{
            "BigO",
            0,
            big_o
        });
    }

    void CheckForBenchChanges(const std::string& benchmark_name) {
        const bool bench_changed = (suite_.empty() || benchmark_name.find(suite_.back().name) == std::string::npos);
        if (!bench_changed) {
            return;
        }

        GetOutputStream() << '\n';

        if (benchmark_name.find("naive") != std::string::npos) {
            // Bench suite changed
            PrintSuiteInfo();
            StartNewSuite();
        }

        AddNewBenchmarkToSuite(benchmark_name);
    }

    void ReportRuns(const std::vector<Run>& reports) override {
        auto& first_report = reports.front();
        CheckForBenchChanges(first_report.benchmark_name);

        for (auto& r: reports) {
            if (!r.report_big_o && !r.report_rms) {
                AddTimeMeasureToLastBenchmark(r.benchmark_name, static_cast<int>(first_report.GetAdjustedRealTime()));
            } else if (r.report_big_o) {
                AddBigOMeasureToLastBenchmark(r.complexity);
            }
        }

        ::benchmark::ConsoleReporter::ReportRuns(reports);
    }

public:
    SuiteComparingConsoleReporter() {
        StartNewSuite();
    }

    ~SuiteComparingConsoleReporter() {
        PrintSuiteInfo();
    }
};

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }

    SuiteComparingConsoleReporter rep;
    ::benchmark::RunSpecifiedBenchmarks(&rep);
}
