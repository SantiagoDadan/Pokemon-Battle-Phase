#ifndef GENERACIONES_H_INCLUDED
#define GENERACIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemon.h"

#define ARCHIVO_GENERACIONES "bin/generaciones.bin"

typedef struct {
  int numeroDeGeneracion;
  int primerNumeroEnPokedex; // Tiene que ser igual al numero de la anterior + cantidad del anterior
  int cantidadDePokemons;
} stGeneracion;

typedef struct _nodoGeneracion {
  stGeneracion generacion;
  nodoRegistroPokemon* arbolPokemons;

  struct _nodoGeneracion* anterior;
  struct _nodoGeneracion* siguiente;
} nodoGeneracion; // Lista doblemente vinculada

void menuGeneraciones();
void mostrarMenuGeneraciones();
stGeneracion crearGeneracion();
int calcularNumeroPokedex(int cant);
void guardarGeneracion(stGeneracion gen);
void cargarGeneracionArchivo();
void mostrarUnaGeneracion(stGeneracion generacion);
void mostrarGeneraciones();
void mostrarGeneracionesLista(nodoGeneracion *lista);
nodoGeneracion *inicListaGeneracion();
nodoGeneracion *crearNodoListaGen(stGeneracion generacion);
nodoGeneracion *agregarAlPpioGen(nodoGeneracion *lista, nodoGeneracion *nuevo);
nodoGeneracion *agregarGenEnOrden(nodoGeneracion *lista, nodoGeneracion *nuevo);
nodoGeneracion *cargarGeneracionDesdeArchivo(nodoGeneracion *lista);
void cargarPokemonArbolDesdeArchivo(nodoGeneracion *lista);
nodoGeneracion *buscarGeneracion(nodoGeneracion *lista, int idPokedex);
void mostrarPokePorGeneracion(nodoGeneracion *lista, int generacion);
int compararPokemonConTipo( modeloDePokemon poke, int tipo );
int compararGeneracionConNumero( stGeneracion generacion, int numero );
void mostrarGeneracion( nodoRegistroPokemon* arbolPokemons, int tipo );
void mostrarPokemons( nodoGeneracion* lista, int generacion, int tipo );
void encabezadoDeMostrarPokemons();
modeloDePokemon buscarPokemonEnGeneraciones( nodoGeneracion* listaGen, int idPokedex );

#endif // GENERACIONES_H_INCLUDED
