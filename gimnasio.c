#include "gimnasio.h"

void cargarLideresGimnasio( char* archivoMedallas ) {
  int bandera;
  liderGimnasio ingreso;
  FILE* archivo = fopen( archivoMedallas, "ab" );

  if(archivo) {

    do {
      printf("\nNombre del lider: ");
      scanf("%[^\n]", ingreso.nombre);
      limpiarBuffer();

      for(int i=1; i<=3; i++) {
        printf("\nId Pokemon %d: ", i);
        scanf("%d", &ingreso.equipo[i]);
        limpiarBuffer();
      }

      printf("\nNombre de medalla: ");
      scanf("%[^\n]", ingreso.recompensa.nombreMedalla);
      limpiarBuffer();

      printf("\nNombre de Gimnasio: ");
      scanf("%[^\n]", ingreso.recompensa.nombreGimnasio);
      limpiarBuffer();

      fwrite(&ingreso, sizeof(liderGimnasio), 1, archivo);

      printf("\nContinuar ingresando? [s/N]");
      limpiarBuffer();
      bandera = getchar() == 's' ? 1 : 0;
    } while ( bandera );

    fclose( archivo );
  }
}

medalla entregaMedalla( liderGimnasio lider ) {
  return lider.recompensa;
}

void guardarEnMedallero( medallasJugador* medallas, medalla nuevaMedalla ) {
  medallas->medallero[ medallas->cantidadMedallas ] = nuevaMedalla;
}

void guardarMedallas( char* archivoMedallas, medallasJugador medallas ) {
  FILE* archivo = fopen( archivoMedallas, "r+b" );
  medallasJugador aux;
  int bandera = 0;

  if( archivo ) {

    while ( !bandera && fread(&aux, sizeof(medallasJugador), 1, archivo) > 0 ) {
      if( strcmp(aux.nombreEntrenador, medallas.nombreEntrenador) == 0 ) {
        fseek(archivo, -sizeof(medallasJugador), SEEK_CUR);
        fwrite(&medallas, sizeof(medallasJugador), 1, archivo);
        bandera = 1;
      }
    }

    fclose(archivo);
  }

  if( !bandera ) {
    archivo = fopen( archivoMedallas, "ab" );
    fwrite(&medallas, sizeof(medallasJugador), 1, archivo);
    fclose(archivo);
  }
}

medallasJugador obtenerMedallasDeJugador( char* archivoMedallas, char* nombreJugador ) {
  FILE* archivo = fopen( archivoMedallas, "r+b" );
  medallasJugador aux;
  int bandera = 0;

  if( !archivo ) {
    archivo = fopen(archivoMedallas, "ab");
    fclose(archivo);
    archivo = fopen(archivoMedallas, "r+b");
  }

  if( archivo ) {

    while ( !bandera && fread(&aux, sizeof(medallasJugador), 1, archivo) > 0 ) {
      if( strcmp(aux.nombreEntrenador, nombreJugador) == 0 ) {
        bandera = 1;
      }
    }

    fclose(archivo);
  }

  if( !bandera ) {
    strcpy(aux.nombreEntrenador, nombreJugador);
    aux.cantidadMedallas = 0;
  }

  return aux;
}

void mostrarLider( liderGimnasio lider ) {
  printf("1-\t %s\n", lider.nombre);
  printf("\tGimnasio: %s\n", lider.recompensa.nombreGimnasio);
  printf("\tMedalla: %s\n\n", lider.recompensa.nombreMedalla);
}

int mostrarLideres( char* archivoLideres ) {
  FILE* archivo = fopen( archivoLideres, "r+b" );
  liderGimnasio aux;
  int cantLeidos = 0;

  if( archivo ) {
    while ( fread(&aux, sizeof(liderGimnasio), 1, archivo)>0 ) {
      mostrarLider(aux);
      cantLeidos++;
    }

    fclose(archivo);
  } else {
    fopen( archivoLideres, "ab" );
    printf("No hay lideres cargados. Comuniquese con el desarrollador\n");
  }

  return cantLeidos;
}

liderGimnasio buscarLider( char* archivoLideres, int numeroLider ) {
  FILE* archivo = fopen( archivoLideres, "r+b" );
  liderGimnasio aux;

  if( archivo ) {
    fseek(archivo, (numeroLider-1)*sizeof(liderGimnasio), SEEK_SET);
    fread(&aux, sizeof(liderGimnasio), 1, archivo);


    fclose(archivo);
  }

  return aux;
}

int elegirLiderParaCombatir( char* archivoLideres, liderGimnasio* lider ) {
  int opcion=0;
  int bandera=0;
  int cantidad;

  do {
    limpiarPantalla();
    cantidad = mostrarLideres(archivoLideres);

    if( cantidad > 0 ) {
      printf("Desafiar a: ");
      scanf("%d", &opcion);
      limpiarBuffer();
      bandera = 1;
    }

  } while( opcion > 0 && opcion <= cantidad && cantidad > 0 );

  if( bandera ) {
    *lider = buscarLider(archivoLideres, opcion);
  }

  return bandera;
}

void imprimirMedallas(medallasJugador jugador)
{
    for(int i = 0; i < jugador.cantidadMedallas; i++)
    {
        printf("\nMedalla: %s de %s", jugador.medallero[i].nombreMedalla, jugador.medallero[i].nombreGimnasio);
    }
}
