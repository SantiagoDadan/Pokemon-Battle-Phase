#include "pokemon.h"

modeloDePokemon crearModeloPokemon()
{
    modeloDePokemon pokemon;
    int i = 0;
    char opcion = 0;

    printf("\nID Pokedex: ");
    scanf("%d", &pokemon.idPokedex);
    limpiarBuffer();

    printf("Nombre: ");
    scanf("%[^\n]s", pokemon.nombre);
    limpiarBuffer();

    printf("Tipo (1): ");
    scanf("%d", &pokemon.idTipo[0]);
    limpiarBuffer();

    printf("Tipo (2): ");       // -1 en el segundo tipo si no lo tiene
    scanf("%d", &pokemon.idTipo[1]);
    limpiarBuffer();

    printf("Estadistica de salud: ");
    scanf("%d", &pokemon.estadSalud);
    limpiarBuffer();

    printf("Estadistica de ataque: ");
    scanf("%d", &pokemon.estadAtaque);
    limpiarBuffer();

    printf("Estadistica de defensa: ");
    scanf("%d", &pokemon.estadDefensa);
    limpiarBuffer();

    printf("Estadistica de velocidad: ");
    scanf("%d", &pokemon.estadVelocidad);
    limpiarBuffer();

    printf("ID siguiente evolucion: "); // -1 si no tiene
    scanf("%d", &pokemon.idSiguienteEvolucion);
    limpiarBuffer();

    do
    {
        printf("ID moviminetos aptos: ");
        scanf("%d", &pokemon.idMovimientosAptos[i]);
        limpiarBuffer();
        i++;

        printf("\nContinuar? [s/N] ");
        opcion = getchar();
    }
    while(opcion == 's' || opcion == 'S');

    pokemon.idMovimientosAptos[i] = -1;

    return pokemon;
}

void mostrarUnModeloPokemon(modeloDePokemon pokemon)
{
    int tabulaciones = 2 - strlen(pokemon.nombre)/8;
    int cont = contarMovAptos(pokemon);

    printf("%d", pokemon.idPokedex);
    printf("\t%s", pokemon.nombre);
    for( int i=0; i<tabulaciones; i++)
        printf("\t");
    printf("\t%d", pokemon.idTipo[0]);
    if(pokemon.idTipo[1] != -1)
    {
        printf("-%d", pokemon.idTipo[1]);
    }
    printf("\t%d", pokemon.estadSalud);
    printf("\t%d", pokemon.estadAtaque);
    printf("\t%d", pokemon.estadDefensa);
    printf("\t%d", pokemon.estadVelocidad);
    printf("\t\t%d\t\t", pokemon.idSiguienteEvolucion);

    for(int i = 0; i < cont; i++)
    {
        printf("%d ", pokemon.idMovimientosAptos[i]);
    }
    printf("\n");
}

int contarMovAptos(modeloDePokemon pokemon)
{
    int i = 0;

    while(pokemon.idMovimientosAptos[i] != -1 && i < MAX_LENGTH)
        i++;

    return i;
}

void guardarModeloPokemon(modeloDePokemon pokemon)
{
    FILE *archivo = fopen(ARCHIVO_POKEMONS, "ab");

    if(archivo)
    {
        fwrite(&pokemon, sizeof(modeloDePokemon), 1, archivo);
        fclose(archivo);
    }
}

void cargarModeloArchivo()
{
    char opcion = 's';

    while(opcion == 's' || opcion == 'S')
    {
        limpiarPantalla();
        guardarModeloPokemon(crearModeloPokemon());

        printf("\nContinuar? [s/N] ");
        limpiarBuffer();
        opcion = getchar();
    }
}

void mostrarModelos()
{
    FILE *archivo = fopen(ARCHIVO_POKEMONS, "rb");
    modeloDePokemon pokemon;

    printf("\t\t\t\t Mostrando Pokemones: \n\n");
    if(archivo)
    {
        while(fread(&pokemon, sizeof(modeloDePokemon), 1, archivo) != 0)
        {
            mostrarUnModeloPokemon(pokemon);
        }
    }
    else
    {
        archivo = fopen( ARCHIVO_POKEMONS, "wb" );
    }

    fclose(archivo);
}

