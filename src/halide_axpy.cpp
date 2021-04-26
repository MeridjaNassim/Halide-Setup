#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

/// we only need to import Halide
#include <Halide.h>

/// default variables 
#define ALPHA 1
#define SIZE 4
#define UPPER_BOUND 12
#define LOWER_BOUND 0


void writeConfigToFile(char * filaname,int size,int alpha,Halide::Buffer<int> vectorX,Halide::Buffer<int> vectorY){
    std::ofstream savefile;
    savefile.open(filaname);
        savefile << size << std::endl;
        
        savefile << alpha << std::endl;
        for (int i = 0; i < vectorX.width(); i++)
        {
            savefile << vectorX(i) << " ";
        }
        savefile << std::endl;
        for (int i = 0; i < vectorY.width(); i++)
        {
            savefile << vectorY(i) << " ";
        }
        savefile.close();
}
void saveResults(char * filaname,Halide::Buffer<int> res){
    std::ofstream savefile;
    savefile.open(filaname);
        for (int i = 0; i < res.width(); i++)
        {
            savefile << res(i) << " ";
        }
        savefile.close();
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    int size = SIZE;
    int alpha = ALPHA;
    if(argc > 1)
    {
        size = atoi(argv[1]);
        alpha = atoi(argv[2]);        
    }
    int useRandom = 1;
    // variables to fill the objects
    Halide::Var sizeFill;
    // Pipeline to fill the matrixes
    Halide::Func fillVectX,fillVectY;
    if(useRandom)
    {
    Halide::Expr seed(rand());
    fillVectX(sizeFill) = Halide::cast<int>(((Halide::random_int(seed)) % (UPPER_BOUND - LOWER_BOUND + 1)) + LOWER_BOUND);
    fillVectY(sizeFill) = Halide::cast<int>(((Halide::random_int(seed)) % (UPPER_BOUND - LOWER_BOUND + 1)) + LOWER_BOUND);
    
    }

    // Add parallalisation using the x_fill to the Halide fillMatrix pipline
    fillVectX.parallel(sizeFill);
    fillVectY.parallel(sizeFill);
    clock_t initstart = clock();
    //Declare and initialize the buffers of matrices
    Halide::Buffer<int> vectorX = fillVectX.realize(size);
    Halide::Buffer<int> vectorY = fillVectY.realize(size);
    
    writeConfigToFile("./data/config.txt",size,alpha,vectorX,vectorY);
    clock_t initend = clock();
    std::cout << "Init took : " << (initend - initstart) << " clock cycles" <<std::endl; 
    /// printing tha matrices
    int debug = 1;
    if(debug)
    {
        std::cout << "Vect X" << std::endl;
        for (int i = 0; i < vectorX.width(); i++)
        {
            std::cout << vectorX(i) << " ";
        }
        std::cout << std::endl;
    std::cout << "Vect Y" << std::endl;
        for (int i = 0; i < vectorY.width(); i++)
        {
            std::cout << vectorY(i) << " ";
        }
    } 
    std::cout << std::endl;
    
    // Add definition to the Halide gemv pipline
    Halide::Var Y;
    Halide::Func axpy;
    axpy(Y) = alpha *  vectorX(Y)  +  vectorY(Y);
    axpy.parallel(Y);
    clock_t execStart = clock();
    
     // executing the gemv pipeline and saving the results in the reslut buffer
    Halide::Buffer<int> result = axpy.realize(size);
    clock_t execEnd = clock();
    std::cout << "Exec took : " << (execEnd - execStart) << " clocks cycles" <<std::endl; 
    std::cout << std::endl;
    if(debug)
    {
        std::cout << "Result" << std::endl;
        for (int i = 0; i < result.width(); i++)
        {
            std::cout << result(i) << " ";
        }
    
    }
    saveResults("./results/halide_results.txt",result);
    return 0;
}
