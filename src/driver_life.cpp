#include <iostream>
#include <vector>
#include <fstream> 
#include <cstdio>
#include "../include/life.h"

int main (int argc, char *argv[])
{
    life::data inputs(argc, argv); //lê os comandos
    life::life_game celulas(inputs);

    bool condition = true;
    int generation = 0; // conta quantas gerações teve

    while(condition == true && inputs.get_maxgen() != generation)
    {   
        celulas.update( inputs );
	    if(celulas.extinct() || celulas.stable()) condition = false;
        generation++;
    }

    if(inputs.get_maxgen() == generation)
    {
        std::cout << "MAX GEN (Generation: " << generation << ")!\n";
    }

}
