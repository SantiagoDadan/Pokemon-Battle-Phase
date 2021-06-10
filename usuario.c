#include "usuario.h"

void inicio()
{

    printf("\n\n       ppppp.   oooooo   kk  kk    eeeeeee  mmmm    mmmm   oooooo   .nn.    nn              _.--\"\"`-..\n");
    printf("       pp  'p  ooo  ooo  kk  kk    eee      mm m    m mm  ooo  ooo  nnnn    nn            ,'          `.\n");
    printf("       pp  .p  oo    oo  kk  kk    ee       mm  mmmm  mm  oo    oo  nn nn   nn          ,'          __  `.\n");
    printf("       ppppp'  oo    oo  kk kk     eeeee    mm   mm   mm  oo    oo  nn  nn  nn         /|          \" __   \\\n");
    printf("       pp      oo    oo  kkkk      eeeee    mm        mm  oo    oo  nn   nn nn        , |           / |.   .\n");
    printf("       pp      oo    oo  kk  kk    ee       mm        mm  oo    oo  nn    nnnn        |,'          !_.'|   |\n");
    printf("       pp      ooo  ooo  kk   kk   eee      mm        mm  ooo  ooo  nn     nnn      ,'             '   |   |\n");
    printf("       pp       oooooo   kk    kk  eeeeeee  mm        mm   oooooo   nn      n.     /              |`--'|   |\n");
    printf("                                                                                  |                `---'   |\n");
    printf("                                                                                   .   ,                   |      \n");
    printf("                                                                                    ._     '           _'  |       \n");
    printf("                                 BATTLE PHASE                                    `.. `.`-...___,...---\"\"    |       __,\n");
    printf("                                                                                |, `- .`._        _,-,.'   .  __.-'-. / \n");
    printf("                                                                              -:..     `. `-..--_.,.<       `\"      / \n");
    printf("                                                                                `,         \"\"\"\"'     `.            \n");
    printf("                                                                                  `.      '            '            /  \n");
    printf("                                                                                    `.   |              \\       _,-'\n");
    printf("                                                                                      `._'               \\   '\"\\  \n");
}

void menuPrincipal()
{
    int opcion;

    Usuario nuevo;

    do
    {
        inicio();

        printf("\n\t1 - Iniciar sesion\n");
        printf("\t2 - Crear cuenta\n");
        printf("\n\t3 - Iniciar sesion como admin\n");
        printf("\t0 - Salir\n");

        printf("\n> ");

        scanf("%d", &opcion);
        limpiarBuffer();

        limpiarPantalla();

        switch (opcion)
        {
        case 0:
            break;

        case 1:
            inicSesionUsuario();
            break;

        case 2:
            nuevo = crearCuenta();
            pausa();
            limpiarPantalla();
            menuUsuario(nuevo);
            break;

        case 3:
            inicSesionAdmin();
            break;

        default:
            printf("\nIngreso una opcion no valida!");
            break;
        }
    }
    while(opcion != 0);

}

void menuUsuario(Usuario jugador)
{
    tipoNodo *listaDeTipos = cargarTiposDesdeArchivo(ARCHIVO_TIPOS);
    movimientoNodo *arbolDeMovimientos = cargarMovimientosDesdeArchivo(ARCHIVO_MOVIMIENTOS);

    nodoGeneracion *listaGeneracion = inicListaGeneracion();
    nodoRegistroPokemon *arbolPokemones = NULL;

    listaGeneracion = cargarGeneracionDesdeArchivo(listaGeneracion);
    cargarPokemonArbolDesdeArchivo(listaGeneracion);

    int rta;

    if (jugador.equipo[0].idPokedex == -1)
    {
        jugador = asignarStarter(jugador, listaGeneracion);
        pausa();
        limpiarPantalla();
    }

    int opcion;

    do
    {
        limpiarPantalla();

        printf("\n\t1 - Buscar pokemon en la Hierba\n");
        printf("\t2 - Combate vs entrenador\n");
        printf("\t3 - Perfil de entrenador\n");
        printf("\t0 - Volver al inicio\n\n>");

        scanf("%d", &opcion);

        switch (opcion)
        {

        case 0:
            guardarUsuario(jugador);
            break;

        case 1:
            rta = equipoLleno(jugador);
            if (rta == 1)
            {
                limpiarPantalla();
                jugador = entrarEnLaHierba(jugador, listaGeneracion, listaDeTipos,arbolDeMovimientos);
            }
            else
            {
                printf("\nEquipo lleno!! Libera un pokemon antes de seguir "
                       "capturando\n\n");
                limpiarBuffer();
                pausa();
            }

            break;

        case 2:

                limpiarPantalla();
                jugador = pelarVsEntrenador(jugador, listaGeneracion, listaDeTipos,arbolDeMovimientos);


            break;

        case 3:

            jugador = perfilEntrenador(jugador);
            limpiarBuffer();
            pausa();
            break;

        default:

            break;
        }

    }
    while (opcion != 0);
}

