#include "parallel_counter.h"
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include <iostream>

// Select version based on defined flags
size_t PositiveCounter::count_positive(const std::vector<double>& array, size_t num_threads) {
    
#ifdef LINEAR_MODE
    std::cout << "[MODE: LINEAR VERSION]" << std::endl;
    return count_positive_linear(array);
    
#elif defined(AUTO_CORES)
    size_t cores = std::thread::hardware_concurrency();
    std::cout << "[MODE: AUTO-DETECT CORES = " << cores << "]" << std::endl;
    return count_positive_parallel(array, cores);
    
#else
    std::cout << "[MODE: PARALLEL VERSION]" << std::endl;
    return count_positive_parallel(array, num_threads);
    
#endif
}

// Linear version
size_t PositiveCounter::count_positive_linear(const std::vector<double>& array) {
    size_t count = 0;
    for (double value : array) {
        if (value > 0.0) {
            ++count;
        }
    }
    return count;
}

// Parallel version
size_t PositiveCounter::count_positive_parallel(const std::vector<double>& array, 
                                                       size_t num_threads) {
    if (array.empty()) {
        return 0;
    }
    
    // Determine number of threads
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) {
            num_threads = 4;
        }
    }
    
    num_threads = std::min(num_threads, array.size());
    
    // A priori partitioning
    size_t block_size = array.size() / num_threads;
    
    std::vector<std::packaged_task<size_t()>> tasks;
    std::vector<std::future<size_t>> futures;
    
    // Create packaged_task for each block
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start_index = i * block_size;
        size_t end_index = (i == num_threads - 1) ? array.size() : start_index + block_size;
        
        std::packaged_task<size_t()> task(
            [&array, start_index, end_index]() -> size_t {
                return count_positive_in_range(array, start_index, end_index);
            }
        );
        
        futures.push_back(task.get_future());
        std::thread(std::move(task)).detach();
    }
    
    // Collect results
    size_t total_positives = 0;
    for (auto& future : futures) {
        total_positives += future.get();
    }
    
    return total_positives;
}

size_t PositiveCounter::count_positive_in_range(const std::vector<double>& array, 
                                                       size_t start, size_t end) {
    size_t count = 0;
    for (size_t i = start; i < end; ++i) {
        if (array[i] > 0.0) {
            ++count;
        }
    }
    return count;
}
