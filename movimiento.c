#include "movimiento.h"

movimientoNodo* inicArbolMovimientos()
{
    return NULL;
}

movimientoNodo* agregarMovimientoAlArbol( movimientoNodo* arbol, movimientoNodo* nodoNuevo )
{
    if( !arbol )
    {
        arbol = nodoNuevo;
    }
    else if( (arbol->movimiento).id > (nodoNuevo->movimiento).id )
    {
        arbol->izquierda = agregarMovimientoAlArbol( arbol->izquierda, nodoNuevo );
    }
    else if ( (arbol->movimiento).id < (nodoNuevo->movimiento).id )
    {
        arbol->derecha = agregarMovimientoAlArbol( arbol->derecha, nodoNuevo );
    }
    else
    {
        free(nodoNuevo);
    }

    return arbol;
}

movimientoNodo* crearNodoMovimiento( stMovimiento movimientoNuevo )
{
    movimientoNodo* nuevoNodo = malloc( sizeof( movimientoNodo ) );

    nuevoNodo->movimiento = movimientoNuevo;
    nuevoNodo->derecha = inicArbolMovimientos();
    nuevoNodo->izquierda = inicArbolMovimientos();

    return nuevoNodo;
}

movimientoNodo* cargarMovimientosDesdeArchivo( char archivoMovimientos[] )
{
    movimientoNodo* arbol = inicArbolMovimientos();
    movimientoNodo* auxNodo;
    stMovimiento auxSt;
    FILE* archivo = fopen( archivoMovimientos, "rb" );

    if(!archivo)
    {
        archivo = fopen( archivoMovimientos, "wb" );
    }
    else
    {
        while( fread(&auxSt, sizeof(stMovimiento), 1, archivo) )
        {
            if( auxSt.id > 0 )
            {
                auxNodo = crearNodoMovimiento( auxSt );
                arbol = agregarMovimientoAlArbol( arbol, auxNodo );
            }
        }
    }

    fclose( archivo );

    return arbol;
}

stMovimiento buscarMovimiento( movimientoNodo* arbolDeMovimientos, int idDelMovimientoBuscado )
{
    stMovimiento movimientoBuscado;

    if ( arbolDeMovimientos )
    {
        if( (arbolDeMovimientos->movimiento).id == idDelMovimientoBuscado )
        {
            movimientoBuscado = arbolDeMovimientos->movimiento;
        }
        else if ( (arbolDeMovimientos->movimiento).id > idDelMovimientoBuscado )
        {
            movimientoBuscado = buscarMovimiento( arbolDeMovimientos->izquierda, idDelMovimientoBuscado );
        }
        else
        {
            movimientoBuscado = buscarMovimiento( arbolDeMovimientos->derecha, idDelMovimientoBuscado );
        }
    }
    else
    {
        printf("======= MOVIMIENTO INEXISTENTE O ARCHIVO NO CARGADO =======\n");
    }

    return movimientoBuscado;
}

void encabezadoDeMostrarMovimientos()
{
    printf("ID\tNOMBRE\t\t\t\tTIPO\tPODER\n\n");
}

void imprimirMovimiento( stMovimiento aMostrar )
{
    int espaciadoNombre = 3-strlen(aMostrar.nombre)/8;
    printf("%d\t", aMostrar.id);
    printf("%s\t", aMostrar.nombre);
    for( int i=0; i<espaciadoNombre; i++ )
        printf("\t");
    printf("%d\t", aMostrar.tipo);
    printf("%d\t", aMostrar.poder);
}

void imprimirMovimientoSinTipo( stMovimiento aMostrar )
{
    int espaciadoNombre = 3-strlen(aMostrar.nombre)/8;
    printf("%d\t", aMostrar.id);
    printf("%s\t", aMostrar.nombre);
    for( int i=0; i<espaciadoNombre; i++ )
        printf("\t");
    printf("%d\t", aMostrar.poder);
}

void mostrarMovimientos( movimientoNodo* arbol )
{
    if ( arbol )
    {
        mostrarMovimientos( arbol->izquierda );
        imprimirMovimiento( arbol->movimiento );
        printf("\n");
        mostrarMovimientos( arbol->derecha );
    }
}

int estaElMovimientoEnArchivo( char* nombreArchivo, int id )
{
    int encontrado = 0;
    stMovimiento aux;
    FILE* archivo = fopen( nombreArchivo, "rb" );

    if(!archivo)
    {
        archivo = fopen( nombreArchivo, "wb" );
    }
    else
    {
        while( fread(&aux, sizeof(stMovimiento), 1, archivo) )
        {
            if( aux.id == id )
            {
                encontrado = 1;
            }
        }
    }

    fclose( archivo );

    return encontrado;
}

