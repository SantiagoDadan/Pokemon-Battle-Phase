#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entsal.h"

#define MAX_LENGTH 20
#define ESC 27
#define ARCHIVO_POKEMONS "bin/pokemons.bin"

typedef struct {
  int idPokedex;
  char nombre[ MAX_LENGTH ];
  int idTipo[2]; // -1 en el segundo tipo si no lo tiene

  int estadSalud;
  int estadAtaque;
  int estadDefensa;
  int estadVelocidad;

  int idSiguienteEvolucion; // -1 si no tiene
  int idMovimientosAptos[MAX_LENGTH];
} modeloDePokemon;

typedef struct _nodoRegistroPokemon {
  modeloDePokemon pokemonBase;

  struct _nodoRegistroPokemon* izquierda;
  struct _nodoRegistroPokemon* derecha;
} nodoRegistroPokemon;

modeloDePokemon crearModeloPokemon();
void mostrarUnModeloPokemon(modeloDePokemon pokemon);
int contarMovAptos(modeloDePokemon pokemon);
void guardarModeloPokemon(modeloDePokemon pokemon);
void cargarModeloArchivo();
void mostrarModelos();
nodoRegistroPokemon *inicArbolModelos();
nodoRegistroPokemon *crearNodoModelo(modeloDePokemon pokemon);
nodoRegistroPokemon *insertarModeloArbol(nodoRegistroPokemon *arbol, modeloDePokemon pokemon);
void preOrden( nodoRegistroPokemon* arbol );
modeloDePokemon buscarPokemonPorID ( nodoRegistroPokemon* arbol, int idPokedex );
int solicitarID();
void modificarNombre();
void modificarStats();
void modificarTipos();
void modificarAtaques();

#endif // POKEMON_H_INCLUDED