Usuario cargarNuevoUsuario()
{
    Usuario aux;

    int control, i;

    aux.categoria = 1;

    do
    {
        printf("\nIngrese su Nick:\n\n\t> ");
        scanf("%[^\n]s", aux.nick);
        limpiarBuffer();

        control = controlarNick(aux.nick);

        if (control == 1)
        {
            limpiarPantalla();
            printf("\nNick en uso actualmente, intente con otro!\n");
        }

    }
    while (control == 1);

    printf("\nIngrese la contrasenia\n\n\t> ");
    scanf("%[^\n]s", aux.contrasenia);
    limpiarBuffer();

    for (i = 0; i < MAX_EQUIPO; i++)
    {
        aux.equipo[i].idPokedex = -1;
    }

    return aux;
}

int controlarNick(char nick[])
{
    int rta = -1, flag = 0;

    FILE *archi = fopen(ARCHIVO_USUARIO, "rb");

    if (archi != NULL)
    {
        Usuario aux;

        while (!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmp(aux.nick, nick) == 0)
            {
                rta = 1;
                flag = 1;
            }
        }

        fclose(archi);
    }

    return rta;
}

Usuario crearCuenta()
{
    Usuario nuevo = cargarNuevoUsuario();

    FILE *archi = fopen(ARCHIVO_USUARIO, "ab");

    if (archi == NULL)
    {
        system("mkdir usr");
        archi = fopen(ARCHIVO_USUARIO, "ab");
    }

    if (archi != NULL)
    {
        fwrite(&nuevo, sizeof(Usuario), 1, archi);

        fclose(archi);
    }

    return nuevo;
}

int siOno()
{
    int rta;

    do
    {
        printf("\t1 - Si\n");
        printf("\t2 - No\n");
        scanf("%d", &rta);
        limpiarBuffer();

        if (rta != 1 && rta != 2)
        {
            limpiarPantalla();
            printf("\nIngreso una opcion no valida!!\n\n");
        }

    }
    while (rta != 1 && rta != 2);

    return rta;
}

Usuario buscarUsuario(char aBuscar[])
{
    Usuario aux;

    int flag = 0;

    FILE *archi = fopen(ARCHIVO_USUARIO, "rb");

    if (archi == NULL)
    {
        system("mkdir usr");
        archi = fopen(ARCHIVO_USUARIO, "wb");
    }
    else
    {
        while (!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmp(aux.nick, aBuscar) == 0)
            {
                flag = 1;
            }
        }
    }

    fclose(archi);

    return aux;
}

void inicSesionUsuario()
{
    Usuario login, aux;

    int control = 0;

    printf("\nIngrese su Nick:\n\n\t> ");
    scanf("%[^\n]", login.nick);
    limpiarBuffer();

    printf("\nIngrese la contrasenia\n\n\t> ");
    scanf("%[^\n]s", login.contrasenia);
    limpiarBuffer();

    aux = buscarUsuario(login.nick);

    limpiarPantalla();

    if (strcmp(aux.contrasenia, login.contrasenia) == 0)
    {
        menuUsuario(aux);
    }
    else
    {
        limpiarPantalla();
        printf("\nEse usuario no existe, desea crear una cuenta?\n\n");

        control = siOno();
        limpiarPantalla();

        switch (control)
        {
        case 1:
            login = crearCuenta();
            pausa();
            menuUsuario(login);
            break;

        case 2:
            menuPrincipal();
            break;

        default:
            break;
        }
    }
}

