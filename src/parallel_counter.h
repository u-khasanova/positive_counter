#ifndef PARALLEL_COUNTER_H
#define PARALLEL_COUNTER_H

#include <vector>
#include <future>

class PositiveCounter {
public:
    static size_t count_positive(const std::vector<double>& array, size_t num_threads = 0);
    static size_t count_positive_linear(const std::vector<double>& array);
    static size_t count_positive_parallel(const std::vector<double>& array, size_t num_threads = 0);

private:
    static size_t count_positive_in_range(const std::vector<double>& array, 
                                         size_t start, size_t end);
};

#endif