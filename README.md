# TareaComputacionalDiscretas
Proyecto semestral de la asignatura Matematicas Discretas S1-2023
Descripcion de la tarea:
La tarea consiste en analizar los datos de una red social para entregar un informe a posibles
anunciantes, de modo que estos puedan tomar una buena decision respecto de que usuario de la
red es conveniente auspiciar.
La red social esta compuesta por usuarios, de cada usuario se conoce la siguiente informacion:
- Nombre de usuario. maximo 20 caracteres.
- Pais de residencia. La red esta disponible en un maximo de 20 paises.
- Edad. es un numero entre 0 y 120.
- Creador de contenido. almacenamos un 1 si el usuario es creador de contenido y 0 si es un usuario regular.
- Amigos. es la lista de personas con las que le gustaria contactarse en la red social. La conexion entre ambos se generara solo si el otro es un creador de contenido o solicita la amistad de manera reciproca.
- Intereses del usuario. es la lista de temas en los que el usuario comparte informacion con otros usuarios de la red. Por simplicidad supondremos que no hay mas de 20 intereses disponibles.

Para generar un informe debemos solicitar el publico objetivo a nuestro anunciante. El anunciante
puede filtrar los datos por paıs de residencia, rango de edad e interes del usuario. De este
modo mirando la red que contiene solo este publico objetivo, calcularemos, cuantas comunidades
independientes hay en la red.
Entendemos por comunidad un grupo de usuarios entre los cuales existe una conexion directa o
indirecta a traves de una sucesion de usuarios conectados. Cuando aplicamos los filtros quitaremos
de la red todos los usuarios que no cumplen con los filtros, ya que, aunque pueden ayudar a conectar
mas personas, consideramos que entre ellos no comparten informacion del tema que le interesa a
nuestro anunciante.

El informe debe contener la siguiente informacion para cada comunidad:
- El numero de usuarios de esa comunidad. Diferenciando usuarios regulares y creadores de
contenido.
- La lista de creadores de contenido que podrıa hacer llegar el mensaje mas rapidamente a la
comunidad.
- La lista de usuarios regulares que podrıa lograr lo mismo.
Para lograr esto se pide escribir un programa en C (no C++) que solicite el nombre de un archivo
con la informacion de la red social. El formato de este archivo es: Un numero que da la cantidad
de usuarios de la red, a continuacion por cada usuario, entrega un nombre, un paıs, un numero
entre 0 y 120 que corresponde a la edad, luego un 1 si el usuario es creador de contenido y 0 si no,
a continuacion, la cantidad de usuarios a quienes les solicita la conexion y la lista de los nombres
de estos usuarios, luego la cantidad de intereses que tiene y la lista de estos.
