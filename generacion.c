#include "generacion.h"

void menuGeneraciones()
{
    nodoGeneracion *listaGeneracion = inicListaGeneracion();
    nodoRegistroPokemon *arbolPokemones = NULL; // Previamente "inicArbolMovimientos();" y resultaba en incompatibilidad de tipos

    listaGeneracion = cargarGeneracionDesdeArchivo(listaGeneracion);
    cargarPokemonArbolDesdeArchivo(listaGeneracion);
    int opcion;
    do
    {
        limpiarPantalla();
        mostrarMenuGeneraciones();
        scanf("%d", &opcion);
        limpiarBuffer();
        limpiarPantalla();
        switch(opcion)
        {
        case 1:
            cargarGeneracionArchivo();
            break;
        case 2:
            mostrarGeneraciones();
            printf("\n\n");
            pausa();
            break;
        case 3:
            encabezadoDeMostrarPokemons();
            mostrarPokemons( listaGeneracion, 0, 0 ); // Los 0 implican que no hay filtro por tipo ni generacion
            printf("\n\n");
            pausa();
            break;
        case 0:

            break;

        default:
            break;
        }

    }
    while(opcion != 0);
}

void mostrarMenuGeneraciones()
{
    printf("Generaciones: \n\n");
    printf("\t1 - Cargar Generaciones\n");
    printf("\t2 - Mostrar Generaciones\n");
    printf("\t3 - Mostrar Pokemones\n");
    printf("\t0 - Volver\n");
    printf("\n> ");
}

stGeneracion crearGeneracion()
{
    stGeneracion generacion;

    printf("Numero de generacion: ");
    limpiarBuffer();
    scanf("%d", &generacion.numeroDeGeneracion);

    printf("Cantidad de pokemones: ");
    limpiarBuffer();
    scanf("%d", &generacion.cantidadDePokemons);

    generacion.primerNumeroEnPokedex = calcularNumeroPokedex(generacion.cantidadDePokemons);

    return generacion;
}

int calcularNumeroPokedex(int cant)
{
    FILE *archivo = fopen(ARCHIVO_GENERACIONES, "rb");
    stGeneracion gen;
    int numero = 0;

    if(!archivo)
    {
        numero = 1;
    }
    else
    {
        fseek(archivo,-1 * sizeof(stGeneracion), SEEK_END);
        fread(&gen, sizeof(stGeneracion), 1, archivo);
        numero = gen.primerNumeroEnPokedex + gen.cantidadDePokemons;
    }

    return numero;
}

void guardarGeneracion(stGeneracion gen)
{
    FILE *archivo = fopen(ARCHIVO_GENERACIONES, "ab");

    if(archivo)
    {
        fwrite(&gen, sizeof(stGeneracion), 1, archivo);
        fclose(archivo);
    }
}

void cargarGeneracionArchivo()
{
    stGeneracion generacion;
    char opcion = 's';

    while(opcion != 's')
    {
        limpiarPantalla();
        guardarGeneracion(crearGeneracion());

        printf("\n\tseguir cargando? (s / n)\n");
        scanf("%d", &opcion);
    }
}

void mostrarUnaGeneracion(stGeneracion generacion)
{
    printf("Numero de generacion: %d\n", generacion.numeroDeGeneracion);
    printf("Primer numero de pokedex: %d\n", generacion.primerNumeroEnPokedex );
    printf("Cantidad de pokemones: %d\n", generacion.cantidadDePokemons);
    printf("----------------------------------\n");
}

void mostrarGeneraciones()
{
    FILE *archivo = fopen(ARCHIVO_GENERACIONES, "rb");
    stGeneracion gen;

    printf("\t\t\t\t Mostrando Generaciones: \n\n");
    if(archivo)
    {
        while(fread(&gen, sizeof(stGeneracion), 1, archivo) != 0)
        {
            mostrarUnaGeneracion(gen);
        }

        fclose(archivo);
    }
}

void mostrarGeneracionesLista(nodoGeneracion *lista)
{
    while(lista != NULL)
    {
        mostrarUnaGeneracion(lista->generacion);
        lista = lista->siguiente;
    }
}

nodoGeneracion *inicListaGeneracion()
{
    return NULL;
}

