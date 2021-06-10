#include "stpoke.h"

void obtenerNaturaleza(pokemonDeJugador *nuevoPoke)
{
    srand(time(0));

    int randomIndex = rand() % 25 + 1;

    char listaNaturalezas[25][8] =
    {
        "Activa",  "Afable",  "Agitada", "Alegre", "Alocada",
        "Amable",  "Audaz",   "Cauta",   "Dócil",   "Firme",
        "Floja",    "Fuerte",   "Grosera", "Huraña", "Ingenua",
        "Mansa",    "Miedosa", "Modesta", "Osada",  "Pícara",
        "Plácida", "Rara", "Serena", "Seria", "Timida"
    };

    strcpy(nuevoPoke->naturaleza, listaNaturalezas[randomIndex]);
}

void obtenerGenero(pokemonDeJugador *nuevoPoke)
{
    srand(time(0));

    nuevoPoke->genero = rand() % 2;
}

void obtenerSetMovimientos(pokemonDeJugador *nuevoPoke, modeloDePokemon base)
{
    srand(time(0));
    int cantidad = contarMovAptos(base);
    int indiceRandom1 = rand() % cantidad;
    int indiceRandom2;
    do
    {
        indiceRandom2 = rand() % cantidad;
    }
    while (indiceRandom1 == indiceRandom2);

    nuevoPoke->idMovimientosDisponibles[0] =
        base.idMovimientosAptos[indiceRandom1];
    nuevoPoke->idMovimientosDisponibles[1] =
        base.idMovimientosAptos[indiceRandom2];
}

pokemonDeJugador crearPokemonDeJugador(nodoGeneracion *lista,
                                       int idPokedex)
{
    pokemonDeJugador nuevoPoke;
    modeloDePokemon base = buscarPokemonEnGeneraciones(lista, idPokedex);

    nuevoPoke.idPokedex = idPokedex;
    strcpy(nuevoPoke.nombre, base.nombre);
    strcpy(nuevoPoke.apodo,
           ""); // El apodo se asigna fuera de la creacion, en el menu.
    obtenerGenero(&nuevoPoke);
    obtenerNaturaleza(&nuevoPoke);
    nuevoPoke.idTipo[0] = base.idTipo[0];
    nuevoPoke.idTipo[1] = base.idTipo[1];
    nuevoPoke.estadSalud = base.estadSalud;
    nuevoPoke.estadAtaque = base.estadAtaque;
    nuevoPoke.estadDefensa = base.estadDefensa;
    nuevoPoke.estadVelocidad = base.estadVelocidad;
    nuevoPoke.experienceObtenida = 0;
    obtenerSetMovimientos(&nuevoPoke, base);

    return nuevoPoke;
}

