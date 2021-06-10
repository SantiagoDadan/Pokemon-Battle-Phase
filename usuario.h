#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <direct.h>
#define GetCurrentDir _getcwd

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "pokemon.h"
#include "stpoke.h"
#include "pokemon.h"
#include "stpoke.h"


#define ARCHIVO_USUARIO "usr/usuarios.dat"
#define ARCHIVO_ADMIN "usr/admins.dat"
#define MAX_ARRAY 20
#define MAX_EQUIPO 6

typedef struct
{
    int categoria; /// 1 para usuario, 2 para admin.
    char nick[MAX_ARRAY];
    char contrasenia[MAX_ARRAY];
    pokemonDeJugador equipo[MAX_EQUIPO]; /// idPokedex -1 si la celda esta libre para un nuevo pokemon.
}Usuario;

void inicio();
void menuPrincipal();
void menuUsuario(Usuario jugador);
Usuario cargarNuevoUsuario();
int controlarNick(char nick[]);
Usuario crearCuenta();
int siOno();
Usuario buscarUsuario(char aBuscar[]);
void inicSesionUsuario();
void inicSesionAdmin();
Usuario cargarNuevoAdmin();
void crearNuevaCuentaAdmin();
void menuAdmin();
void modificaciones();
int equipoLleno(Usuario entrenador);
char* devolverGenero(pokemonDeJugador aux);
Usuario perfilEntrenador(Usuario entrenador);
void modificacionesPokemon();
int seleccionarPokemonPelea(Usuario entrenador);
Usuario entrarEnLaHierba(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos);
Usuario asignarStarter(Usuario entrenador, nodoGeneracion * lista);
void guardarUsuario(Usuario entrenador);
Usuario liberarPokemon(Usuario entrenador);
Usuario agregarPokeAlEquipo( Usuario entrenador, pokemonDeJugador salvaje );
void mostrarMenu();
void menuMovimientos();
void menuMovimientosPorTipo();
int cantPokesEnEquipo(Usuario entrenador);
Usuario pelarVsEntrenador(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos);
Usuario pelearVsLider(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos);


#endif // USUARIO_H_INCLUDED