void inicSesionAdmin()
{
    Usuario login, aux;

    printf("\nIngrese su Nick:\n\n\t> ");
    scanf("%[^\n]s", login.nick);
    limpiarBuffer();

    printf("\nIngrese la contrasenia\n\n\t> ");
    scanf("%[^\n]s", login.contrasenia);
    limpiarBuffer();

    aux = buscarUsuario(login.nick);

    limpiarPantalla();

    if (strcmp(aux.contrasenia, login.contrasenia) == 0)
    {
        if (aux.categoria == 2)
        {
            menuAdmin(aux);
        }
        else
        {
            printf("\nLa cuenta ingresada no es de categoria 'admin'.\n\n");
        }

    }
    else
    {
        printf("\nContrasenia incorrecta!\n\n");
    }
}

Usuario cargarNuevoAdmin()
{
    Usuario aux;

    int control, i;

    aux.categoria = 2;

    do
    {
        printf("\nIngrese su Nick:\n\n\t> ");
        scanf("%[^\n]s", aux.nick);
        limpiarBuffer();

        control = controlarNick(aux.nick);

        if (control == 1)
        {
            limpiarPantalla();
            printf("\nNick en uso actualmente, intente con otro!\n");
        }

    }
    while (control == 1);

    printf("\nIngrese la contrasenia\n\n\t> ");
    scanf("%[^\n]s", aux.contrasenia);
    limpiarBuffer();

    for (i = 0; i < MAX_EQUIPO; i++)
    {
        (aux.equipo[i]).idPokedex = -1;
    }

    return aux;
}

void crearNuevaCuentaAdmin()
{
    Usuario nuevo = cargarNuevoAdmin();

    FILE *archi = fopen(ARCHIVO_USUARIO, "ab");

    if (archi == NULL)
    {
        system("mkdir usr");
        archi = fopen(ARCHIVO_USUARIO, "ab");
    }

    if (archi != NULL)
    {
        fwrite(&nuevo, sizeof(Usuario), 1, archi);

        printf("\nAdmin cargado correctamente!!");

        fclose(archi);
    }
}

void menuAdmin()
{
    tipoNodo *listaDeTipos = cargarTiposDesdeArchivo(ARCHIVO_TIPOS);
    movimientoNodo *arbolDeMovimientos = cargarMovimientosDesdeArchivo(ARCHIVO_MOVIMIENTOS);

    nodoGeneracion *listaGeneracion = inicListaGeneracion();
    nodoRegistroPokemon *arbolPokemones = NULL;

    listaGeneracion = cargarGeneracionDesdeArchivo(listaGeneracion);
    cargarPokemonArbolDesdeArchivo(listaGeneracion);

    int opcion, control;

    do
    {
        printf("\n\t1 - Modificaciones pokemon\n");
        printf("\t2 - Ingresar nuevo admin\n");
        printf("\t3 - Generaciones\n");
        printf("\t4 - Movimientos\n");
        printf("\t5 - Cargar Lideres\n");
        printf("\t0 - Volver al inicio\n\n>");

        scanf("%d", &opcion);
        limpiarBuffer();

        limpiarPantalla();

        switch (opcion)
        {
        case 1:

            modificaciones();
            break;

        case 2:

            crearNuevaCuentaAdmin();
            break;

        case 3:

            menuGeneraciones();
            break;

        case 4:

            menuMovimientos();
            tomarOpcion(&control);
            limpiarPantalla();

            switch( control ) {
            case 1:
                menuMovimientosPorTipo();
                tomarOpcion(&control);
                limpiarPantalla();

                if( control > 0 && control < 19 )
                {
                    encabezadoDeMostrarMovimientosPorTipo();
                    mostrarMovimientosPorTipo( arbolDeMovimientos, control );
                    pausa();
                }
                else if( control == 19 )
                {
                    encabezadoDeMostrarMovimientos();
                    mostrarMovimientos( arbolDeMovimientos );
                    pausa();
                }
                break;
            case 2:
                do
                {
                    mostrarTipos( listaDeTipos );
                    arbolDeMovimientos = creacionDeNuevoMovimiento( arbolDeMovimientos );
                    printf("\nPresione 0 para terminar la carga ");
                    tomarOpcion( &control );
                }
                while ( control );
                break;

            case 3:
                arbolDeMovimientos = borradoDeMovimiento( arbolDeMovimientos );
                break;
            }
            break;

        //case 5:
           // cargarLideresGimnasio(ARCHIVO_LIDERES);
            //reak;

        default:

            break;

        }
    }while(opcion != 0);

}

