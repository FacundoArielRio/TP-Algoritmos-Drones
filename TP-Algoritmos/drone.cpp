#include <iostream>
#include <cstdio>
#include <cmath>
#include <conio.h>
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
    idxDespegue=-1;
    for(int i=0; i<cantidad; i++)
    {
        if(registros[i].x < 0 || registros[i].x >= TAM_GRILLA ||
           registros[i].y < 0 || registros[i].y >= TAM_GRILLA)
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
                cout << "La instrucción de despegue no puede contener armas ni ataques.\n" << endl;
                return false;
            }
        }
        if(registros[i].aterrizaje==true||registros[i].ataqueKamikaze==true)
        {
            finales++;
        }
    }
    if(despegues!=1)
    {
        cout << "Debe haber una unica instruccion de despegue (encontradas: " << despegues << ").\n" << endl;
        return false;
    }
    if(finales!=1)
    {
        cout << "Debe haber una unica instruccion de aterrizaje o ataque kamikaze (encontradas: " << finales << ").\n" << endl;
        return false;
    }
    return true;
}

bool validarRecorrido(OrdenArchivo registros[], int cantidad, int idxDespegue)
{
    bool visitado[TAM_GRILLA][TAM_GRILLA];
    for (int i = 0; i < TAM_GRILLA; i++) {
        for (int j = 0; j < TAM_GRILLA; j++) {
            visitado[i][j] = false;
        }
    }

    int idxActual = idxDespegue;
    int pasosRecorridos = 0;
    bool llegoAlFinal = false;

    while (pasosRecorridos < cantidad)
    {
        int cx = registros[idxActual].x;
        int cy = registros[idxActual].y;

        if (visitado[cx][cy]) {
            cout << "Las coordenadas (" << cx << "; " << cy << ") estan repetidas.\n" << endl;
            return false;
        }

        visitado[cx][cy] = true;
        pasosRecorridos++;

        if (registros[idxActual].aterrizaje || registros[idxActual].ataqueKamikaze) {
            llegoAlFinal = true;
            break;
        }

        int siguienteX = registros[idxActual].siguientex;
        int siguienteY = registros[idxActual].siguientey;

        int diferenciaX = abs(siguienteX - cx);
        int diferenciaY = abs(siguienteY - cy);

        if (diferenciaX > 1 || diferenciaY > 1 || (siguienteX == cx && siguienteY == cy)) {
            cout << "Salto no valido hacia (" << siguienteX << "; " << siguienteY << "). No son celdas aledanas." << endl;
            return false;
        }

        int siguienteIdx = -1;
        for (int j = 0; j < cantidad; j++) {
            if (registros[j].x == siguienteX && registros[j].y == siguienteY) {
                siguienteIdx = j;
                break;
            }
        }

        if (siguienteIdx == -1) {
            cout << "Ruta incompleta: no existe orden guardada para la celda destino ("
                 << siguienteX << "; " << siguienteY << ").\n" << endl;
            return false;
        }

        idxActual = siguienteIdx;
    }

    if (!llegoAlFinal) {
        cout << "La ruta no posee una instruccion de finalizacion alcanzable desde el despegue.\n" << endl;
        return false;
    }

    if (pasosRecorridos != cantidad) {
        cout << "Existen registros aislados en el archivo que no pertenecen al trayecto principal.\n" << endl;
        return false;
    }

    return true;
}

