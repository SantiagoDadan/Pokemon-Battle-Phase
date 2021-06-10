#ifndef GIMNASIO_H_INCLUDED
#define GIMNASIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include "stpoke.h"

#define ARCHIVO_LIDERES "bin/lideres.bin"
#define ARCHIVO_MEDALLAS "usr/medallas.dat"
#define MAX_ARRAY 20
#define MAX_EQUIPO_LIDER 3

typedef struct {
    char nombreMedalla[MAX_ARRAY];
    char nombreGimnasio[MAX_ARRAY];
} medalla;

typedef struct {
    char nombre[MAX_ARRAY];
    int equipo[MAX_EQUIPO_LIDER];
    medalla recompensa;
} liderGimnasio;

typedef struct {
    char nombreEntrenador[MAX_ARRAY];
    int cantidadMedallas;
    medalla medallero[80];
} medallasJugador;

void cargarLideresGimnasio( char* archivoMedallas );
medalla entregaMedalla( liderGimnasio lider );
void guardarEnMedallero( medallasJugador* medallas, medalla nuevaMedalla );
void guardarMedallas( char* archivoMedallas, medallasJugador medallas );
medallasJugador obtenerMedallasDeJugador( char* archivoMedallas, char* nombreJugador );
void mostrarLider( liderGimnasio lider );
int mostrarLideres( char* archivoLideres );
liderGimnasio buscarLider( char* archivoLideres, int numeroLider );
int elegirLiderParaCombatir( char* archivoLideres, liderGimnasio* lider );
void imprimirMedallas(medallasJugador jugador);

#endif // GIMNASIO_H_INCLUDED