void modificaciones()
{
    int opcion;

    do
    {
        printf("\n\t1 - Agregar nuevo pokemon\n");
        printf("\t2 - Modificar pokemon\n");
        printf("\t0 - Salir\n");

        printf("\n> ");

        scanf("%d", &opcion);

        limpiarBuffer();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:

            cargarModeloArchivo();
            break;

        case 2:

            modificacionesPokemon();
            break;

        default:

            break;
        }
    }while(opcion != 0);

}

int equipoLleno(Usuario entrenador)
{
    int rta = 0;

    for (int i = 0; i < MAX_EQUIPO; i++)
    {
        if (entrenador.equipo[i].idPokedex != -1)
        {
            rta++;
        }
    }

    if (rta < 6)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *devolverGenero(pokemonDeJugador aux)
{
    if (aux.genero == 0)
    {
        return "Masculino";
    }
    else
    {
        return "Femenino";
    }
}

Usuario perfilEntrenador(Usuario entrenador)
{
    int opcion, i = 0;

    limpiarPantalla();
    //medallasJugador medallas;

    do
    {
        printf("\nEntrenador: %s\n\n", entrenador.nick);

        printf("\t1 - Ver equipo\n");
        printf("\t2 - Liberar pokemon\n");
        printf("\t3 - Ver medallas obtenidas\n");
        printf("\t0 - Salir\n\n>");

        scanf("%d", &opcion);
        limpiarBuffer();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:

            while (entrenador.equipo[i].idPokedex != -1 && i < MAX_EQUIPO)
            {
                if (entrenador.equipo[i].idPokedex != -1)
                {
                    printf("\n--------------------------\n");
                    printf("      #%d %s\n", entrenador.equipo[i].idPokedex,
                           entrenador.equipo[i].nombre);
                    printf("Tipos: %s / %s\n", devolverTipo(entrenador.equipo[i], 0),
                           devolverTipo(entrenador.equipo[i], 1));
                    printf("Genero: %s\n", devolverGenero(entrenador.equipo[i]));
                    printf("Ataque: %d\n", entrenador.equipo[i].estadAtaque);
                    printf("Defensa: %d\n", entrenador.equipo[i].estadDefensa);
                    printf("Salud: %d\n", entrenador.equipo[i].estadSalud);
                    printf("Velocidad: %d\n", entrenador.equipo[i].estadVelocidad);
                    printf("Naturaleza: %s\n", entrenador.equipo[i].naturaleza);
                    printf("XP: %d", entrenador.equipo[i].experienceObtenida);
                    printf("\n--------------------------\n");

                    pausa();
                    limpiarPantalla();
                }

                limpiarBuffer();
                i++;
            }

            break;

        case 2:

            entrenador = liberarPokemon(entrenador);
            break;

        /*case 3:

            medallas = obtenerMedallasDeJugador(ARCHIVO_MEDALLAS, entrenador.nick);

            if(medallas.cantidadMedallas > 0)
            {
                imprimirMedallas(medallas);
            }else
            {
                printf("\nTodavia no tienes medallas!!\n\n");
            }
            pausa();
            limpiarPantalla();
            break;*/

        case 0:

            break;

        default:

            break;
        }

    }
    while (opcion != 0);

    return entrenador;
}

Usuario liberarPokemon(Usuario entrenador)
{
    int poss, control = 0, flag = 0;

    printf("\nQue pokemon quiere liberar?\n\n");

    for (int i = 0; i < MAX_EQUIPO; i++)
    {
        if (entrenador.equipo[i].idPokedex != -1)
        {
            printf("\t%d - %s\n", i + 1, entrenador.equipo[i].nombre);
        }
    }

    do
    {
        printf(">");
        scanf("%d", &poss);

        poss -= 1;

        if (entrenador.equipo[poss].idPokedex != -1)
        {
            entrenador.equipo[poss].idPokedex = -1;

            while (poss < MAX_EQUIPO)
            {
                if (poss + 1 < MAX_EQUIPO)
                {
                    if (entrenador.equipo[poss + 1].idPokedex != -1)
                    {
                        entrenador.equipo[poss] = entrenador.equipo[poss + 1];
                        entrenador.equipo[poss + 1].idPokedex = -1;
                    }
                }
                poss++;
            }

            control = 1;
        }

    }
    while (control != 1);

    Usuario aux;

    FILE *archi = fopen(ARCHIVO_USUARIO, "r+b");
    if (archi != NULL)
    {
        while (!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmpi(aux.nick, entrenador.nick) == 0)
            {
                fseek(archi, sizeof(Usuario) * -1, SEEK_CUR);
                fwrite(&entrenador, sizeof(Usuario), 1, archi);
                flag = 1;
            }
        }

        fclose(archi);
    }

    printf("\nPokemon liberado!!\n\n");

    return entrenador;
}

