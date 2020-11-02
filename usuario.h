#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_USUARIO "usuarios.dat"
#define ARCHIVO_ADMIN "admins.dat"
#define MAX_ARRAY 20

typedef struct
{
    int categoria; /// 1 para usuario, 2 para admin.
    char nick[MAX_ARRAY];
    char contrasenia[MAX_ARRAY];

}Usuario;

void pause();
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
