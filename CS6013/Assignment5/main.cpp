#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <thread>
#include <vector>

template<typename T>
struct Result {
    T data_;
    int duration_;
};

// part 1
template<typename T>
auto parallel_sum_std(T a[], size_t N, size_t num_threads) {
    num_threads %= N;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<T> sumArr(num_threads, 0);
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    std::atomic<T> sum = 0;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, a, i] () {
            size_t startIdx = (i * N / num_threads);
            size_t endIdx = (i * N / num_threads) + N / num_threads;

            for (size_t j = startIdx; j < endIdx; ++j) {
                sumArr[i] += a[j];
            }
            sum += sumArr[i];
        });
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    if (N % num_threads > 0) {
        for (size_t i = N; i < N; ++i) {
            sum += a[i];
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    Result<T> result{};
    result.data_ = sum;
    result.duration_ = duration_cast<std::chrono::microseconds>(stop - start).count();

    return result;
}

// part 2
template<typename T>
auto parallel_sum_omp1(T a[], size_t N, size_t num_threads) {
    num_threads %= N;
    std::atomic<T> sum = 0;
    std::vector<T> partialSums(num_threads, 0);

    auto start = std::chrono::high_resolution_clock::now();
    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        size_t startIdx = id * N / num_threads;
        size_t endIdx = (id * N / num_threads) + N / num_threads;

        for (size_t j = startIdx; j < endIdx; ++j) {
            partialSums[id] += a[j];
        }
    }
#pragma omp single
    {
        for (int i = 0; i < num_threads; ++i) {
            sum += partialSums[i];
        }

        if (N % num_threads > 0) {
            for (size_t i = N; i < N; ++i) {
                sum += a[i];
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    Result<T> result{};
    result.data_ = sum;
    result.duration_ = duration_cast<std::chrono::microseconds>(stop - start).count();

    return result;
}

// part 3
template<typename T>
auto parallel_sum_omp_builtin(T a[], size_t N, size_t num_threads) {
    auto start = std::chrono::high_resolution_clock::now();

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);
    int sum = 0;

#pragma omp parallel for num_threads(threads) reduction(+:sum)
    {
        for (size_t i = 0; i < N; ++i) {
            sum += a[i];
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    Result<T> result{};
    result.data_ = sum;
    result.duration_ = duration_cast<std::chrono::microseconds>(stop - start).count();

    return result;
}

int main() {
    return 0;
}