void modificacionesPokemon()
{
    int opcion;

    printf("\n\t1 - Modificar nombre\n");
    printf("\t2 - Modificar stats\n");
    printf("\t3 - Modificar tipos\n");
    printf("\t4 - Modificar ataques\n");
    printf("\t0 - Salir\n\n>");

    do
    {
        scanf("%d", &opcion);

        if (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 &&
                opcion != 0)
        {
            printf("\nOpcion invalida, intentelo nuevamente!\n\n");
        }

    }
    while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 &&
            opcion != 0);

    limpiarPantalla();

    switch (opcion)
    {
    case 1:

        modificarNombre();
        break;

    case 2:

        modificarStats();
        break;

    case 3:

        modificarTipos();
        break;

    case 4:

        modificarAtaques();
        break;

    default:

        break;
    }
}

int seleccionarPokemonPelea(Usuario entrenador)
{
    printf("\nPelear con:\n\n");

    int opcion;

    for (int i = 0; i < MAX_EQUIPO; i++)
    {
        if (entrenador.equipo[i].idPokedex != -1)
        {
            printf("\t%d - %s | %d Exp\n", i + 1, entrenador.equipo[i].nombre, entrenador.equipo[i].experienceObtenida);
        }
    }

    scanf("%d", &opcion);

    return opcion - 1;
}

Usuario entrarEnLaHierba(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos)
{
    pokemonDeJugador pokemonSalvaje = elegirDificultatCapturarPokemon(lista);
    int ganador = 0;

    printf("\n\nUn %s salvaje aparecio!!!", pokemonSalvaje.nombre);
    limpiarBuffer();
    pausa();
    limpiarPantalla();

    int pokemonEntrenador = seleccionarPokemonPelea(entrenador);
    pokemonDeJugador pokeElegido = entrenador.equipo[pokemonEntrenador];


    int captura = pelear(pokeElegido, pokemonSalvaje, tipos, movimientos, lista, &ganador);

    int expGanada = calcularExperienciaRecompensa(pokemonSalvaje, ganador);
    sumarExperienciaAPokemon(&pokeElegido, expGanada);
    hayEvolucion(lista, &pokeElegido);

    entrenador.equipo[pokemonEntrenador] = pokeElegido;

    if (captura == 1)
    {
        entrenador = agregarPokeAlEquipo(entrenador, pokemonSalvaje);
    }

    guardarUsuario(entrenador);

    limpiarBuffer();
    pausa();

    return entrenador;
}

int pokeEnEquipo(pokemonDeJugador equipo[], int cantPokes, pokemonDeJugador pokeAgregar)
{
    int rta = 0;

    for (int i = 0; i < cantPokes; i++)
    {
        if(equipo[i].idPokedex == pokeAgregar.idPokedex)
        {
            rta = 1;
        }
    }

    return rta;
}

int cantPokesEnEquipo(Usuario entrenador)
{
    int rta = 0;

    for(int i = 0; i < MAX_EQUIPO; i++)
    {
        if(entrenador.equipo[i].idPokedex != -1)
        {
            rta++;
        }
    }

    return rta;
}

