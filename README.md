# Pokemón Battle Phase
Juego de Pokemón programado en C. Intenta atraparlos a todos !!



## Descripción de Proyecto

​	Este es un proyecto realizado por un equipo de compañeros de clase, organizado bajo el nombre de "**char mander**", para la materia de *Laboratorio de Computación II* de la Tecnicatura Universitaria de Programación en la Universidad Tecnológica Nacional.



## Manual de Usuario

### Instalación

1. Descargar la última versión del juego en la sección de *Release*.
2. Descomprimir el archivo en la carpeta que desee tenerlo instalado.
3. *Opcional:* Borrar el archivo comprimido, ya no es necesario.
4. Abrir la carpeta nueva y ubicar el ejecutable *pokemonBP.exe* .
5. Dar doble clic en el ejecutable.
6. <u>Importante:</u>  **JUGAR Y DIVERTIRSE.**



### Juego	

#### Pantalla de Inicio

​	Además de un atractivo diseño de título y un Charmander muy tierno, hay una serie de opciones para elegir:

- <u>Iniciar sesión:</u> Se te pedirán las credenciales de un usuario que ya hayas creado anteriormente. Si se comprueban, avanzaras a la pantalla principal.
- <u>Crear cuenta:</u> Elegirás las credenciales para una nueva cuenta (que después podrás abrir en el menú explicado anteriormente). Una vez creada, elegirás tu primer pokemón entre los iniciales de Kanto. Elegir bien, este va a ser tu compañero durante un largo tiempo de aventura.
- <u>Iniciar sesión como admin:</u> Lo mismo que en el menú de *Iniciar sesión* pero para una cuenta de administrador (con opciones para modificar el juego).



#### Pantalla Principal

​	Acá empieza lo bueno:

- <u>Buscar pokemón en la Hierba:</u> En esta modalidad te enfrentarás a un pokemón aleatorio, ajustado a la dificultad que elijas. Durante este combate, tendrás la posibilidad de atacar con uno de los movimientos de tu pokemón, intentar capturar lanzando una pokeball y huir del combate. El combate termina cuando huyes, capturas exitosamente al pokemón salvaje o cuando un pokemón, sea el tuyo o el otro, es debilitado.
- <u>Combate vs entrenador:</u> Este modo de juego te enfrenta a un entrenador en un combate de equipos, donde vence el que debilite a todo el equipo rival.
- <u>Combate vs líder de GYM:</u> (*ALPHA: Implementacion Inestable*) Este es el modo que te pone a prueba. El sueño de todo entrenador es convertirse en un maestro pokemón. Para esto, se busca vencer a los lideres de gimnasio y reunir todas las medallas que estos otorgan como recompensa.
- <u>Perfil de entrenador:</u> En esta opción podrás ver a tu equipo en detalle, con sus estadísticas, liberar a uno de tus pokemones para conseguir mas espacio en el equipo (aunque a él/ella posiblemente no le agrade) y ver las medallas conseguidas al momento.



##### Después del Combate

​	Una vez terminado un combate, el pokemón de tu equipo que haya combatido se habrá fortalecido. Esto aumentara su **experiencia** y, junto a ello, uno de sus atributos, por lo que se hará mas fuerte.

​	Además, puede ser que el pokemón **evolucione**; pero, para conseguirlo, será necesario *combatir* y, principalmente, darle *mucho* *cariño*.



#### Menú Administrador

​	Este apartado es accesible unicamente para quienes tengan credenciales de administrador (solicitar a los desarrolladores).

- <u>Modificaciones pokemón:</u> Opciones para modificar los pokemones cargados en la base de datos o agregar nuevos a la misma.
- <u>Ingresar nuevo admin:</u> Con esto se ingresarán las credenciales correspondientes a un nuevo administrador.
- <u>Generaciones:</u> Se podrán cargar nuevas generaciones de pokemones, mostrar la información de las existentes y mostrar todos los pokemones cargados
- <u>Movimientos:</u> Menú para mostrar los movimientos cargados, agregar nuevos y borrar alguno (por si lo cargaste erróneamente o lo hiciste muy fuerte).
- <u>Lideres:</u> Aqui se ingresan lideres, con su nombre, id de pokedex de su equipo, nombre de gimnasio y nombre de medalla que otorga.
