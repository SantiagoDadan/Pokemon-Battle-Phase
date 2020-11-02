#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "movimiento.h"

#define MAX_LENGTH 20

enum enGenero { femenino = 1, masculino = 2 };

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

  struct _nodoRegistroPokemon* izquieda;
  struct _nodoRegistroPokemon* derecha;
} nodoRegistroPokemon;

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

void crearNuevaGeneracion( char archivoGeneraciones, nodoGeneracion* listaGeneraciones, char nombreNuevaGeneracion[MAX_LENGTH] );
void crearNuevoPokemon( char nombreDeGeneracion[MAX_LENGTH] );
nodoRegistroPokemon* cargarPokemonsEnGeneracion( char archivoGeneracion[MAX_LENGTH], nodoGeneracion* generacion );
nodoGeneracion* cargarListaDeGeneraciones( char archivoGeneraciones[MAX_LENGTH] );
void obtenerConducta( char conducta[MAX_LENGTH] );
void pokemonAtaca( pokemonDeJugador atacante, pokemonDeJugador receptor, int usaAtaqueEspecial );
int calcularEficienciaDelAtaque( int idTipoDelAtaque, int idTiposDelPokemonDefensor[2] );
int calcularDanioRealizado( int poderDelAtaque, int eficienciaDelAtaque, int defensaDefensor ); // Incompleto, falta resolver la formula a utilizar
