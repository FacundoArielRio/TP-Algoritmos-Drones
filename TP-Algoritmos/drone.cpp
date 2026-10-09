#include <iostream>
#include <cstdio>
#include "include/drone.h"

using namespace std;

void inicializarGrilla(Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    for (int i = 0; i < TAM_GRILLA; i++)
    {
        for (int j = 0; j < TAM_GRILLA; j++)
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

bool validarInstrucciones(OrdenArchivo registros[], int cantidad, int &idxDespegue)
{
    int despegues=0;
    int finales=0;
    idxDespegues=-1;
    for(int i=0; i<cantidad; i++)
    {
        if(registros[i].x<0||registros[i].x>=TAM_GRILLA||registros[i].y<0||registros[i].y>=TAM_GRILLA)
        {
            cout << "Las coordenadas (" << registros[i].x << ";" << registros[i].y << ") estan fuera de rango.\n" << endl;
            return false;
        }

        if(registros[i].despegue==true)
        {
            despegues++;
            idxDespegue=i;
            if(registros[i].soltarGranada1==true||registros[i].soltarGranada2==true||registros[i].ataqueKamikaze==true)
            {

            }

        }
    }
}

bool validarRuta(OrdenArchivo registros[], int cantidad, int &idxDespegue)
{
    if(cantidad<=0)
    {
        cout << "No hay registros para validad.\n" << endl;
        return false;
    }

    if(validarInstrucciones(registros, cantidad, idxDespegue)==false)
    {
        return false;
    }

    if(validarRecorrido(registros, cantidad, idxDespegue)==false)
    {
        return false;
    }
}

bool cargarEnMemoria(char rutaArchivo[], Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    FILE *f = fopen(rutaArchivo,"rb");
    if(f == NULL)
    {
        cout << "No se puedo abrir el archivo \n" << rutaArchivo << endl;
        return false;
    }

    static OrdenArchivo buffer[TAM_GRILLA * TAM_GRILLA];
    int cantidad=0;
    while (fread(&buffer[cantidad], sizeof(OrdenArchivo), 1, f)==1)
    {
        cantidad++;
    }
    fclose(f);

    int idxDespegue=-1;
    if (validarRuta(buffer, cantidad, idxDespegue)==false)
    {
        cout << "El archivo no cumple las reglas de vuelo. No se cargo en memoria.\n" << endl;
        return false;
    }

    inicializarGrilla(grilla);

    for(int i=0; i<cantidad; i++)
    {
        int x = buffer[i].x;
        int y = buffer[i].y;

        grilla[x][y].espera=buffer[i].espera;
        grilla[x][y].soltarGranada1 = buffer[i].soltarGranada1;
        grilla[x][y].soltarGranada2 = buffer[i].soltarGranada2;
        grilla[x][y].ataqueKamikaze = buffer[i].ataqueKamikaze;
        grilla[x][y].aterrizaje = buffer[i].aterrizaje;
        grilla[x][y].despegue = buffer[i].despegue;
        grilla[x][y].siguientex = buffer[i].siguientex;
        grilla[x][y].siguientey = buffer[i].siguientey;
    }
    cout << "Archivo cargado en memoria exitosamente. Cantidad de registros: " << cantidad << endl;
}
