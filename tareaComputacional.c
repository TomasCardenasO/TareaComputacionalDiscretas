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
	
	//Creamos la matriz de conexiones entre usuarios (aristas del grafo).
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
	//Inicializamos la matriz con ceros.
	for(int i = 0; i < red.numUsuarios; i++) {
		for(int j = 0; j < red.numUsuarios; j++) {
			red.conexion[i][j] = 0;
		}
	}
	
	//Rellenamos la matriz con las conexiones respectivas.
	for(int i = 0; i < red.numUsuarios; i++) { 			//Para cada usuario "i" de la red has lo siguiente:
		for(int g = 0; g < red.usuario[i].gradoMax; g++) { 	//por cada solicitud de amistad que envio,
			for(int j = 0; j < red.numUsuarios; j++) { 	//busca a ese usuario "j" en la lista.
				if(strcmp(red.usuario[j].nombre, red.usuario[i].amigos[g]) == 0) {
					if(red.usuario[j].esCreador == 1) { 	//Si "j" es creador,
						red.conexion[i][j] = 1; 	//agrega la conexion "(i,j)" inmediatamente.
					} else { 				//Si no es creador,
						for(int m = 0; m < red.usuario[j].gradoMax; m++) { 	//busca a "i" en su lista de solicitudes.
							if(strcmp(red.usuario[j].amigos[m], red.usuario[i].nombre) == 0) {
								red.conexion[i][j] = 1; 		//si aparece entoces se agregaron mutuamente por lo que agregamos la conexion "(i,j)".
							}
						}
					}
				}
			}
		}
	}
	
	//Entramos en el bucle de consultas del anunciante.
	char siono;
	char* pais;
	int eminima, emaxima;
	char* interes;
	int c;
	int flag1;
	do {
		//Pedimos al anunciante los filtros de busqueda.
		while((c = getchar()) != '\n') {} //Limpiamos el buffer antes de leer.
		printf("Ingrese los criterios de busqueda\n");
		printf("Ingrese el pais, (si no es importante ingrese -1): ");
		pais = (char*)malloc(sizeof(char) * 21);
		scanf("%s", pais);
		flag1 = 0;
		do {
			if(flag1 == 1) {
				printf("Error: La edad minima tiene que ser menor o igual a la edad maxima.\n");
			}
			printf("Ingrese la edad minima (si no es importante ingrese 0): ");
			scanf("%d", &eminima);
			printf("Ingrese la edad maxima (si no es importante ingrese 120): ");
			scanf("%d", &emaxima);
			flag1 = 1;
		} while(eminima > emaxima);
		while((c = getchar()) != '\n') {} //Limpiamos el buffer antes de leer.
		printf("Ingrese el interes, (si no es importante ingrese -1): ");
		interes = (char*)malloc(sizeof(char) * 21);
		scanf("%s", interes);
		printf("\nLos parametros son: %s, %d, %d, %s.\n", pais, eminima, emaxima, interes);
		//Generamos el un subgrafo de la red segun los intereses del anunciante.
		
		
		//Operamos sobre el subgrafo para encontrar, por cada componente conexa, el numero de usuarios (total, generales y creadores), y los usuarios con menor excentricidad.
		
		
		//Liberamos la memoria dinamica de la consulta.
		free(pais);
		free(interes);
		
		while((c = getchar()) != '\n') {} //Limpiamos el buffer antes de leer.
		printf("Desea hacer otra consulta? (S/N): ");
		scanf("%c", &siono);
	} while(siono == 's' || siono == 'S');
	
	//Liberamos la memoria dinamica de la red.
	free(red.usuario);
	for(int i = 0; i < red.numUsuarios; i++) {
		free(red.conexion[i]);
	}
	free(red.conexion);
	return 0;
}
