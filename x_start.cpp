//////////////////////////// DETAIL ////////////////////////////

#include "0_conf.hpp"


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

        const std::size_t gap_between_columns = 3; // Separate benchmark names by at least 3 whitespaces

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

        std::size_t min_measures = static_cast<std::size_t>(-1);
        for (const auto& bench: suite_) {
            min_measures = (std::min)(min_measures, bench.measures.size());
        }

        for (unsigned i = 0; i < min_measures; ++i) {
            GetOutputStream() << std::setw(first_column_width) << std::left << suite_.front().measures[i].name  << std::right;

            for (const auto& bench: suite_) {
                const measure_t& measure = bench.measures[i];
                if (measure.complexity == benchmark::oNone) {
                    const double rel = suite_.front().measures[i].time * 1.0 / measure.time;
                    GetOutputStream() << std::setw(max_column_width) << std::fixed << std::setprecision(2) << rel;
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

        std::string measure_name = benchmark_name.substr(pos);
        for (const char* skip: {"iterations", "min_time"}) {
            const auto pos_iter = measure_name.find(skip);
            if (pos_iter != std::string::npos) {
                auto end = measure_name.find("/", pos_iter);
                if (end != std::string::npos) {
                    end = end - pos_iter;
                }
                measure_name.erase(pos_iter, end);
            }
        }

        while (measure_name.back() == '/') {
            measure_name.pop_back();
        }
        while (measure_name.front() == '/') {
            measure_name.erase(measure_name.begin());
        }
        do {
            const auto pos_dbl = measure_name.find("//");
            if (pos_dbl == std::string::npos) {
                break;
            }
            measure_name.erase(pos_dbl, 1);
        } while(1);

        suite_.back().measures.push_back(measure_t{
            std::move(measure_name),
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