Usuario pelarVsEntrenador(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos)
{
    int contador = 0, cantPokes = 0, ganador = 0;

    do
    {
        printf("\nIngrese la cantidad de pokemon con los que quiere pelear: ");
        tomarOpcion(&cantPokes);

        if(cantPokesEnEquipo(entrenador) < cantPokes)
        {
            printf("\nNo tienes tantos pokemon en el equipo!!\n\n");
        }

    }while(cantPokesEnEquipo(entrenador) < cantPokes);

    int indices[cantPokes];
    int pokemonEntrenador;

    pokemonDeJugador pokesElegidos[cantPokes];

    limpiarPantalla();

    for(int i = 0; i < cantPokes; i++)
    {
        limpiarPantalla();
        printf("\nSelccionando poke numero %d\n", i + 1);
        pokemonEntrenador = seleccionarPokemonPelea(entrenador);

        if(pokeEnEquipo(pokesElegidos, cantPokes, entrenador.equipo[pokemonEntrenador]) == 0)
        {
            pokesElegidos[i] = entrenador.equipo[pokemonEntrenador];
            indices[i] = pokemonEntrenador;
        }else
        {
            printf("\nEse poke ya esta en el equipo");
            i--;
            limpiarBuffer();
            pausa();
        }

    }
    pokemonDeJugador contrincante[cantPokes];

    for(int i = 0; i < cantPokes; i++)
    {
        limpiarPantalla();
        printf("\nPokemon numero %d:\n\n", i+1);
        contrincante[i] = elegirDificultatCapturarPokemon(lista);
    }

    ganador = pelearXvX(pokesElegidos, contrincante, cantPokes, tipos, movimientos, lista, ganador);

    int expGanada = 0;

    for (size_t i = 0; i < cantPokes; i++) {
        expGanada += calcularExperienciaRecompensa(contrincante[i], ganador);
    }

    expGanada = expGanada / cantPokes;

    for (size_t i = 0; i < cantPokes; i++) {
        sumarExperienciaAPokemon(&pokesElegidos[i], expGanada);
        hayEvolucion(lista, &pokesElegidos[i]);
        entrenador.equipo[indices[i]] = pokesElegidos[i];
    }

    guardarUsuario(entrenador);

    limpiarBuffer();
    pausa();

    return entrenador;
}

Usuario asignarStarter(Usuario entrenador, nodoGeneracion *lista)
{
    int opcion, flag = 0;

    Usuario aux;

    printf("\bBienvenido a Pokemon Battle Phase %s!!\n\n", entrenador.nick);
    printf("Este puede ser un mundo un poco salvaje, es mejor ir bien "
           "acompaniado\n\n");
    printf("Escoje a tu nuevo companiero:\n\n");

    do
    {
        printf("\t1 - Bulbasaur (Planta/Veneno)\n");
        printf("\t2 - Charmander (Fuego)\n");
        printf("\t3 - Squirtle (Agua)\n\n>");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:

            entrenador.equipo[0] = crearPokemonDeJugador(lista, 1);
            break;

        case 2:

            entrenador.equipo[0] = crearPokemonDeJugador(lista, 4);
            break;

        case 3:

            entrenador.equipo[0] = crearPokemonDeJugador(lista, 7);
            break;

        default:

            printf("Opcion no valida!!\n\n");
            pausa();
            limpiarPantalla();
            break;
        }

    }
    while (opcion != 1 && opcion != 2 && opcion != 3);

    printf(
        "\nAsique elegiste a %s, muy buena eleccion, suerte en tu aventura!!\n\n",
        entrenador.equipo[0].nombre);

    FILE *archi = fopen(ARCHIVO_USUARIO, "r+b");

    if (archi != NULL)
    {
        while (!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmp(aux.nick, entrenador.nick) == 0)
            {
                fseek(archi, sizeof(Usuario) * -1, SEEK_CUR);
                fwrite(&entrenador, sizeof(Usuario), 1, archi);
                flag = 1;
            }
        }

        fclose(archi);
    }

    return entrenador;
}

Usuario agregarPokeAlEquipo(Usuario entrenador, pokemonDeJugador salvaje)
{
    int i = 0, flag = 0;

    while (i < MAX_EQUIPO && !flag)
    {
        if (entrenador.equipo[i].idPokedex == -1)
        {
            entrenador.equipo[i] = salvaje;
            flag = 1;
        }
        i++;
    }
    if (!flag)
        printf("Equipo completo. Libera un pokemon para atrapar mas\n");

    return entrenador;
}

void guardarUsuario(Usuario entrenador)
{
    int flag = 0;

    Usuario aux;

    FILE *archi = fopen(ARCHIVO_USUARIO, "r+b");

    if (archi != NULL)
    {
        while (!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if (strcmp(aux.nick, entrenador.nick) == 0)
            {
                fseek(archi, sizeof(Usuario) * -1, SEEK_CUR);
                fwrite(&entrenador, sizeof(Usuario), 1, archi);
                flag = 1;
            }
        }

        fclose(archi);
    }
}
void mostrarMenu() {
  printf("1- Tipos Elementales\n");
  printf("2- Movimientos\n");
  printf("3- Generaciones\n");
  printf("\n0- Salir\n");
}