nodoRegistroPokemon *inicArbolModelos()
{
    return NULL;
}

nodoRegistroPokemon *crearNodoModelo(modeloDePokemon pokemon)
{
    int cont = contarMovAptos(pokemon);
    nodoRegistroPokemon *aux = (nodoRegistroPokemon*)malloc(sizeof(nodoRegistroPokemon));

    aux->pokemonBase.idPokedex = pokemon.idPokedex;
    strcpy(aux->pokemonBase.nombre, pokemon.nombre);
    aux->pokemonBase.idTipo[0] = pokemon.idTipo[0];
    aux->pokemonBase.idTipo[1] = pokemon.idTipo[1];
    aux->pokemonBase.estadSalud = pokemon.estadSalud;
    aux->pokemonBase.estadAtaque = pokemon.estadAtaque;
    aux->pokemonBase.estadDefensa = pokemon.estadDefensa;
    aux->pokemonBase.estadVelocidad = pokemon.estadVelocidad;
    aux->pokemonBase.idSiguienteEvolucion = pokemon.idSiguienteEvolucion;
    for(int i = 0; i < cont+1; i++) // +1 para que tambien tome el -1 que sirve de limite
    {
        aux->pokemonBase.idMovimientosAptos[i] = pokemon.idMovimientosAptos[i];
    }

    aux->derecha = NULL;
    aux->izquierda = NULL;

    return aux;
}

nodoRegistroPokemon *insertarModeloArbol(nodoRegistroPokemon *arbol, modeloDePokemon pokemon)
{
    nodoRegistroPokemon* nuevoNodo = crearNodoModelo( pokemon );

    if(arbol == NULL)
    {
        arbol = nuevoNodo;
    }
    else if(pokemon.idPokedex > arbol->pokemonBase.idPokedex)
    {
        arbol->derecha = insertarModeloArbol(arbol->derecha, pokemon);
    }
    else if(pokemon.idPokedex < arbol->pokemonBase.idPokedex)
    {
        arbol->izquierda = insertarModeloArbol(arbol->izquierda, pokemon);
    }
    else
    {
        printf("ERROR: ID POKEMON REPETIDO\n");
        free(nuevoNodo);
    }

    return arbol;
}

void preOrden(nodoRegistroPokemon *arbol)
{
    if(arbol != NULL)
    {
        preOrden(arbol->izquierda);
        mostrarUnModeloPokemon(arbol->pokemonBase);
        preOrden(arbol->derecha);
    }
}

modeloDePokemon buscarPokemonPorID ( nodoRegistroPokemon* arbol, int idPokedex )
{
    modeloDePokemon poke;

    if( arbol )
    {
        if( (arbol->pokemonBase).idPokedex == idPokedex )
        {
            poke = arbol->pokemonBase;
        }
        else if( (arbol->pokemonBase).idPokedex > idPokedex )
        {
            poke = buscarPokemonPorID( arbol->izquierda, idPokedex );
        }
        else
        {
            poke = buscarPokemonPorID( arbol->derecha, idPokedex );
        }
    }
    else
    {
        printf("ERROR: POKEMON INEXISTENTE. VUELVA A DESCARGAR EL JUEGO O COMUNIQUESE CON EL DESARROLLADOR\n");
    }

    return poke;
}

int solicitarID()
{
    int idAbuscar;

    printf("\nIngrese el ID (pokedex) del pokemon a modificar:\n\n");

    scanf("%d", &idAbuscar);

    return idAbuscar;
}