int pelear(pokemonDeJugador poke1, pokemonDeJugador poke2, tipoNodo *listaTipos,
           movimientoNodo *arbolMoviminetos, nodoGeneracion *listaGen, int* ganador)
{
    *ganador = 0; // 0 gana el rival, 1 gana el jugador
    int turno = calcularTurno(poke1, poke2);
    int danio = 0, opcion, captura = 0, flag = 0;
    int psBasePK1 = poke1.estadSalud, psBasePK2 = poke2.estadSalud;

    while (poke1.estadSalud > 0 && poke2.estadSalud > 0 && !flag &&
            captura != 1)
    {
        pausa();
        limpiarPantalla();
        imprimirPokemonSalvaje(poke2, psBasePK2, poke2.estadSalud);
        imprimirPokemonSalvaje(poke1, psBasePK1, poke1.estadSalud);

        printf("\n\n\t1 - Pelear\n");
        printf("\t2 - Lanzar pokeball\n");
        printf("\t3 - Huir\n\n>");

        do
        {
            limpiarBuffer();
            scanf("%d", &opcion);

            switch (opcion)
            {
            case 1:

                if (turno == 1)
                {
                    danio = realizarAtaque(poke1, poke2, listaTipos, arbolMoviminetos);
                    poke2.estadSalud -= danio;
                    if (poke2.estadSalud > 0)
                    {
                        danio = ataqueEnemigo(poke2, poke1, listaTipos, arbolMoviminetos);
                        poke1.estadSalud -= danio;
                    }
                }
                else if (turno == 2)
                {
                    danio = ataqueEnemigo(poke2, poke1, listaTipos, arbolMoviminetos);
                    poke1.estadSalud -= danio;
                    if (poke1.estadSalud > 0)
                    {
                        danio = realizarAtaque(poke1, poke2, listaTipos, arbolMoviminetos);
                        poke2.estadSalud -= danio;
                    }
                }

                break;

            case 2:

                captura = lanzarPokeball(poke2);

                if (captura == 1)
                {
                    printf("\n%s capturado!!\n", poke2.nombre);

                }
                else
                {
                    printf("\nQue pena, te falto poco!!\n");
                    danio = ataqueEnemigo(poke2, poke1, listaTipos, arbolMoviminetos);
                    poke1.estadSalud -= danio;
                }

                break;

            case 3:

                printf("\nHuiste con exito!!\n\n");
                flag = 1;
                break;

            default:

                printf("Opcion incorrecta!!\n");
                break;
            }

        }
        while (opcion != 1 && opcion != 2 && opcion != 3);
    }

    if (poke1.estadSalud <= 0)
    {
        printf("\n%s se debilito, %s es el ganador!!", poke1.nombre, poke2.nombre);
        ganador = 0;
    }
    else if (poke2.estadSalud <= 0)
    {
        printf("\n%s se debilito, %s es el ganador!!", poke2.nombre, poke1.nombre);
        *ganador = 1;
    }

    return captura;
}

int pelearXvX(pokemonDeJugador pokesElegidos[], pokemonDeJugador contrincante[], int cantPokes, tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos, nodoGeneracion *listaGen, int ganador) {
    int i = 0, j = 0;
    int psPokesEntrenador[cantPokes];

    for( int k=0; k<cantPokes; k++ ) {
      psPokesEntrenador[k] = pokesElegidos[k].estadSalud;
    }

    int psBasePK1 = pokesElegidos[i].estadSalud, psBasePK2 = contrincante[j].estadSalud;

    ganador = 0; // 0 gana el rival, 1 gana el jugador

    while(i < cantPokes && j < cantPokes)
    {
        int turno = calcularTurno(pokesElegidos[i], contrincante[j]);
        int danio = 0, opcion, captura = 0, flag = 0;

        while (psPokesEntrenador[i] > 0 && contrincante[j].estadSalud > 0)
        {
            limpiarBuffer();
            pausa();
            limpiarPantalla();
            imprimirPokemonSalvaje(contrincante[j], psBasePK2, contrincante[j].estadSalud);
            imprimirPokemonSalvaje(pokesElegidos[i], psBasePK1, psPokesEntrenador[i]);

            do
            {
                printf("\n\n\t1 - Pelear\n");
                scanf("%d", &opcion);

                switch (opcion)
                {
                case 1:

                    if (turno == 1)
                    {
                        danio = realizarAtaque(pokesElegidos[i], contrincante[j], listaTipos, arbolMoviminetos);
                        contrincante[j].estadSalud -= danio;
                        if (contrincante[j].estadSalud > 0)
                        {
                            danio = ataqueEnemigo(contrincante[j], pokesElegidos[i], listaTipos, arbolMoviminetos);
                            psPokesEntrenador[i] -= danio;
                        }
                    }
                    else if (turno == 2)
                    {
                        danio = ataqueEnemigo(contrincante[j], pokesElegidos[i], listaTipos, arbolMoviminetos);
                        psPokesEntrenador[i] -= danio;
                        if (pokesElegidos[i].estadSalud > 0)
                        {
                            danio = realizarAtaque(pokesElegidos[i], contrincante[j], listaTipos, arbolMoviminetos);
                            contrincante[j].estadSalud -= danio;
                        }
                    }

                    break;

                default:

                    printf("Opcion incorrecta!!\n");
                    break;
                }

            }
            while (opcion != 1);
        }
        limpiarBuffer();
        pausa();
        limpiarPantalla();

        if (psPokesEntrenador[i] <= 0)
        {
            limpiarBuffer();
            printf("\n%s se debilito!!", pokesElegidos[i].nombre);
            i++;
            psBasePK1 = psPokesEntrenador[i];
            pausa();
            limpiarPantalla();
            if(i < cantPokes)
            {
                printf("\n\n\tTu: Sal %s !!\n\n", pokesElegidos[i].nombre);
            }else
            {
                printf("\nEl contrincante gana!!\n\n");
            }
        }
        else if (contrincante[j].estadSalud <= 0)
        {
            limpiarBuffer();
            printf("\n%s se debilito!!", contrincante[j].nombre);
            j++;
            psBasePK2 = contrincante[j].estadSalud;
            pausa();
            limpiarPantalla();
            if(j < cantPokes)
            {
                printf("\n\n\tContrincante: Sal %s !!\n\n", contrincante[j].nombre);
            }else
            {
                printf("\nTu ganas!!\n\n");
            }
        }
    }

    if(i < cantPokes)
    {
        ganador = 1;
    }else
    {
        ganador = 0;
    }

    return ganador;
}

