#include "movimiento.h"

movimientoNodo* inicArbolMovimientos() {
  return NULL;
}

movimientoNodo* agregarMovimientoAlArbol( movimientoNodo* arbol, movimientoNodo* nodoNuevo ) {
  if( !arbol ) {
    arbol = nodoNuevo;
  } else if( (arbol->movimiento).id > (nodoNuevo->movimiento).id ) {
    arbol->izquierda = agregarMovimientoAlArbol( arbol->izquierda, nodoNuevo );
  } else if ( (arbol->movimiento).id < (nodoNuevo->movimiento).id ) {
    arbol->derecha = agregarMovimientoAlArbol( arbol->derecha, nodoNuevo );
  }

  return arbol;
}

movimientoNodo* crearNodoMovimiento( stMovimiento movimientoNuevo ) {
  movimientoNodo* nuevoNodo = malloc( sizeof( movimientoNodo ) );

  nuevoNodo->movimiento = movimientoNuevo;
  nuevoNodo->derecha = inicArbolMovimientos();
  nuevoNodo->izquierda = inicArbolMovimientos();

  return nuevoNodo;
}

movimientoNodo* cargarMovimientosDesdeArchivo( char archivoMovimientos[] ) {
  movimientoNodo* arbol = inicArbolMovimientos();
  movimientoNodo* auxNodo;
  stMovimiento auxSt;
  FILE* archivo = fopen( archivoMovimientos, "rb" );
  
  if(!archivo) {
    archivo = fopen( archivoMovimientos, "wb" );
  } else {
    while( fread(&auxSt, sizeof(stMovimiento), 1, archivo) ) {
      auxNodo = crearNodoMovimiento( auxSt );
      arbol = agregarMovimientoAlArbol( arbol, auxNodo );
    }
  }

  fclose( archivo );

  return arbol;
}

stMovimiento buscarMovimiento( movimientoNodo* arbolDeMovimientos, int idDelMovimientoBuscado ) {
  stMovimiento movimientoBuscado;

  if ( arbolDeMovimientos ) {
    if( (arbolDeMovimientos->movimiento).id == idDelMovimientoBuscado ) {
      movimientoBuscado = arbolDeMovimientos->movimiento;
    } else if ( (arbolDeMovimientos->movimiento).id > idDelMovimientoBuscado ) {
      movimientoBuscado = buscarMovimiento( arbolDeMovimientos->izquierda, idDelMovimientoBuscado );
    } else {
      movimientoBuscado = buscarMovimiento( arbolDeMovimientos->derecha, idDelMovimientoBuscado );
    }
  } else {
    printf("======= MOVIMIENTO INEXISTENTE O ARCHIVO NO CARGADO =======\n"); 
  }

  return movimientoBuscado;
}

void imprimirMovimiento( stMovimiento aMostrar ) {
  printf("ID: %d\n", aMostrar.id);
  printf("Nombre: %s\n", aMostrar.nombre);
  printf("Tipo: %d\n", aMostrar.tipo); // Solo para desarrollo, luego cambiar al nombre del tipo
  printf("Poder: %d\n", aMostrar.poder);
}

void imprimirMovimientoSinTipo( stMovimiento aMostrar ) {
  printf("ID: %d\n", aMostrar.id);
  printf("Nombre: %s\n", aMostrar.nombre);
  printf("Poder: %d\n", aMostrar.poder);
}

void mostrarMovimientos( movimientoNodo* arbol ) {
  if ( arbol ) {
    mostrarMovimientos( arbol->izquierda );
    imprimirMovimiento( arbol->movimiento );
    printf("\n");
    mostrarMovimientos( arbol->derecha );
  }
}

int estaElMovimientoEnArchivo( char* nombreArchivo, int id ) {
  int encontrado = 0;
  stMovimiento aux;
  FILE* archivo = fopen( nombreArchivo, "rb" );
  
  if(!archivo) {
    archivo = fopen( nombreArchivo, "wb" );
  } else {
    while( fread(&aux, sizeof(stMovimiento), 1, archivo) ) {
      if( aux.id == id ) {
        encontrado = 1;
      }
    }
  }

  fclose( archivo );

  return encontrado;
}

stMovimiento crearMovimiento() {
  stMovimiento nuevoMovimiento;
  
  do {
    printf("\n\nID: ");
    scanf("%d", &nuevoMovimiento.id);
    while( getchar() != '\n' );

  } while( estaElMovimientoEnArchivo( ARCHIVO_MOVIMIENTOS, nuevoMovimiento.id ) );

  printf("Nombre: ");
  fgets(nuevoMovimiento.nombre, MAX_LENGTH, stdin);
  nuevoMovimiento.nombre[strlen(nuevoMovimiento.nombre)-1] = 0;
  printf("Tipo: ");
  scanf("%d", &nuevoMovimiento.tipo);
  while( getchar() != '\n' );
  printf("Poder: ");
  scanf("%d", &nuevoMovimiento.poder);
  while( getchar() != '\n' );

  return nuevoMovimiento;
}

movimientoNodo* creacionDeNuevoMovimiento( movimientoNodo* arbolDeMovimientos ) {
  stMovimiento nuevoMovimiento = crearMovimiento();

  movimientoNodo* nuevoNodo = crearNodoMovimiento( nuevoMovimiento );
  arbolDeMovimientos = agregarMovimientoAlArbol( arbolDeMovimientos, nuevoNodo );

  FILE* archivo = fopen( ARCHIVO_MOVIMIENTOS, "ab" );

  if( archivo ) {
    fwrite(&nuevoMovimiento, sizeof(stMovimiento), 1, archivo);
  }

  fclose( archivo );

  return arbolDeMovimientos;
}

void mostrarMovimientosPorTipo( movimientoNodo* arbolDeMovimientos, int tipoBuscado ) {
  if ( arbolDeMovimientos ) {
    mostrarMovimientosPorTipo( arbolDeMovimientos->izquierda, tipoBuscado );
    if( (arbolDeMovimientos->movimiento).tipo == tipoBuscado ) {
      imprimirMovimientoSinTipo( arbolDeMovimientos->movimiento );
      printf("\n");
    }
    mostrarMovimientosPorTipo( arbolDeMovimientos->derecha, tipoBuscado );
  }
}
