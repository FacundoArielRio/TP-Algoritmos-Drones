#include <iostream>
#include <cstdio>
#include <cstring>
#include "include/archivos.h"

using namespace std;

void pedirRutaArchivo(char rutaFinal[])
{
    char ruta[256];
    char nombre[128];

    rutaFinal[0] = '\0';

    cout << "Ingrese la ruta del archivo: " << endl;
    cin >> ruta;
    cout << "Ingrese el nombre del archivo: " << endl;
    cin >> nombre;

    strcat(rutaFinal, ruta);
    strcat(rutaFinal, "/");
    strcat(rutaFinal, nombre);
    strcat(rutaFinal, ".dat");
}

void crearArchivoAtaque()
{
    char rutaFinal[384];

    pedirRutaArchivo(rutaFinal);

    FILE *f = fopen(rutaFinal,"wb");
    if (f == NULL)
    {
        cout << "\nNo se pudo crear el archivo en: \n" << rutaFinal << endl;
        return;
    }

    cout << "\nArchivo creado. Ingresar los registros: \n" << endl;

    char continuar;
    int contador=0;

    do
    {
        OrdenArchivo reg;

        cout << "\n---- Registro " << contador+1 << " ----\n" << endl;

        cout << "Coordenada X entre 0 y 199: ";
        cin >> reg.x;
        cout << "Coordenada Y entre 0 y 199: ";
        cin >> reg.y;

        reg.soltarGranada1 = false;
        reg.soltarGranada2 = false;
        reg.ataqueKamikaze = false;
        reg.aterrizaje = false;
        reg.despegue = false;

        int accion;
        cout << "\nAccion a realizar en (" << reg.x << ";" << reg.y << "):\n" << endl;

        cout << "  0 = Ninguna (solo moverse)\n";
        cout << "  1 = Despegue\n";
        cout << "  2 = Soltar Granada 1\n";
        cout << "  3 = Soltar Granada 2\n";
        cout << "  4 = Ataque Kamikaze\n";
        cout << "  5 = Aterrizaje\n";

        cout << "\nElija una opcion de 0 a 5: ";
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
                cout << "\nError: debe de elegir una opcion del 0 al 5." << endl;
            break;
        }

        cout << "\nSegundos de espera: ";
        cin >> reg.espera;
        cout << "\nSiguiente posicion X entre 0 y 199: ";
        cin >> reg.siguientex;
        cout << "Siguiente posicion Y entre 0 y 199: ";
        cin >> reg.siguientey;

        fwrite(&reg, sizeof(OrdenArchivo),1,f);
        contador++;

        cout << "\nDesea ingresar otro registro? (s o S para si, pulsar otro boton para no): \n";
        cin >> continuar;

    }while (continuar == 's' || continuar == 'S');
}

void corregirRegistroArchivo()
{
    char rutaArchivo[384];
    pedirRutaArchivo(rutaArchivo);

    FILE *f = fopen(rutaArchivo, "rb+");
    if (f == NULL)
    {
        cout << "\nNo se pudo abrir el archivo: " << rutaArchivo << endl;
        return;
    }

    int x, y;
    cout << "\nIngrese la coordenada X del registro a corregir: ";
    cin >> x;
    cout << "Ingrese la coordenada Y del registro a corregir: ";
    cin >> y;

    if (x<0 || x>=TAM_GRILLA || y<0 || y>=TAM_GRILLA)
    {
        cout << "\nCoordenadas incorrectas" << endl;
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_END);
    int tam = ftell(f);
    int cantidad = tam / sizeof(OrdenArchivo);
    fseek(f, 0, SEEK_SET);

    OrdenArchivo reg;
    int posicion = -1;

    for (int i=0; i<cantidad; i++)
    {
        fread(&reg, sizeof(OrdenArchivo), 1, f);

        if (reg.x == x && reg.y == y)
        {
            posicion = i;
            break;
        }
    }

    if (posicion == -1)
    {
        cout << "\nNo existe un registro con esas coordenadas." << endl;
        fclose(f);
        return;
    }
    cout << "\n--- REGISTRO ENCONTRADO ---" << endl;
    cout << "X: " << reg.x << endl;
    cout << "Y: " << reg.y << endl;
    cout << "Espera: " << reg.espera << endl;
    cout << "Soltar granada 1: " << reg.soltarGranada1 << endl;
    cout << "Soltar granada 2: " << reg.soltarGranada2 << endl;
    cout << "Ataque kamikaze: " << reg.ataqueKamikaze << endl;
    cout << "Aterrizaje: " << reg.aterrizaje << endl;
    cout << "Despegue: " << reg.despegue << endl;
    cout << "Siguiente X: " << reg.siguientex << endl;
    cout << "Siguiente Y: " << reg.siguientey << endl;

    OrdenArchivo nuevo = reg;
    cout << "\nIngrese los nuevos datos del registro:" << endl;
    cout << "Nueva X (0 a 199): ";
    cin >> nuevo.x;
    cout << "Nueva Y (0 a 199): ";
    cin >> nuevo.y;
    cout << "Nueva espera (segundos): ";
    cin >> nuevo.espera;
    cout << "Soltar granada 1 (1=Si, 0=No): ";
    cin >> nuevo.soltarGranada1;
    cout << "Soltar granada 2 (1=Si, 0=No): ";
    cin >> nuevo.soltarGranada2;
    cout << "Ataque kamikaze (1=Si, 0=No): ";
    cin >> nuevo.ataqueKamikaze;
    cout << "Aterrizaje (1=Si, 0=No): ";
    cin >> nuevo.aterrizaje;
    cout << "Despegue (1=Si, 0=No): ";
    cin >> nuevo.despegue;
    cout << "Siguiente X (0 a 199): ";
    cin >> nuevo.siguientex;
    cout << "Siguiente Y (0 a 199): ";
    cin >> nuevo.siguientey;

    if (nuevo.espera < 0 || nuevo.x < 0 || nuevo.x >= TAM_GRILLA ||
        nuevo.y < 0 || nuevo.y >= TAM_GRILLA ||
        nuevo.siguientex < 0 || nuevo.siguientex >= TAM_GRILLA ||
        nuevo.siguientey < 0 || nuevo.siguientey >= TAM_GRILLA)
    {
        cout << "\nDatos incorrectos. No se modifico el archivo." << endl;
        fclose(f);
        return;
    }

    fseek(f,posicion * sizeof(OrdenArchivo),SEEK_SET);
    fwrite(&nuevo,sizeof(OrdenArchivo),1,f);
    cout << "\nRegistro corregido y guardado en el archivo." << endl;

    fclose(f);
}
