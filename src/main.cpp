#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "parallel_counter.h"

void print_program_info() {
    std::cout << "==========================================" << std::endl;
    std::cout << "Group Number: 61" << std::endl;
    std::cout << "Task: Count positive elements in array" << std::endl;
    std::cout << "Parallelization: A priori partitioning with packaged_task" << std::endl;
    std::cout << "Array element type: double" << std::endl;
    std::cout << "==========================================" << std::endl;
}

int main(int argc, char* argv[]) {
    print_program_info();
    
    std::vector<double> array;
    size_t num_threads = 0;

#ifndef AUTO_CORES
#ifndef LINEAR_MODE
    if (argc > 1) {
        try {
            num_threads = std::stoul(argv[1]);
            std::cout << "Threads specified: " << num_threads << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: invalid thread count. Using auto-detection." << std::endl;
            num_threads = 0;
        }
    }
#endif
#endif
    std::cout << "Enter array elements (double type, space-separated): ";
    std::string array_input;
    std::getline(std::cin, array_input);
    
    std::istringstream iss(array_input);
    double value;
    while (iss >> value) {
        array.push_back(value);
    }
    
    if (array.empty()) {
        std::cout << "Array is empty." << std::endl;
        return 0;
    }
    
    std::cout << "Array size: " << array.size() << std::endl;
    
    size_t positive_count = PositiveCounter::count_positive(array, num_threads);
    
    std::cout << "==========================================" << std::endl;
    std::cout << "Result: " << positive_count << " positive elements" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}
