#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "drone.h"

// Prototipos de funciones implementadas en archivos.cpp
void pedirRutaArchivo(char rutaFinal[]);
void crearArchivoAtaque();
void corregirRegistroArchivo();
void guardarMemoriaAArchivo(const Orden grilla[TAM_GRILLA][TAM_GRILLA]);

#endif // ARCHIVOS_H_INCLUDED
