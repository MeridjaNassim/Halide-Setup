#!/bin/bash

while getopts p: flag
do
    case "${flag}" in
        p) halidePath=${OPTARG};;
    esac
done

printf "<< Executing make command >>\n"
printf "<< make sure you have pathToHeader and pathToLib env variables set"
make 

printf "<< Testing with a Vector size of 100 >>\n"

printf "<< PS : Halide version must run before C++ version because it needs to generate the test case with random values >>\n"

printf "\t<< Executing Halide version >>\n"
bin/halide_axpy 100 1

printf "\t<< Executing C++ version >>\n"
bin/cpp_axpy 

printf "\n<< Checking Results differences >>\n"
differences=`diff -s -q results/halide_results.txt results/cpp_results.txt`
printf "$differences"