#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entsal.h"

#define MAX_LENGTH 20
#define ARCHIVO_MOVIMIENTOS "bin/movimientos.bin"

typedef struct {
  int id;
  char nombre[ MAX_LENGTH ];
  int tipo;
  int poder;

} stMovimiento;

typedef struct _movimientoNodo {
  stMovimiento movimiento;

  struct _movimientoNodo* izquierda;
  struct _movimientoNodo* derecha;
} movimientoNodo; // Nodo de arbol binario

movimientoNodo* cargarMovimientosDesdeArchivo( char archivoMovimientos[MAX_LENGTH] );
stMovimiento buscarMovimiento( movimientoNodo* arbolDeMovimientos, int idDelMovimientoBuscado );
movimientoNodo* inicArbolMovimientos();
movimientoNodo* agregarMovimientoAlArbol( movimientoNodo* arbol, movimientoNodo* nodoNuevo );
movimientoNodo* crearNodoMovimiento( stMovimiento movimientoNuevo );
void imprimirMovimiento( stMovimiento aMostrar );
void imprimirMovimientoSinTipo( stMovimiento aMostrar );
void mostrarMovimientos( movimientoNodo* arbol );
stMovimiento crearMovimiento();
movimientoNodo* creacionDeNuevoMovimiento( movimientoNodo* arbolDeMovimientos );
void mostrarMovimientosPorTipo( movimientoNodo* arbolDeMovimientos, int tipoBuscado );
void encabezadoDeMostrarMovimientos();
void encabezadoDeMostrarMovimientosPorTipo();
movimientoNodo* mayorNodoPorId( movimientoNodo* arbol );
movimientoNodo* quitarMovimientoDeArbol ( movimientoNodo* arbol, int idEliminar );
void borrarMovimientoDeBinario( int idMovimiento );
movimientoNodo* borradoDeMovimiento( movimientoNodo* arbol );
int obtenerPoder(movimientoNodo* arbol, int idMovimiento);
char* mostrarMovimientoPelea(movimientoNodo * arbolMovimientos, int idBuscar);

#endif // MOVIMIENTO_H_INCLUDED
