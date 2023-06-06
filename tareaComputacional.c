#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Usuario {
	int id; //Identificador del usuario, sirve para hacer mas facil las operaciones. (0,1,...,n)
	char nombre[21];
	char pais[21];
	int edad;
	int esCreador; //1 si el usuario es creador de contenido, 0 si no.
	int gradoMax; //Numero de personas a las que se les envio solicitud, en nuestro modelo este es el posible grado del nodo.
	char amigos[100][21]; //Las filas son todas las personas a las que se envio una solicitud (maximo 100).
	int numIntereses;
	char intereses[20][21]; //Las filas son los intereses del usuario (maximo 20), pueden tener 20 caracteres.
};

struct Grafo {
	int numUsuarios; //El orden del grafo.
	struct Usuario* usuario; //Vector con que contiene a los usuarios (conjunto de los vertices del grafo).
	int** conexion; //Matriz que contiene la informacion sobre las conexiones (aristas del grafo).
};

void imprimeUsuario(struct Usuario usuario) {
	printf("Nombre: %s\n", usuario.nombre);
	printf("Pais: %s\n", usuario.pais);
	printf("Edad: %d\n", usuario.edad);
	if(usuario.esCreador == 1) {
		printf("Es creador de contenido\n");
	} else {
		printf("No es creador de contenido\n");
	}
	printf("Solicitudes enviadas: ");
	for(int i = 0; i < usuario.gradoMax; i++) {
		printf("%s ", usuario.amigos[i]);
	}
	printf("\n");
	printf("Intereses: ");
	for(int i = 0; i < usuario.numIntereses; i++) {
		printf("%s ", usuario.intereses[i]);
	}
	printf("\n");
}

int main() {
	//Primero abrimos el archivo de entrada.
	char nombreArchivo[30];
	printf("Ingrese el nombre del archivo que desea leer: ");
	scanf("%s", nombreArchivo);
	FILE* archivo;
	archivo = fopen(nombreArchivo, "r"); //Abre el archivo en modo lectura "r" (read).
	if(archivo == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	//Leemos el contenido del archivo y lo guardamos en la red.
	struct Grafo red; //El grafo de la red social.
	fscanf(archivo, "%d", &red.numUsuarios);
	red.usuario = (struct Usuario*)malloc(red.numUsuarios * sizeof(struct Usuario));
	if(red.usuario == NULL) {
		printf("Error al asignar memoria dinamica.\n");
		return 1;
	}
	//Leemos los datos de cada usuario.
	for(int i = 0; i < red.numUsuarios; i++) {
		red.usuario[i].id = i;
		fscanf(archivo, "%s", red.usuario[i].nombre);
		fscanf(archivo, "%s", red.usuario[i].pais);
		fscanf(archivo, "%d", &red.usuario[i].edad);
		fscanf(archivo, "%d", &red.usuario[i].esCreador);
		fscanf(archivo, "%d", &red.usuario[i].gradoMax);
		for(int j = 0; j < red.usuario[i].gradoMax; j++) {
			fscanf(archivo, "%s", red.usuario[i].amigos[j]);
		}
		fscanf(archivo, "%d", &red.usuario[i].numIntereses);
		for(int j = 0; j < red.usuario[i].numIntereses; j++) {
			fscanf(archivo, "%s", red.usuario[i].intereses[j]);
		}
	}
	//Cerramos el archivo.
	fclose(archivo);
	
	//Creamos la matriz con las conexiones entre usuarios (aristas del grafo).
	red.conexion = (int**)malloc(red.numUsuarios * sizeof(int*));
	if(red.conexion == NULL) {
		printf("Error al asignar memoria dinamica.\n");
		return 1;
	}
	for(int i = 0; i < red.numUsuarios; i++) {
		red.conexion[i] = (int*)malloc(red.numUsuarios * sizeof(int));
		if(red.conexion[i] == NULL) {
			printf("Error al asignar memoria dinamica.\n");
			return 1;
		}
	}
	//Rellenamos la matriz con las conexiones respectivas.
	
	
	//Entramos en el bucle de consultas del anunciante.
	//Pedimos al anunciante los filtros de busqueda.
	//Generamos el un subgrafo de la red segun los intereses del anunciante.
	//Operamos sobre el subgrafo para encontrar, por cada componente conexa, el numero de usuarios (total, generales y creadores), y los usuarios con menor excentricidad.
	
	
	
	//Liberamos la memoria dinamica de la red.
	free(red.usuario);
	for(int i = 0; i < red.numUsuarios; i++) {
		free(red.conexion[i]);
	}
	free(red.conexion);
	return 0;
}