int calcularTurno(pokemonDeJugador poke1, pokemonDeJugador poke2)
{
    int turno = 0;
    if (poke1.estadVelocidad > poke2.estadVelocidad)
    {
        turno = 1;
    }
    else if (poke2.estadVelocidad > poke1.estadVelocidad)
    {
        turno = 2;
    }
    else
    {
        turno = rand() % 2 + 1;
    }

    return turno;
}
int ataqueEnemigo(pokemonDeJugador atacante, pokemonDeJugador receptor,
                  tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos)
{
    srand(time(NULL));

    int indiceAtaque = rand() % 1;

    int movimiento = atacante.idMovimientosDisponibles[indiceAtaque];
    int danio = pokemonAtaca(atacante, receptor, movimiento, listaTipos,
                             arbolMoviminetos);

    printf("\nEl %s enemigo utilizo %s", atacante.nombre,
           mostrarMovimientoPelea(arbolMoviminetos, movimiento));
    printf("\nEl danio realizado fue: %d\n", danio);

    return danio;
}

int realizarAtaque(pokemonDeJugador atacante, pokemonDeJugador receptor,
                   tipoNodo *listaTipos, movimientoNodo *arbolMoviminetos)
{
    int movimiento = elegirMovimiento(atacante, arbolMoviminetos);
    int danio = pokemonAtaca(atacante, receptor, movimiento, listaTipos,
                             arbolMoviminetos);

    printf("\n%s utilizo %s", atacante.nombre,
           mostrarMovimientoPelea(arbolMoviminetos, movimiento));
    printf("\nEl danio realizado fue: %d\n", danio);

    return danio;
}

int elegirMovimiento(pokemonDeJugador atacante,
                     movimientoNodo *arbolMoviminetos)
{
    int movimiento = 0;
    int opcion = 0;

    printf("\n\t1 - %s\n",
           mostrarMovimientoPelea(arbolMoviminetos,
                                  atacante.idMovimientosDisponibles[0]));
    printf("\t2 - %s",
           mostrarMovimientoPelea(arbolMoviminetos,
                                  atacante.idMovimientosDisponibles[1]));
    tomarOpcion(&opcion);
    switch (opcion)
    {
    case 1:
        movimiento = atacante.idMovimientosDisponibles[0];
        break;
    case 2:
        movimiento = atacante.idMovimientosDisponibles[1];
        break;
    }

    return movimiento;
}

int pokemonAtaca(pokemonDeJugador atacante, pokemonDeJugador receptor,
                 int idMovimiento, tipoNodo *listaTipos,
                 movimientoNodo *arbolMovimientos)
{
    stMovimiento movimiento = buscarMovimiento(arbolMovimientos, idMovimiento);
    float efectividad = calcularEfectividadDelAtaque(
                            listaTipos, movimiento.tipo, receptor.idTipo[0], receptor.idTipo[1]);
    int ataque = atacante.estadAtaque;
    int poder = movimiento.poder;
    int defensa = receptor.estadDefensa;
    int nivel = atacante.experienceObtenida;

    int danio = 0.01 * efectividad *
                ((((0.01 * nivel + 1) * ataque * poder) / 80 * defensa) + 2);

    return danio;
}

