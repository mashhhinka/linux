#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <numeric>

void partial_sum(const std::vector<int>& arr, size_t start, size_t end, long long& result) {
    result = std::accumulate(arr.begin() + start, arr.begin() + end, 0LL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <M>\n";
        return 1;
    }

    size_t N = std::stoull(argv[1]);
    size_t M = std::stoull(argv[2]);

    // Step 1: Initialize the array with random values
    std::vector<int> array(N);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);
    for (size_t i = 0; i < N; ++i) {
        array[i] = dist(rng);
    }

    // Step 2: Compute the summary using a single thread
    auto start_time = std::chrono::high_resolution_clock::now();
    long long single_thread_sum = std::accumulate(array.begin(), array.end(), 0LL);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> single_thread_duration = end_time - start_time;

    // Step 3: Compute the summary using multiple threads
    start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    std::vector<long long> partial_results(M, 0);

    size_t chunk_size = N / M;
    for (size_t i = 0; i < M; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == M - 1) ? N : start + chunk_size;
        threads.emplace_back(partial_sum, std::cref(array), start, end, std::ref(partial_results[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    long long multi_thread_sum = std::accumulate(partial_results.begin(), partial_results.end(), 0LL);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> multi_thread_duration = end_time - start_time;

    std::cout << "Time spent without threads: " << single_thread_duration.count() << " seconds\n";
    std::cout << "Time spent with " << M << " threads: " << multi_thread_duration.count() << " seconds\n";

    if (single_thread_sum != multi_thread_sum) {
        std::cerr << "Error: Results do not match!\n";
    }

    return 0;
}