nodoGeneracion *crearNodoListaGen(stGeneracion generacion)
{
    nodoGeneracion *aux = (nodoGeneracion*)malloc(sizeof(nodoGeneracion));

    aux->generacion.numeroDeGeneracion = generacion.numeroDeGeneracion;
    aux->generacion.primerNumeroEnPokedex = generacion.primerNumeroEnPokedex;
    aux->generacion.cantidadDePokemons = generacion.cantidadDePokemons;

    aux->arbolPokemons = NULL; //inicArbolMovimientos();

    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodoGeneracion *agregarAlPpioGen(nodoGeneracion *lista, nodoGeneracion *nuevo)
{
    nuevo->siguiente = lista;

    if(lista != NULL)
    {
        lista->anterior = nuevo;
    }

    return nuevo;
}

nodoGeneracion *agregarGenEnOrden(nodoGeneracion *lista, nodoGeneracion *nuevo)
{
    nodoGeneracion *aux;
    nodoGeneracion *anterior;

    if(lista == NULL)
    {
        lista = nuevo;
    }
    else if(nuevo->generacion.numeroDeGeneracion < lista->generacion.numeroDeGeneracion)
    {
        lista = agregarAlPpioGen(lista, nuevo);
    }
    else
    {
        aux = lista;
        while(aux != NULL && nuevo->generacion.numeroDeGeneracion > lista->generacion.numeroDeGeneracion)
        {
            anterior = aux;
            aux =aux->siguiente;
        }

        anterior->siguiente = nuevo;
        nuevo->anterior = anterior;
        nuevo->siguiente = aux;
        if(aux != NULL)
        {
            aux->anterior = nuevo;
        }
    }

    return lista;
}

nodoGeneracion *cargarGeneracionDesdeArchivo(nodoGeneracion *lista)
{
    FILE *archivo = fopen(ARCHIVO_GENERACIONES, "rb");
    stGeneracion gen;
    nodoGeneracion *nuevo;

    if(archivo)
    {
        while(fread(&gen, sizeof(stGeneracion), 1, archivo) != 0)
        {
            nuevo = crearNodoListaGen(gen);
            lista = agregarGenEnOrden(lista, nuevo);
        }
    }
    else
    {
        archivo = fopen( ARCHIVO_GENERACIONES, "wb" );
    }

    fclose(archivo);

    return lista;
}

void cargarPokemonArbolDesdeArchivo(nodoGeneracion *lista)
{
    FILE *archivo = fopen(ARCHIVO_POKEMONS, "rb");
    modeloDePokemon pokemon;
    nodoGeneracion* generacionDelPokemon;

    if(archivo)
    {
        while(fread(&pokemon, sizeof(modeloDePokemon), 1, archivo) != 0)
        {
            generacionDelPokemon = buscarGeneracion(lista, pokemon.idPokedex);
            generacionDelPokemon->arbolPokemons = insertarModeloArbol(generacionDelPokemon->arbolPokemons, pokemon);
        }
        fclose(archivo);
    }
}

nodoGeneracion *buscarGeneracion(nodoGeneracion *lista, int idPokedex)
{
    if( lista )
    {
        // Por ejemplo, en caso de haber tres pokemon en la generacion 1,
        // primerNumero es 1 + cantidad que es 3 - 1 = 3 (ultimo id en pokedex)
        int ultimoPokedexID = lista->generacion.primerNumeroEnPokedex + lista->generacion.cantidadDePokemons - 1;

        if ( idPokedex > ultimoPokedexID )
        {
            return buscarGeneracion( lista->siguiente, idPokedex );
        }
        else
        {
            return lista;
        }
    }

    return NULL;
}

int compararPokemonConTipo( modeloDePokemon poke, int tipo )
{
    return poke.idTipo[0] == tipo || poke.idTipo[1] == tipo;
}

int compararGeneracionConNumero( stGeneracion generacion, int numero )
{
    return generacion.numeroDeGeneracion == numero;
}

void mostrarGeneracion( nodoRegistroPokemon* arbolPokemons, int tipo )
{
    if( arbolPokemons )
    {
        int hayFiltro = tipo > 0 && tipo < 19;
        int esElTipoBuscado = compararPokemonConTipo( arbolPokemons->pokemonBase, tipo );
        int hayQueMostrar = !hayFiltro || esElTipoBuscado;

        mostrarGeneracion( arbolPokemons->izquierda, tipo );
        if ( hayQueMostrar )
        {
            mostrarUnModeloPokemon( arbolPokemons->pokemonBase );
        }
        mostrarGeneracion( arbolPokemons->derecha, tipo );
    }
}

void encabezadoDeMostrarPokemons()
{
    printf("ID\tNombre\t\t\tTipos\tSalud\tAtaque\tDefensa\tVelocidad\tID Evolucion\tMovimientos\n\n");
}

void mostrarPokemons( nodoGeneracion* lista, int generacion, int tipo )
{
    if ( lista )
    {
        int hayFiltroGeneracional = generacion > 0;
        int esGeneracionBuscada = compararGeneracionConNumero( lista->generacion, generacion );
        int hayQueMostrar = !hayFiltroGeneracional || esGeneracionBuscada;

        if( hayQueMostrar )
        {
            mostrarGeneracion( lista->arbolPokemons, tipo );
        }
        mostrarPokemons( lista->siguiente, generacion, tipo );
    }
}

modeloDePokemon buscarPokemonEnGeneraciones( nodoGeneracion* listaGen, int idPokedex )
{
    stGeneracion gen;
    nodoGeneracion* segLista = listaGen;
    modeloDePokemon busqueda;
    int bandera = 0;

    while(segLista && !bandera) {
        gen = segLista->generacion;

        if( idPokedex < ( gen.primerNumeroEnPokedex + gen.cantidadDePokemons ) )
        {
            busqueda = buscarPokemonPorID(listaGen->arbolPokemons, idPokedex);
            bandera = 1;
        }
        else
        {
            segLista = segLista->siguiente;
        }
    }

    if(!bandera) {
        busqueda.idPokedex = -1;
    }

    return busqueda;
}
