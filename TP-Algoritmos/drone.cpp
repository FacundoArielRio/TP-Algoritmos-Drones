#include <iostream>
#include <cstdio>
#include <cstring>
#include "include/drone.h"

using namespace std;

void inicializarGrilla(Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    for(int i=0;i<TAM_GRILLA;i++)
    {
        for(int j=0; j<TAM_GRILLA;j++)
        {
            grilla[i][j].espera = 0;
            grilla[i][j].soltarGranada1 = false;
            grilla[i][j].soltarGranada2 = false;
            grilla[i][j].ataqueKamikaze = false;
            grilla[i][j].aterrizaje = false;
            grilla[i][j].despegue = false;
            grilla[i][j].siguientex = 0;
            grilla[i][j].siguientey = 0;
        }
    }
}