bool validarRuta(OrdenArchivo registros[], int cantidad, int &idxDespegue)
{
    if(cantidad<=0)
    {
        cout << "\nNo hay registros para validar." << endl;
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
    return true;
}

bool cargarEnMemoria(char rutaArchivo[], Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    FILE *f = fopen(rutaArchivo,"rb");
    if(f == NULL)
    {
        cout << "\nNo se puedo abrir el archivo " << rutaArchivo << endl;
        return false;
    }

    OrdenArchivo buffer[TAM_GRILLA * TAM_GRILLA];
    int cantidad=0;
    while (fread(&buffer[cantidad], sizeof(OrdenArchivo), 1, f)==1)
    {
        cantidad++;
    }
    fclose(f);

    int idxDespegue=-1;
    if (validarRuta(buffer, cantidad, idxDespegue)==false)
    {
        cout << "\nEl archivo no cumple las reglas de vuelo. No se cargo en memoria." << endl;
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
    cout << "\nArchivo cargado en memoria exitosamente. Cantidad de registros: " << cantidad << endl;
    return true;
}

void mostrarAtaque(Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    int pos_x = 0, pos_y = 0;
    bool pos_despegue = false;

    while (pos_x < TAM_GRILLA && !pos_despegue) {
        while (pos_y < TAM_GRILLA && !pos_despegue) {
            if (grilla[pos_x][pos_y].despegue == true)
                pos_despegue = true;

            else
                pos_y++;
        }

        if (!pos_despegue) {
            pos_x++;
            pos_y = 0;
        }
    }

    if (!pos_despegue) {
        cout << "No se ha hallado ningun ataque cargado en memoria.\n" << endl;
        return;
    }

    cout << "--- RECORRIDO DEL ATAQUE CARGADO ---\n" << endl;

    int contador_celdas = 0;
    bool fin_ruta = false;

    while (!fin_ruta)
    {
        Orden coordenada = grilla[pos_x][pos_y];

        if (contador_celdas % 5 == 0) {
            cout << "-- PAGINA " << (contador_celdas / 5) + 1 << " --" << endl << endl;
        }

        cout << "- Coordenada: (" << pos_x << "; " << pos_y << ") -" << endl;
        if (coordenada.despegue)
            cout << " -> [ACCION] Despegue" << endl;
        if (coordenada.aterrizaje)
            cout << " -> [ACCION] Aterrizaje" << endl;
        if (coordenada.soltarGranada1)
            cout << " -> [ACCION] Soltar Granada 1" << endl;
        if (coordenada.soltarGranada2)
            cout << " -> [ACCION] Soltar Granada 2" << endl;
        if (coordenada.ataqueKamikaze)
            cout << " -> [ACCION] Ataque Kamikaze" << endl;
        if (coordenada.espera == 1)
            cout << " -> Tiempo de espera: " << coordenada.espera << " segundo" << endl;
        else
            cout << " -> Tiempo de espera: " << coordenada.espera << " segundos" << endl;

        cout << endl;

        if (coordenada.aterrizaje || coordenada.ataqueKamikaze)
        {
            fin_ruta = true;
            cout << "--- FIN DEL ATAQUE ---\n" << endl;
        }
        else
        {
            pos_x = coordenada.siguientex;
            pos_y = coordenada.siguientey;
        }

        contador_celdas++;

        if (contador_celdas % 5 == 0 && !fin_ruta)
        {
            cout << "\n[Presione la tecla 's' para ver la siguiente pagina...]";
            char tecla = getch();
            while (tecla != 's' && tecla != 'S') {
                tecla = getch();
            }
            cout << endl << endl << endl;
        }
    }
}

void corregirRegistroMemoria(Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    int x, y;
    cout << "=== OPERACION 5: CORREGIR REGISTRO EN MEMORIA ===" << endl;
    cout << "Ingrese la coordenada X a corregir (0 a 199): ";
    cin >> x;
    cout << "Ingrese la coordenada Y a corregir (0 a 199): ";
    cin >> y;

    if (x < 0 || x >= TAM_GRILLA || y < 0 || y >= TAM_GRILLA)
    {
        cout << "\n[!] Error: Las coordenadas (" << x << "; " << y << ") estan fuera del rango de la grilla." << endl;
        return;
    }

    Orden &celda = grilla[x][y];

    cout << "\n--- ESTADO ACTUAL EN LA CASILLA (" << x << "; " << y << ") ---" << endl;
    cout << " -> Despegue: " << (celda.despegue ? "Si" : "No") << endl;
    cout << " -> Aterrizaje: " << (celda.aterrizaje ? "Si" : "No") << endl;
    cout << " -> Soltar Granada 1: " << (celda.soltarGranada1 ? "Si" : "No") << endl;
    cout << " -> Soltar Granada 2: " << (celda.soltarGranada2 ? "Si" : "No") << endl;
    cout << " -> Ataque Kamikaze: " << (celda.ataqueKamikaze ? "Si" : "No") << endl;
    cout << " -> Tiempo de espera: " << celda.espera << " segundos" << endl;
    cout << " -> Siguiente casilla: (" << celda.siguientex << "; " << celda.siguientey << ")" << endl;

    cout << "\n--- INGRESE LOS NUEVOS DATOS PARA LA CASILLA ---" << endl;

    int accion;
    cout << "Elija la accion a realizar en (" << x << "; " << y << "):\n";
    cout << "  0 = Ninguna (Solo moverse)\n";
    cout << "  1 = Despegue\n";
    cout << "  2 = Soltar Granada 1\n";
    cout << "  3 = Soltar Granada 2\n";
    cout << "  4 = Ataque Kamikaze\n";
    cout << "  5 = Aterrizaje\n";
    cout << "Opcion (0 a 5): ";
    cin >> accion;

    celda.despegue = false;
    celda.soltarGranada1 = false;
    celda.soltarGranada2 = false;
    celda.ataqueKamikaze = false;
    celda.aterrizaje = false;

    switch (accion)
    {
        case 0:
            break;
        case 1:
            celda.despegue = true;
            break;
        case 2:
            celda.soltarGranada1 = true;
            break;
        case 3:
            celda.soltarGranada2 = true;
            break;
        case 4:
            celda.ataqueKamikaze = true;
            break;
        case 5:
            celda.aterrizaje = true;
            break;
        default:
            cout << "\nOpcion no valida. No se aplicaron cambios de accion." << endl;
            break;
    }

    cout << "Segundos de espera: ";
    cin >> celda.espera;

    cout << "Siguiente posicion X (0 a 199): ";
    cin >> celda.siguientex;

    cout << "Siguiente posicion Y (0 a 199): ";
    cin >> celda.siguientey;

    if (celda.siguientex < 0 || celda.siguientex >= TAM_GRILLA ||
        celda.siguientey < 0 || celda.siguientey >= TAM_GRILLA)
    {
        cout << "\nAdvertencia: La celda siguiente ingresada excede los limites de la grilla." << endl;
    }

    cout << "\nEl registro en memoria RAM (" << x << "; " << y << ") fue actualizado correctamente." << endl;
}
