#include "mt_common.hpp"

#include <deque>

//////////////////////////// TASK 3 ////////////////////////////

template <class T>
class naive_queue_t {
    std::deque<T>           data_;
    std::mutex              mutex_;
    std::condition_variable cond_;

public:
    using value_type = T;

    void push(const T& val) {
        std::lock_guard<std::mutex> l{mutex_};
        data_.push_back(val);
        cond_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock{mutex_};
        while (data_.empty()) {
            cond_.wait(lock);
        }

        T res = data_.front();
        data_.pop_front();

        return res;
    }
};


template <class T>
class optim_queue_t {
    std::deque<T>           data_;
    std::mutex              mutex_;
    std::condition_variable cond_;

public:
    using value_type = T;

    void push(const T& val) {
        std::lock_guard<std::mutex> l{mutex_};
        data_.push_back(val);
        cond_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock{mutex_};
        while (data_.empty()) {
            cond_.wait(lock);
        }

        T res = data_.front();
        data_.pop_front();

        return res;
    }
};


template <class T>
class ultim_queue_t {
    std::deque<T>           data_;
    std::mutex              mutex_;
    std::condition_variable cond_;

public:
    using value_type = T;

    void push(const T& val) {
        std::lock_guard<std::mutex> l{mutex_};
        data_.push_back(val);
        cond_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock{mutex_};
        while (data_.empty()) {
            cond_.wait(lock);
        }

        T res = data_.front();
        data_.pop_front();

        return res;
    }
};

//////////////////////////// DETAIL ////////////////////////////

naive_queue_t<std::vector<int>> naive_queue;
optim_queue_t<std::vector<int>> optim_queue;
ultim_queue_t<std::vector<int>> ultim_queue;

template <class Queue, class T>
static void mt_queue(benchmark::State& state, Queue& q, const T& init_val) {
    const std::size_t iterations_count = 8 << 12;

    const std::size_t readers_count = state.range(0);
    const auto pop_in_loop = [&q, readers_count, iterations_count](){
        for (unsigned i = 0; i < iterations_count / readers_count; ++i) {
            const auto val = q.pop();
            benchmark::DoNotOptimize(val);
        }
    };

    const std::size_t writers_count = state.range(1);
    const auto push_in_loop = [&q, writers_count, &init_val, iterations_count](){
        for (unsigned i = 0; i < iterations_count / writers_count; ++i) {
            q.push(init_val);
        }
    };


    std::vector<std::thread> readers;
    readers.resize(readers_count);

    std::vector<std::thread> writers;
    writers.resize(writers_count - 1);

    for (auto _ : state) {
        state.PauseTiming();
        for (unsigned i = 0; i < readers_count; ++i){
            readers[i] = std::thread{pop_in_loop};
        }
        state.ResumeTiming();

        for (unsigned i = 0; i < writers_count - 1; ++i){
            writers[i] = std::thread{push_in_loop};
        }
        push_in_loop();


        for (auto& t : readers){
            t.join();
        }
        for (auto& t : writers){
            t.join();
        }
    }
}

const std::vector<int> init_value{1, 2, 42, 314};

BENCH(mt_queue, naive/rw, naive_queue, init_value)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->RangePair(1, 4, 1, 4); //->UseRealTime();
BENCH(mt_queue, optim/rw, optim_queue, init_value)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->RangePair(1, 4, 1, 4); //->UseRealTime();
BENCH(mt_queue, ultim/rw, ultim_queue, init_value)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->RangePair(1, 4, 1, 4); //->UseRealTime();
