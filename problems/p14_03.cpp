#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

uint64_t calculate_hits(uint64_t points, unsigned int seed) {
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    uint64_t hits = 0;

    for (uint64_t i = 0; i < points; ++i) {
        double x = dist(generator);
        double y = dist(generator);
        if (x * x + y * y <= 1.0) {
            hits++;
        }
    }
    return hits;
}

int main() {
    uint64_t num_points = 1000000000ULL;

    int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 4;
    }

    std::cout << "Num threads: " << num_threads << std::endl;
    std::cout << "Num points: " << num_points << std::endl;

    uint64_t pts_per_thread = num_points / num_threads;

    std::vector<unsigned int> seeds(num_threads);
    std::random_device rd;
    for (int i = 0; i < num_threads; ++i) {
        seeds[i] = rd();
    }

    std::vector<std::thread> threads;
    std::vector<uint64_t> results(num_threads);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, i]() {
            results[i] = calculate_hits(pts_per_thread, seeds[i]);
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    uint64_t num_hits = 0;
    for (auto &r : results) {
        num_hits += r;
    }

    double pi = 4.0 * num_hits / num_points;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    std::cout << "Pi approximation: " << std::setprecision(10) << pi
              << std::endl;
    std::cout << "Time: " << duration << std::endl;

    return 0;
}