int pokemonRandom(nodoGeneracion *lista)
{
    int rta;

    srand(time(NULL));

    int starterSIoNO = rand() % 9 + 1;

    if (starterSIoNO <= 4)
    {
        rta = (rand() % 58) + 1;
    }
    else
    {
        rta = (rand() % 49) + 10;
    }

    return rta;
}

// Si se pasa la lista de tipos, esta funcion resulta mas simple y flexible
// utilizando la funcion de obtener tipo.
char *devolverTipo(pokemonDeJugador aux, int nroTipo)
{
    char *tipos[20] = {"-",         "Acero",    "Agua",   "Bicho",    "Dragon",
                       "Electrico", "Fantasma", "Fuego",  "Hada",     "Hielo",
                       "Lucha",     "Normal",   "Planta", "Psiquico", "Roca",
                       "Siniestro", "Tierra",   "Veneno", "Volador"
                      };

    int indiceTipo = aux.idTipo[nroTipo];

    return indiceTipo > 0 && indiceTipo < 19 ? tipos[indiceTipo] : "-";
}

int calcularTotalStats(pokemonDeJugador poke)
{
    return poke.estadAtaque + poke.estadDefensa + poke.estadSalud +
           poke.estadVelocidad;
}

int estadisticaSubir(pokemonDeJugador poke, int totalEstadisticas)
{
    srand(time(0));

    int stat = rand() % totalEstadisticas;

    if (stat < poke.estadAtaque)
    {
        stat = 1;
    }
    else if (stat < poke.estadDefensa + poke.estadAtaque)
    {
        stat = 2;
    }
    else if (stat < poke.estadSalud + poke.estadDefensa + poke.estadAtaque)
    {
        stat = 3;
    }
    else
    {
        stat = 4;
    }

    return stat;
}

void sumarExperienciaAPokemon(pokemonDeJugador *poke, int experiencia)
{
    int totalStats = calcularTotalStats(*poke);
    int stat;

    poke->experienceObtenida += experiencia;

    while (experiencia--)
    {
        stat = estadisticaSubir(*poke, totalStats);

        switch (stat)
        {
        case 1:
            poke->estadAtaque++;
            break;
        case 2:
            poke->estadDefensa++;
            break;
        case 3:
            poke->estadSalud++;
            break;
        case 4:
            poke->estadVelocidad++;
            break;
        }

        totalStats++;
    }
}

int existeEvolucionSiguiente(nodoGeneracion *listaGen, int idPokedex)
{
    modeloDePokemon poke =
        buscarPokemonEnGeneraciones(listaGen, idPokedex);

    return poke.idSiguienteEvolucion > 0 ? 1 : 0;
}

void evolucionarPokemon(nodoGeneracion *listaGen, pokemonDeJugador *poke)
{
    modeloDePokemon modeloActual =
        buscarPokemonEnGeneraciones(listaGen, poke->idPokedex);
    modeloDePokemon modeloEvolucion =
        buscarPokemonEnGeneraciones(listaGen, modeloActual.idSiguienteEvolucion);

    poke->idPokedex = modeloEvolucion.idPokedex;
    strcpy(poke->nombre, modeloEvolucion.nombre);
    poke->idTipo[0] = modeloEvolucion.idTipo[0];
    poke->idTipo[1] = modeloEvolucion.idTipo[1];
    poke->estadAtaque = modeloEvolucion.estadAtaque;
    poke->estadDefensa = modeloEvolucion.estadDefensa;
    poke->estadSalud = modeloEvolucion.estadSalud;
    poke->estadVelocidad = modeloEvolucion.estadVelocidad;
    obtenerSetMovimientos(poke, modeloEvolucion);

    // Con esto se compensa si un poke mejoro mucho sin evolucionar antes de
    // conseguir la evolucion
    if (poke->experienceObtenida > 100)
    {
        int compensacion = poke->experienceObtenida - 100;
        sumarExperienciaAPokemon(poke, compensacion);
        poke->experienceObtenida -= compensacion;
    }
}

