#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_USUARIO "usuarios.dat"
#define ARCHIVO_ADMIN "admins.dat"
#define MAX_ARRAY 20

typedef struct
{
    char nick[MAX_ARRAY];
    char contrasenia[MAX_ARRAY];

}Usuario;

typedef struct
{
    char nombre[MAX_ARRAY];
    char contrasenia[MAX_ARRAY];

}Admin;

void pause();
void menuPrincipal();
void menuUsuario(Usuario jugador);
Usuario cargarNuevoUsuario();
int controlarNick(char nick[]);
Usuario crearCuenta();
int siOno();
Usuario buscarUsuario(char aBuscar[]);
void inicSesionUsuario();
