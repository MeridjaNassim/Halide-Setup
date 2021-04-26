all: bin/halide_axpy bin/cpp_axpy
bin/halide_axpy: src/halide_axpy.cpp
	g++ src/halide_axpy.cpp -g -I $(pathToHeader) -L $(pathToLib) -lHalide -lpthread -ldl -o bin/halide_axpy -std=c++11

bin/cpp_axpy: src/cpp_axpy.cpp
	g++ src/cpp_axpy.cpp -o bin/cpp_axpy

