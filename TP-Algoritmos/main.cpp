#include <iostream>
#include "include/drone.h"
#include "include/archivos.h"
#include "include/visualizador.h"

using namespace std;

void opcionesMenu();
void ejecutarMenu(/*Orden grilla[TAM_GRILLA][TAM_GRILLA]*/);

int main()
{
    //Orden grilla[TAM_GRILLA][TAM_GRILLA];
    //inicializarGrilla(grilla);

    ejecutarMenu(/*grilla*/);

    return 0;
}

void opcionesMenu()
{
    cout << "=====================================================\n";
    cout << "1. Cargar archivo de ataque en memoria.              \n";
    cout << "2. Mostrar ataque cargado.                           \n";
    cout << "3. Crear un archivo de ataque nuevo                  \n";
    cout << "4. Corregir un registro del archivo.                 \n";
    cout << "5. Corregir un registro de memoria.                  \n";
    cout << "6. Guardar memoria en un archivo nuevo.              \n";
    cout << "7. Visualizar un archivo de ataque en html.          \n";
    cout << "0. Salir.                                            \n";
    cout << "=====================================================\n";
}

void ejecutarMenu(/*Orden grilla[TAM_GRILLA][TAM_GRILLA]*/)
{
    int opcion = -1;
    char ruta[256];

    do
    {
        opcionesMenu();
        cout << "Ingrese una opcion del 0 al 7" << endl;
        cin >> opcion;
        switch(opcion)
        {
            case 1:
                cout << "[OPERACION 1] Cargar archivo de ataque en memoria\n" << endl;
                cout << "Indique ruta y nombre del archivo binario (ej: ataque.dat): " << endl;
                cin >> ruta;
                //cargarEnMemoria(ruta, grilla);
                break;

            case 2:
                cout << "[OPERACION 2] Mostrar ataque cargado en memoria\n" << endl;
                //mostrarAtaque(grilla);
                break;

            case 3:
                cout << "[OPERACION 3] Crear un archivo de ataque nuevo\n" << endl;
                //crearArchivoAtaque();
                break;

            case 4:
                cout << "[OPERACION 4] Corregir un registro del archivo binario\n" << endl;
                //corregirRegistroArchivo();
                break;

            case 5:
                cout << "[OPERACION 5] Corregir un registro en memoria\n" << endl;
                //corregirRegistroMemoria(grilla);
                break;

            case 6:
                cout << "[OPERACION 6] Guardar memoria en un archivo nuevo\n" << endl;
                //guardarMemoriaAArchivo(grilla);
                break;

            case 7:
                cout << "[OPERACION 7] Visualizar ataque cargado en HTML\n" << endl;
                cout << "Indique ruta y nombre del archivo HTML a generar (ej: mapa.html): " << endl;
                cin >> ruta;
                //generarHTML(ruta, grilla);
                break;

            case 0:
                cout << "Saliendo del sistema de navegacion offline del dron...\n" << endl;
                break;

            default:
                cout << "[!] Opcion no valida. Seleccione un numero entre 0 y 7.\n" << endl;
                break;
        }
    }while (opcion != 0);
}


