#ifndef STPOKE_H_INCLUDED
#define STPOKE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gotoxy.h"

#include "tipos.h"
#include "movimiento.h"
#include "generacion.h"

enum enGenero { masculino = 0, femenino = 1 };

typedef struct {
  int idPokedex;
  char nombre[ MAX_LENGTH ];
  char apodo[ MAX_LENGTH ]; // Nombre elegido por el entrenador
  int genero; // femenino o masculino
  int idTipo[2]; // -1 en el segundo tipo si no lo tiene

  int estadSalud;
  int estadAtaque;
  int estadDefensa;
  int estadVelocidad;

  char naturaleza[ MAX_LENGTH ]; // Son 25 en total, seleccionado al azar
  int idMovimientosDisponibles[2];
  int experienceObtenida;
} pokemonDeJugador;

void obtenerNaturaleza( pokemonDeJugador* nuevoPoke );
void obtenerGenero( pokemonDeJugador* nuevoPoke );
void obtenerSetMovimientos( pokemonDeJugador* nuevoPoke, modeloDePokemon base );
pokemonDeJugador crearPokemonDeJugador( nodoGeneracion* lista, int idPokedex );
int pelear(pokemonDeJugador poke1, pokemonDeJugador poke2, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos, nodoGeneracion* listaGen, int* ganador);
int calcularTurno(pokemonDeJugador poke1, pokemonDeJugador poke2);
int ataqueEnemigo(pokemonDeJugador atacante, pokemonDeJugador receptor, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos);
int realizarAtaque(pokemonDeJugador atacante, pokemonDeJugador receptor, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos);
int elegirMovimiento(pokemonDeJugador atacante, movimientoNodo *arbolMoviminetos );
int pokemonAtaca(pokemonDeJugador atacante, pokemonDeJugador receptor, int idMovimiento, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos);
int pokemonRandom(nodoGeneracion * lista);
char* devolverTipo(pokemonDeJugador aux, int nroTipo);
int calcularTotalStats( pokemonDeJugador poke ); // No usar directamente, llamada en sumarExperienciaAPokemon
int estadisticaSubir( pokemonDeJugador poke, int totalEstadisticas ); // No usar directamente, llamada en sumarExperienciaAPokemon
void sumarExperienciaAPokemon( pokemonDeJugador* poke, int experiencia );
void evolucionarPokemon( nodoGeneracion* listaGen, pokemonDeJugador* poke );
int hayEvolucion( nodoGeneracion* listaGen, pokemonDeJugador* poke );
int calcularExperienciaRecompensa( pokemonDeJugador pokemonAdversario, int resultadoDelCombate );
int lanzarPokeball(pokemonDeJugador pokeSalvajed);
void imprimirPokemonSalvaje(pokemonDeJugador aux, int saludBase, int saludActual);
float calcularPromedioStats(pokemonDeJugador pokemon);
pokemonDeJugador elegirDificultatCapturarPokemon(nodoGeneracion * lista);
int pelearXvX(pokemonDeJugador pokesElegidos[], pokemonDeJugador contrincante[], int cantPokes, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos, nodoGeneracion *listaGen, int ganador);

#endif // STPOKE_H_INCLUDED
