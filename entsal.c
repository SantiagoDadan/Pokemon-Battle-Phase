#include "entsal.h"

void limpiarBuffer() {
  fflush(stdin);
}

void limpiarPantalla() {
  system("cls||clear");
}

void pausa()
{
  printf("\n\nPresione una tecla para continuar!\n\n");
  getchar();
}

void tomarOpcion( int* opcion ) {
  printf("\n> ");
  scanf("%d", opcion);
  limpiarBuffer();
}
