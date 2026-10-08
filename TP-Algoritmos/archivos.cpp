#include <iostream>
#include <cstdio>
#include <cstring>
#include "include/archivos.h"

using namespace std;

void crearArchivoAtaque()
{
    char ruta[256];
    char nombre[128];
    char rutaFinal[384] = "";

    cout << "Crear archivo de ataque nuevo \n" << endl;
    cout << "Ingrese la ruta del archivo a crear: \n" << endl;
    cin >> ruta;
    cout << "Ingrese el nombre del archivo a crear: \n" << endl;
    cin >> nombre;

    strcat(rutaFinal,ruta);
    strcat(rutaFinal,"/");
    strcat(rutaFinal,nombre);
    strcat(rutaFinal,".dat");

    FILE *f = fopen(rutaFinal,"wb");
    if (f == NULL)
    {
        cout << "\nNo se pudo crear el archivo en: \n" << rutaFinal << endl;
        return;
    }

    cout << "Archivo creado. Ingresar los registros:\n" << endl;

    char continuar;
    int contador=0;

    do
    {
        OrdenArchivo reg;

        cout << "Registro " << contador+1 << "\n" << endl;

        cout << "Coordenada X entre 0 y 199: \n" << endl;
        cin >> reg.x;
        cout << "Coordenada Y entre 0 y 199: \n" << endl;
        cin >> reg.y;

        reg.soltarGranada1 = false;
        reg.soltarGranada2 = false;
        reg.ataqueKamikaze = false;
        reg.aterrizaje = false;
        reg.despegue = false;

        int accion;
        cout << "Accion a realizar en (" << reg.x << ";" << reg.y << "):\n" << endl;

        cout << "  0 = Ninguna (solo moverse)\n";
        cout << "  1 = Despegue\n";
        cout << "  2 = Soltar Granada 1\n";
        cout << "  3 = Soltar Granada 2\n";
        cout << "  4 = Ataque Kamikaze\n";
        cout << "  5 = Aterrizaje\n";
        cout << "Elija una opcion de 0 a 5: ";
        cin >> accion;

        switch(accion)
        {
            case 0:
                break;
            case 1:
                reg.despegue = true;
            break;
            case 2:
                reg.soltarGranada1 = true;
                break;
            case 3:
                reg.soltarGranada2 = true;
                break;
            case 4:
                reg.ataqueKamikaze = true;
                break;
            case 5:
                reg.aterrizaje = true;
                break;
            default:
                cout << "Error: debe de elegir una opcion del 0 al 5.\n" << endl;
            break;
        }

        cout << "Segundos de espera: \n" << endl;
        cin >> reg.espera;
        cout << "Siguiente posicion X entre 0 y 199:\n" << endl;
        cin >> reg.siguientex;
        cout << "Siguiente posicion Y entre 0 y 199:\n" << endl;
        cin >> reg.siguientey;

        fwrite(&reg, sizeof(OrdenArchivo),1,f);
        contador++;

        cout << "Desea ingresar otro registro? (s o S para si, pulsar otro boton para no): \n";
        cin >> continuar;

    }while (continuar == 's' || continuar == 'S');
}
