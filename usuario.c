#include "usuario.h"

void pause()
{
    printf("\n\nPresione una tecla para continuar!\n\n");
    getchar();
    system("cls");
}

void menuPrincipal()
{
    int opcion;

    Usuario nuevo;

    printf("\n\t1 - Iniciar sesion\n");
    printf("\t2 - Crear cuenta\n");
    printf("\n\t3 - Iniciar sesion como admin\n");
    printf("\t0 - Salir\n");

    scanf("%d", &opcion);

    system("cls");

    switch(opcion)
    {
    case 1:

        inicSesionUsuario();
        break;

    case 2:

        nuevo = crearCuenta();
        pause();
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

void menuUsuario(Usuario jugador)
{
    int opcion;

    printf("\n\t1 - Capturar pokemon\n");
    printf("\t2 - Combate vs entrenador\n");
    printf("\t3 - Combate vs lider de GYM\n");
    printf("\t4 - Perfil de entrenador\n");
    printf("\t0 - Salir\n");

    scanf("%d",&opcion);

    switch(opcion)
    {
    case 1:

        break;

    case 2:

        break;

    case 3:

        break;

    case 4:

        break;

    default:

        break;

    }
}

Usuario cargarNuevoUsuario()
{
    Usuario aux;

    int control;

    aux.categoria = 1;

    do
    {
        printf("\nIngrese su Nick:\n\n\t>");
        fflush(stdin);
        gets(&aux.nick);

        control = controlarNick(aux.nick);

        if(control == 1)
        {
            system("cls");
            printf("\nNick en uso actualmente, intente con otro!\n");
        }

    }while(control == 1);

    printf("\nIngrese la contrasenia\n\n\t>");
    fflush(stdin);
    gets(&aux.contrasenia);

    return aux;
}

int controlarNick(char nick[])
{
    int rta = -1, flag = 0;

    FILE * archi = fopen(ARCHIVO_USUARIO, "rb");

    if(archi != NULL)
    {
        Usuario aux;

        while(!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if(strcmpi(aux.nick, nick) == 0)
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

    FILE * archi = fopen(ARCHIVO_USUARIO, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo, sizeof(Usuario), 1, archi);

        printf("\nBienvenido %s a Pokemon Battle Phase!!", nuevo.nick);

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

        if(rta != 1 && rta != 2)
        {
            system("cls");
            printf("\nIngreso una opcion no valida!!\n\n");
        }

    }while(rta != 1 && rta != 2);

    return rta;
}

Usuario buscarUsuario(char aBuscar[])
{
    Usuario aux;

    int flag = 0;

    FILE * archi = fopen(ARCHIVO_USUARIO, "rb");

    if(archi != NULL)
    {
        while(!flag && fread(&aux, sizeof(Usuario), 1, archi) > 0)
        {
            if(strcmpi(aux.nick, aBuscar) == 0)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }

    return aux;
}

void inicSesionUsuario()
{
    Usuario login, aux;

    int control = 0;

    printf("\nIngrese su Nick:\n\n\t>");
    fflush(stdin);
    gets(&login.nick);

    printf("\nIngrese la contrasenia\n\n\t>");
    fflush(stdin);
    gets(&login.contrasenia);

    aux = buscarUsuario(login.nick);

    system("cls");

    if(strcmpi(aux.contrasenia, login.contrasenia) == 0)
    {
        menuUsuario(aux);
    }else
    {
        system("cls");
        printf("\nEse usuario no existe, desea crear una cuenta?\n\n");

        control = siOno();
        system("cls");

        switch(control)
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

    int control = 0;

    printf("\nIngrese su Nick:\n\n\t>");
    fflush(stdin);
    gets(&login.nick);

    printf("\nIngrese la contrasenia\n\n\t>");
    fflush(stdin);
    gets(&login.contrasenia);

    aux = buscarUsuario(login.nick);

    system("cls");

    if(strcmpi(aux.contrasenia, login.contrasenia) == 0)
    {
        if(aux.categoria == 2)
        {
            menuAdmin(aux);
        }else
        {
            printf("\nLa cuenta ingresada no es de categoria 'admin'.\n\n");
        }

    }else
    {
        printf("\nContrasenia incorrecta!\n\n");
    }
}

Usuario cargarNuevoAdmin()
{
   Usuario aux;

    int control;

    aux.categoria = 2;

    do
    {
        printf("\nIngrese su Nick:\n\n\t>");
        fflush(stdin);
        gets(&aux.nick);

        control = controlarNick(aux.nick);

        if(control == 1)
        {
            system("cls");
            printf("\nNick en uso actualmente, intente con otro!\n");
        }

    }while(control == 1);

    printf("\nIngrese la contrasenia\n\n\t>");
    fflush(stdin);
    gets(&aux.contrasenia);

    return aux;
}

void crearNuevaCuentaAdmin()
{
    Usuario nuevo = cargarNuevoAdmin();

    FILE * archi = fopen(ARCHIVO_USUARIO, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo, sizeof(Usuario), 1, archi);

        printf("\nAdmin cargado correctamente!!");

        fclose(archi);
    }

    return nuevo;
}

void menuAdmin()
{
    int opcion;

    printf("\n\t1 - Modificaciones\n");
    printf("\t2 - Ingresar nuevo admin\n");
    printf("\t0 - Salir\n");

    scanf("%d", &opcion);

    system("cls");

    switch(opcion)
    {
    case 1:

        modificaciones();
        break;

    case 2:

        crearNuevaCuentaAdmin();
        break;

    default:

        break;
    }
}

void modificaciones()
{
    int opcion;

    printf("\n\t1 - Agregar nueva generacion\n");
    printf("\t2 - Agregar nuevo pokemon\n");
    printf("\t3 - Modificar pokemon\n");
    printf("\t0 - Salir\n");

    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:

        break;

    case 2:

        break;

    case 3:

        break;

    default:

        break;
    }
}
