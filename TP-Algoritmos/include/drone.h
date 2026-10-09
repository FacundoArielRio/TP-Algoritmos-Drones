#ifndef DRONE_H_INCLUDED
#define DRONE_H_INCLUDED

// Grilla de 200x200 definida en la consigna
const int TAM_GRILLA = 200;

// Estructura para cada casillero en memoria
struct Orden {
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = 0;
    int siguientey = 0;
};

// Estructura para los registros en disco
struct OrdenArchivo {
    int x = 0;
    int y = 0;
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = 0;
    int siguientey = 0;
};

// Prototipos de funciones implementadas en drone.cpp
bool cargarEnMemoria(const char *rutaArchivo, Orden grilla[TAM_GRILLA][TAM_GRILLA]);
bool validarRuta(OrdenArchivo registros[], int cantidad, int &idxDespegue);
void pedirRutaArchivo(char rutaFinal[]);



void mostrarAtaque(const Orden grilla[TAM_GRILLA][TAM_GRILLA]);
void corregirRegistroMemoria(Orden grilla[TAM_GRILLA][TAM_GRILLA]);

#endif // DRONE_H_INCLUDED