void menuMovimientos() {
  printf("1- Mostrar Movimientos\n");
  printf("2- Agregar Movimiento Nuevo\n");
  printf("3- Borrar Movimiento\n");
  printf("\n0- Salir\n");
}

void menuMovimientosPorTipo() {
  printf("MOSTRAR MOVIMIENTOS POR TIPO\n");
  printf("1- Acero\n");
  printf("2- Agua\n");
  printf("3- Bicho\n");
  printf("4- Dragon\n");
  printf("5- Electrico\n");
  printf("6- Fantasma\n");
  printf("7- Fuego\n");
  printf("8- Hada\n");
  printf("9- Hielo\n");
  printf("10- Lucha\n");
  printf("11- Normal\n");
  printf("12- Planta\n");
  printf("13- Psiquico\n");
  printf("14- Roca\n");
  printf("15- Siniestro\n");
  printf("16- Tierra\n");
  printf("17- Veneno\n");
  printf("18- Volador\n");

  printf("\n19 - Mostrar todos\n");

  printf("\n20 - Volver atras\n");
}


/*Usuario pelearVsLider(Usuario entrenador, nodoGeneracion *lista,tipoNodo *tipos, movimientoNodo *movimientos) {
  int contador = 0, cantPokes = 3, ganador = 0;
  int combatir = 1;
  int indices[cantPokes];
  int pokemonEntrenador;
  liderGimnasio rival;
  pokemonDeJugador pokesElegidos[cantPokes];
  pokemonDeJugador contrincante[cantPokes];
  limpiarPantalla();

  if(cantPokesEnEquipo(entrenador) < cantPokes) {
    printf("\nNo tienes suficientes pokemon en el equipo!!\nNecesitas 3 para este combate.\n");
    combatir = 0;
    pausa();
  }

  if( combatir ) {
    combatir = elegirLiderParaCombatir(ARCHIVO_LIDERES, &rival);
  }

  if( combatir ) {
    for (int i = 0; i < cantPokes; i++) {
      contrincante[i] = crearPokemonDeJugador(lista, rival.equipo[i]);
      if ( contrincante[i].idPokedex == -1 ) {
        contrincante[i] = crearPokemonDeJugador( lista, pokemonRandom(lista) );
      }
      sumarExperienciaAPokemon(&contrincante[i], 80);
    }

    for(int i = 0; i < cantPokes; i++)
    {
      limpiarPantalla();
      printf("\nSelccionando poke numero %d\n", i + 1);
      pokemonEntrenador = seleccionarPokemonPelea(entrenador);

      if(pokeEnEquipo(pokesElegidos, cantPokes, entrenador.equipo[pokemonEntrenador]) == 0) {
        pokesElegidos[i] = entrenador.equipo[pokemonEntrenador];
        indices[i] = pokemonEntrenador;
      }else {
        printf("\nEse poke ya esta en el equipo");
        i--;
        limpiarBuffer();
        pausa();
      }
    }

    ganador = pelearXvX(pokesElegidos, contrincante, cantPokes, tipos, movimientos, lista, ganador);

    int expGanada = 0;

    for (size_t i = 0; i < cantPokes; i++) {
      expGanada += calcularExperienciaRecompensa(contrincante[i], ganador);
    }

    expGanada = expGanada / cantPokes;

    for (size_t i = 0; i < cantPokes; i++) {
      sumarExperienciaAPokemon(&pokesElegidos[i], expGanada);
      hayEvolucion(lista, &pokesElegidos[i]);
      entrenador.equipo[indices[i]] = pokesElegidos[i];
    }

    guardarUsuario(entrenador);

    medallasJugador medallas = obtenerMedallasDeJugador( ARCHIVO_MEDALLAS, entrenador.nick );
    medalla recompensa = entregaMedalla( rival );
    guardarEnMedallero(&medallas, recompensa);
    guardarMedallas(ARCHIVO_MEDALLAS, medallas);

    limpiarBuffer();
  } else {
      printf("\nNo hay lideres cargador. Solicite al administrador que los cargue.");
  }

  pausa();

  return entrenador;
}*/
