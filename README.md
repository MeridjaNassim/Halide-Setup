# Implementation of AXPY with Halide and C++

This is a basic implementation of the axpy specification from BLAS (Basic Linear Algebra Subprograms) Using Halide and Vanila C++
![equation]()

## 1.2. Build

1. First thing you need to do is clone this repository
```
git clone 
```
2. then more to the project directory:
```
cd   
```

3. make sure to export 2 environment variables:
```
export pathToHeader=<the absolute path in your system to Halide.h>
export pathToLib = <the absolute path in your system to libHalide.so and libHalide.so.12>
```
4. Build the binaries for Halide and C++ implementation by running 
```
make
```
5. Execute the comparaison script between implementations by running
```
sh ./compare.sh
```
## About the project structure
- **bin** : will contain the binaries built from running make for Halide and C++ named respectively : halide_axpy and cpp_axpy
- **data** : will contain the randomly generated instance by Halide that will also be used in C++ program (to have same results)
- **results** : individual results for both the Halide run and the C++ run
- **src** : Source code for both Halide implementation and C++ implementation
- **logs** : Extra folder that contains the logs generated while building LLVM and Halide from sources

### this Readme will be improved further