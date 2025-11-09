# Count Positive Elements in Array

## Information
- **Group Number**: 61
- **Task**: Count positive elements in double array
- **Parallelization**: A priori partitioning with `packaged_task`
- **Element Type**: double

## Build Instructions

### Prerequisites
- C++17 compatible compiler (g++ 7.0+ or clang++ 5.0+)
- Make build system

### Building the Project

```bash
# Clone or download the project
cd positive_counter

# Build different versions:
make parallel      # Parallel version (default)
make linear        # Linear version only
make auto_cores    # Auto-detect CPU cores

# Clean build artifacts
make clean
```

## Usage Examples

### Different Build Modes

```bash
# Linear version (single-threaded) - ignores thread count
make linear && ./bin/positive_counter
make linear && ./bin/positive_counter 4    # Thread count ignored

# Parallel version with specific threads
make parallel && ./bin/positive_counter 4

# Auto-detect CPU cores - ignores thread count
make auto_cores && ./bin/positive_counter
make auto_cores && ./bin/positive_counter 4    # Thread count ignored
```

## Program Output Examples

### Linear Version
```
==========================================
Group Number: 61
Task: Count positive elements in array
Parallelization: A priori partitioning with packaged_task
Array element type: double
==========================================
Enter array elements (double type, space-separated): 1.5 -2.3 4.7 -0.5 3.2
Array size: 5
[MODE: LINEAR VERSION]
==========================================
Result: 3 positive elements
==========================================
```

### Parallel Version
```
==========================================
Group Number: 61
Task: Count positive elements in array
Parallelization: A priori partitioning with packaged_task
Array element type: double
==========================================
Threads specified: 4
Enter array elements (double type, space-separated): 1.5 -2.3 4.7 -0.5 3.2
Array size: 5
[MODE: PARALLEL VERSION]
Using 4 threads
==========================================
Result: 3 positive elements
==========================================
```

### Auto-Cores Version
```
==========================================
Group Number: 61
Task: Count positive elements in array
Parallelization: A priori partitioning with packaged_task
Array element type: double
==========================================
Enter array elements (double type, space-separated): 1.5 -2.3 4.7 -0.5 3.2
Array size: 5
[MODE: AUTO-DETECT CORES = 12]
Using 8 threads
==========================================
Result: 3 positive elements
==========================================
```