stMovimiento crearMovimiento()
{
    stMovimiento nuevoMovimiento;

    do
    {
        printf("\n\nID: ");
        scanf("%d", &nuevoMovimiento.id);
        while( getchar() != '\n' );

    }
    while( estaElMovimientoEnArchivo( ARCHIVO_MOVIMIENTOS, nuevoMovimiento.id ) );

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

movimientoNodo* creacionDeNuevoMovimiento( movimientoNodo* arbolDeMovimientos )
{
    stMovimiento nuevoMovimiento = crearMovimiento();

    movimientoNodo* nuevoNodo = crearNodoMovimiento( nuevoMovimiento );
    arbolDeMovimientos = agregarMovimientoAlArbol( arbolDeMovimientos, nuevoNodo );

    FILE* archivo = fopen( ARCHIVO_MOVIMIENTOS, "ab" );

    if( archivo )
    {
        fwrite(&nuevoMovimiento, sizeof(stMovimiento), 1, archivo);
    }

    fclose( archivo );

    return arbolDeMovimientos;
}

void encabezadoDeMostrarMovimientosPorTipo()
{
    printf("ID\tNOMBRE\t\t\t\tPODER\n\n");
}

void mostrarMovimientosPorTipo( movimientoNodo* arbolDeMovimientos, int tipoBuscado )
{
    if ( arbolDeMovimientos )
    {
        mostrarMovimientosPorTipo( arbolDeMovimientos->izquierda, tipoBuscado );
        if( (arbolDeMovimientos->movimiento).tipo == tipoBuscado )
        {
            imprimirMovimientoSinTipo( arbolDeMovimientos->movimiento );
            printf("\n");
        }
        mostrarMovimientosPorTipo( arbolDeMovimientos->derecha, tipoBuscado );
    }
}

movimientoNodo* mayorNodoPorId( movimientoNodo* arbol )
{
    if( arbol && arbol->derecha )
    {
        return mayorNodoPorId( arbol->derecha );
    }

    return arbol;
}

movimientoNodo* quitarMovimientoDeArbol ( movimientoNodo* arbol, int idEliminar )
{
    if ( arbol )
    {
        if( (arbol->movimiento).id > idEliminar )
        {
            arbol->izquierda = quitarMovimientoDeArbol( arbol->izquierda, idEliminar );
        }
        else if( (arbol->movimiento).id < idEliminar )
        {
            arbol->derecha = quitarMovimientoDeArbol( arbol->derecha, idEliminar );
        }
        else
        {
            if( !( arbol->izquierda || arbol->derecha ) )
            {
                free(arbol);
                arbol = NULL;
            }
            else if ( arbol->izquierda )
            {
                movimientoNodo* mayorNodoArbolIzquierdo = mayorNodoPorId( arbol->izquierda );
                arbol->movimiento = mayorNodoArbolIzquierdo->movimiento;
                arbol->izquierda = quitarMovimientoDeArbol( arbol->izquierda, (mayorNodoArbolIzquierdo->movimiento).id );
            }
            else
            {
                movimientoNodo* aux = arbol;
                arbol = arbol->derecha;
                free(aux);
                aux = NULL;
            }
        }
    }

    return arbol;
}

void borrarMovimientoDeBinario( int idMovimiento )
{
    FILE* archivo = fopen( ARCHIVO_MOVIMIENTOS, "rb+" );
    stMovimiento aux;

    if( archivo )
    {
        do
        {
            fread( &aux, sizeof(stMovimiento), 1, archivo );
        }
        while ( aux.id != idMovimiento && !feof( archivo ) );

        if( aux.id == idMovimiento )
        {
            aux.id = -1;
            fseek( archivo, -sizeof(stMovimiento), SEEK_CUR );
            fwrite( &aux, sizeof(stMovimiento), 1, archivo );
        }

        fclose( archivo );
    }
}

movimientoNodo* borradoDeMovimiento( movimientoNodo* arbol )
{
    int idBorrar = -1;

    printf("ID a borrar: ");
    scanf("%d", &idBorrar);
    limpiarBuffer();

    arbol = quitarMovimientoDeArbol( arbol, idBorrar );
    borrarMovimientoDeBinario( idBorrar );

    return arbol;
}

int obtenerPoder(movimientoNodo* arbol, int idMovimiento)
{
    int poder = 0;

    if(arbol)
    {
        if(arbol->movimiento.id == idMovimiento)
        {
            poder = arbol->movimiento.poder;
        }
        else if(arbol->movimiento.id > idMovimiento)
        {
            poder = obtenerPoder(arbol->izquierda, idMovimiento);
        }
        else
        {
            poder = obtenerPoder(arbol->derecha, idMovimiento);
        }
    }

    return poder;
}

char* mostrarMovimientoPelea(movimientoNodo * arbolMovimientos, int idBuscar)
{
    if(arbolMovimientos->movimiento.id == idBuscar)
    {
        return arbolMovimientos->movimiento.nombre;

    }
    else
    {
        if(arbolMovimientos->movimiento.id > idBuscar)
        {
            mostrarMovimientoPelea(arbolMovimientos->izquierda, idBuscar);
        }
        else
        {
            mostrarMovimientoPelea(arbolMovimientos->derecha, idBuscar);
        }

    }
}