int hayEvolucion(nodoGeneracion *listaGen, pokemonDeJugador *poke)
{
    srand(time(0));

    int ocurreEvolucion = 0;

    if( existeEvolucionSiguiente(listaGen, poke->idPokedex) )
    {
        ocurreEvolucion = (rand() % 100) < 4 ? 1 : 0;

        if (ocurreEvolucion)
        {
            printf("\n%s EVOLUCIONO A ", poke->nombre);
            evolucionarPokemon(listaGen, poke);
            printf("%s\n", poke->nombre);
        }
    }

    return ocurreEvolucion;
}

int calcularExperienciaRecompensa(pokemonDeJugador pokemonAdversario,
                                  int resultadoDelCombate)
{
    float promedioStats = calcularTotalStats(pokemonAdversario) / 4.0;

    float coeficiente = resultadoDelCombate ? 0.03 : 0.01;

    int recompensa = promedioStats * coeficiente;

    return recompensa? recompensa : 1;
}

int lanzarPokeball(pokemonDeJugador pokeSalvaje)
{
    srand(time(NULL));

    if (pokeSalvaje.estadSalud > 30)
    {
        int rta = rand() % 9 + 1;

        if (rta <= 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }
    else
    {
        int rta = rand() % 9 + 1;

        if (rta <= 6)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void imprimirPokemonSalvaje(pokemonDeJugador aux, int saludBase, int saludActual)
{
    printf("\n----------------\n");
    printf("   %s\n", aux.nombre);
    printf("%s / %s", devolverTipo(aux, 0), devolverTipo(aux, 1));
    printf("\n----------------\n\n");

    float ps = ((float)saludActual * 50) / (float)saludBase;

    for (int i = 0; i < ps; i++)
    {
        color(120);
        printf("_");
        color(15);
    }
    printf("  %d PS", saludActual);
}

float calcularPromedioStats(pokemonDeJugador pokemon)
{
    int totalStats = calcularTotalStats(pokemon);
    float promedio = totalStats / 4.0;

    return promedio;
}

pokemonDeJugador elegirDificultatCapturarPokemon(nodoGeneracion * lista)
{
    float promedioStats = 0;
    int opcion = 0;
    pokemonDeJugador pokemonSalvaje;

    printf("Eliga el nivel de dificultad: \n\n");
    printf("\t1 - Facil\n");
    printf("\t2 - Medio\n");
    printf("\t3 - Dificil\n");
    tomarOpcion(&opcion);

    switch(opcion)
    {
    case 1:
        do
        {
            pokemonSalvaje = crearPokemonDeJugador(lista, pokemonRandom(lista));
            promedioStats = calcularTotalStats(pokemonSalvaje) / 4.0;
        }
        while(promedioStats > 70);
        break;
    case 2:
        do
        {
            pokemonSalvaje = crearPokemonDeJugador(lista, pokemonRandom(lista));
            promedioStats = calcularTotalStats(pokemonSalvaje) / 4.0;
            if( promedioStats < 70 ) {
                sumarExperienciaAPokemon(&pokemonSalvaje, 40);
            }
            promedioStats = calcularTotalStats(pokemonSalvaje) / 4.0;
        }
        while(promedioStats < 70 || promedioStats > 90);
        break;
    case 3:
        do
        {
            pokemonSalvaje = crearPokemonDeJugador(lista, pokemonRandom(lista));
            promedioStats = calcularTotalStats(pokemonSalvaje) / 4.0;
            if( promedioStats < 90 ) {
                sumarExperienciaAPokemon(&pokemonSalvaje, 80);
            }
            promedioStats = calcularTotalStats(pokemonSalvaje) / 4.0;
        }
        while(promedioStats < 90);
        break;
    }

    return pokemonSalvaje;
}