void modificarNombre()
{
    int ID, flag = 0;

    char nuevoNombre[20];

    modeloDePokemon aux;

    FILE * archi = fopen(ARCHIVO_POKEMONS, "r+b");

    if(archi != NULL)
    {
        ID = solicitarID();

        while(!flag && fread(&aux, sizeof(modeloDePokemon), 1, archi) > 0)
        {
            if(aux.idPokedex == ID)
            {
                printf("\nIngrese el nuevo nombre:\n\n");
                limpiarBuffer();
                scanf("%[^\n]s", &nuevoNombre);

                strcpy(aux.nombre, nuevoNombre);

                fseek(archi, sizeof(modeloDePokemon)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(modeloDePokemon), 1, archi);
                limpiarPantalla();
                printf("\nNombre modificado correctamente!!\n\n");

                mostrarUnModeloPokemon(aux);
                limpiarBuffer();
                pausa();
                flag = 1;
            }
        }

        fclose(archi);
    }
}

void modificarStats()
{
    int ID, flag = 0;

    modeloDePokemon aux;

    FILE * archi = fopen(ARCHIVO_POKEMONS, "r+b");

    if(archi != NULL)
    {
        ID = solicitarID();

        while(!flag && fread(&aux, sizeof(modeloDePokemon), 1, archi) > 0)
        {
            if(aux.idPokedex == ID)
            {
                printf("\nIngrese el nuevo stat de salud:\n\n");
                scanf("%d", &aux.estadSalud);

                printf("\nIngrese el nuevo stat de ataque:\n\n");
                scanf("%d", &aux.estadAtaque);

                printf("\nIngrese el nuevo stat de defenza:\n\n");
                scanf("%d", &aux.estadDefensa);

                printf("\nIngrese el nuevo stat de velocidad:\n\n");
                scanf("%d", &aux.estadVelocidad);

                fseek(archi, sizeof(modeloDePokemon)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(modeloDePokemon), 1, archi);
                limpiarPantalla();
                printf("\nStats modificados correctamente!!\n\n");

                mostrarUnModeloPokemon(aux);
                limpiarBuffer();
                pausa();
                flag = 1;
            }
        }

        fclose(archi);
    }
}

void modificarTipos()
{
    int ID, flag = 0;

    modeloDePokemon aux;

    FILE * archi = fopen(ARCHIVO_POKEMONS, "r+b");

    if(archi != NULL)
    {
        ID = solicitarID();

        while(!flag && fread(&aux, sizeof(modeloDePokemon), 1, archi) > 0)
        {
            if(aux.idPokedex == ID)
            {
                printf("\nIngrese el nuevo tipo (1):\n\n");
                scanf("%d", &aux.idTipo[0]);

                printf("\nIngrese el nuevo tipo (2):\n\n");
                scanf("%d", &aux.idTipo[1]);

                fseek(archi, sizeof(modeloDePokemon)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(modeloDePokemon), 1, archi);
                limpiarPantalla();
                printf("\nTipos modificados correctamente!!\n\n");

                mostrarUnModeloPokemon(aux);
                limpiarBuffer();
                pausa();
                flag = 1;
            }
        }

        fclose(archi);
    }
}

void modificarAtaques()
{
    int ID, flag = 0, i = 0;

    char control = 's';

    modeloDePokemon aux;

    int nuevosAtaques[MAX_LENGTH];

    FILE * archi = fopen(ARCHIVO_POKEMONS, "r+b");

    if(archi != NULL)
    {
        ID = solicitarID();

        while(!flag && fread(&aux, sizeof(modeloDePokemon), 1, archi) > 0)
        {
            if(aux.idPokedex == ID)
            {
                while(i < MAX_LENGTH && control == 's' || control == 'S')
                {
                    printf("\nNuevo Ataque:\n\n");
                    scanf("%d", &nuevosAtaques[i]);

                    i++;

                    printf("\nSeguir cargando? (s/n)\n>");
                    limpiarBuffer();
                    scanf("%c", &control);
                }

                for(int j = 0; j < i; j++)
                {
                    aux.idMovimientosAptos[j] = nuevosAtaques[j];
                }

                aux.idMovimientosAptos[i] = -1;

                fseek(archi, sizeof(modeloDePokemon)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(modeloDePokemon), 1, archi);
                limpiarPantalla();
                printf("\nMovimientos modificados correctamente!!\n\n");

                mostrarUnModeloPokemon(aux);
                limpiarBuffer();
                pausa();
                flag = 1;
            }
        }

        fclose(archi);
    }
}

