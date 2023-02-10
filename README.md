# SparseMatrix
First homework for CDA5110. The core implementation of the sparse matrix class is in the file `sparse.hpp`. The file `main.cpp` generates sparse matrices from the .mtx files, multiplies multiplies their 1000th power by a vector, and prints out the runtime.

## Build Instructions

Starting from the main project directory:

```bash
mkdir build
cd build
cmake ..
make
./main
```

The unit tests, which verify output against truth values generated using numpy, will be built if the "GTest" package is present on the system. To run the tests from 'build':

```bash
test/test_1
```
