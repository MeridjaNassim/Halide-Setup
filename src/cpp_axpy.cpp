#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
/// default variables 
#define ALPHA 1
#define SIZE 4
#define UPPER_BOUND 12
#define LOWER_BOUND 0
/// helper function to generate random ints between lower and upper
void fillRandomInt(int * adr,int lower,int upper)
{
    int r = rand() % (upper - lower +1) + lower;
    *adr = r;
}
/// parses a string sequence of number into a vector of size (size)
void parseVect(const char *str, int * vect,int size)
{
    std::string st = str; 
    std::istringstream iss(st); 
    std::string s;
    int i = 0;
    while ( getline( iss, s, ' ' ) ) {
        std::cout << s.c_str() << std::endl;
        int val = atoi(s.c_str());
        vect[i]=val;
        i ++;
    }
}
/// reads a configuration from file
void readFromConfig(char * filename,int * size , int*alpha,int** vectX,int**vectY)
{
    std::ifstream configFile;
    configFile.open(filename);
    if(configFile.is_open())
    {
        std::string line;
        int i = 0;
        while(std::getline(configFile,line))
        {
            const char *  linestr = line.c_str();
            if(i==0)
            {
                *size = atoi(linestr);
                *vectX = (int*) malloc(sizeof(int) * (*size));
                *vectY= (int*) malloc(sizeof(int) * (*size));
            }
            if(i==1) *alpha = atoi(linestr);
            if(i==2)
                parseVect(linestr,*vectX,*size);
            if(i==3)
                parseVect(linestr,*vectY,*size);
            printf("%s\n",line.c_str());
            i++;
        }
    }
    configFile.close();
}
// saves results to a file
void saveResults(char * filaname,int* res,int size){
    std::ofstream savefile;
    savefile.open(filaname);
        for (int i = 0; i < size; i++)
        {
            savefile << res[i] << " ";
        }
        savefile.close();
}
// implementation of axpy
void axpy(int alpha, int* vectx,int* vecty,int* res,int size) 
{
    for (size_t i = 0; i < size; i++)
    {
        res[i] = alpha * vectx[i] + vecty[i];
    }
    
}
/// helper function to print
void printVect(int * vect, int size, char * title)
{
    std::cout << title << std::endl;
    std::cout << "[ ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << vect[i] << " ";
    
    }
    std::cout << "]" << std::endl;
    
    
}
int main(int argc, char const *argv[])
{
    int size = SIZE;
    int alpha = ALPHA;
    int useRandom = 1;
    int lower = LOWER_BOUND;
    int upper = UPPER_BOUND;
    int * vectX  ; 
    int * vectY  ;
    int random = 0;
    srand(time(0));
    clock_t initstart = clock();
    
    if(random)
    {
         vectX  =(int*) malloc(sizeof(int) * size); 
         vectY  =(int*) malloc(sizeof(int) * size);
   
        for (size_t i = 0; i < size; i++)
        {
            fillRandomInt(&vectX[i],lower,upper);
            fillRandomInt(&vectY[i],lower,upper);
        }
    }
    else
    {
        readFromConfig("./data/config.txt",&size,&alpha,&vectX,&vectY);
    }
    
    clock_t initend = clock();
    std::cout << "Init took : " << (initend - initstart) << " clock cycles" <<std::endl; 
    printVect(vectX,size,"VectX");
    printVect(vectY,size,"VectY");
    
    int * res  =(int*) malloc(sizeof(int) * size);
    clock_t execStart = clock();
    axpy(alpha,vectX,vectY,res,size);
    clock_t execEnd = clock();   
    std::cout << "Exec took : " << (execEnd - execStart) << " clock cycles" <<std::endl; 
    
    printVect(res,size,"Result");
    saveResults("./results/cpp_results.txt",res,size);
    free(vectX);
    free(vectY);
    return 0;
}
