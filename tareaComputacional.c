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
	int compExplored; //Indica si la componente conexa (comunidad) fue explorada.
	int visitado; //Indica si este usuario fue visitado dentro del algoritmo BFS.
};

struct Grafo {
	int numUsuarios; //El orden del grafo.
	struct Usuario* usuario; //Vector que contiene a los usuarios (conjunto de los vertices del grafo).
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
		struct Grafo subred;
		subred.numUsuarios = 0;
		subred.usuario = (struct Usuario*)malloc(sizeof(struct Usuario) * red.numUsuarios);
		if(subred.usuario == NULL) {
				printf("Error al asignar memoria dinamica.\n");
				return 1;
		}
		//Añadimos los usuarios que nos interesan al conjunto de usuarios del subgrafo.
		int flag2;
		for(int i = 0; i < red.numUsuarios; i++) {
			flag2 = 0;
			if((strcmp(pais, "-1") == 0 || strcmp(red.usuario[i].pais, pais) == 0) && (eminima <= red.usuario[i].edad && red.usuario[i].edad <= emaxima)) {
				for(int j = 0; j < red.usuario[i].numIntereses; j++) {
					if(strcmp(red.usuario[i].intereses[j], interes) == 0) {
						flag2 = 1;
						break;
					}
				}
				if(strcmp(interes, "-1") == 0 || flag2 == 1) {
					subred.usuario[subred.numUsuarios] = red.usuario[i];
					subred.usuario[subred.numUsuarios].id = subred.numUsuarios;
					subred.usuario[subred.numUsuarios].compExplored = 0;
					subred.numUsuarios += 1;
				}		
			}
		}
		//Si existen usuarios que cumplan con los criterios hacemos lo siguiente.
		if(subred.numUsuarios > 0) {
			//Generamos la matriz con las conexiones entre usuarios.
			subred.conexion = (int**)malloc(subred.numUsuarios * sizeof(int*));
			if(subred.conexion == NULL) {
				printf("Error al asignar memoria dinamica.\n");
				return 1;
			}
			for(int i = 0; i < subred.numUsuarios; i++) {
				subred.conexion[i] = (int*)malloc(subred.numUsuarios * sizeof(int));
				if(subred.conexion[i] == NULL) {
					printf("Error al asignar memoria dinamica.\n");
					return 1;
				}
			}
			//Inicializamos la matriz con ceros.
			for(int i = 0; i < subred.numUsuarios; i++) {
				for(int j = 0; j < subred.numUsuarios; j++) {
					subred.conexion[i][j] = 0;
				}
			}
	
			//Rellenamos la matriz con las conexiones respectivas.
			//Para cada usuario "i" de la red has lo siguiente:
			for(int i = 0; i < subred.numUsuarios; i++) {
				//por cada solicitud de amistad que envio,
				for(int g = 0; g < subred.usuario[i].gradoMax; g++) {
					//busca a ese usuario "j" en la lista.
					for(int j = 0; j < subred.numUsuarios; j++) { 
						if(strcmp(subred.usuario[j].nombre, subred.usuario[i].amigos[g]) == 0) {
							//Si "j" es creador,
							if(subred.usuario[j].esCreador == 1) { 
								//agrega la conexion "(i,j)" inmediatamente.
								subred.conexion[i][j] = 1; 
							//Si no es creador,
							} else { 
								//busca a "i" en su lista de solicitudes.
								for(int m = 0; m < subred.usuario[j].gradoMax; m++) {
									//si aparece entoces se agregaron mutuamente por lo que agregamos la conexion "(i,j)".
									if(strcmp(subred.usuario[j].amigos[m], subred.usuario[i].nombre) == 0) {
										subred.conexion[i][j] = 1;
									}
								}
							}
						}
					}
				}
			}
			
			/*Operamos sobre el subgrafo para encontrar, por cada componente conexa, el numero de
			usuarios (total, general y creadores), y los usuarios con menor excentricidad.*/
		
			/*Algoritmo:
			- Recorre todos los vertices del grafo, por cada vertice {
				- si su componente conexa no fue explorada {
				- recorre la componente contando el numero de creador y usuarios generales
				- guarda cada vertice en un vector y marca su componente conexa como explorada
				- por cada vertice en el vector aplica BFS para saber su excentricidad
				- imprime los datos obtenidos de esta comunidad
			}
			- si su componente conexa fue explorada pasa al siguiente.	
			}
			*/
			int numComunidad = 0;
			int numCreadores;
			int numUsuarios;
			int numTotal;
			struct Usuario** usuariosComunidad;
			struct Usuario** cola;
			int sizeCola;
			struct Usuario* primero;
			for(int i = 0; i < subred.numUsuarios; i++) {
				if(subred.usuario[i].compExplored == 0) {
					numComunidad += 1;
					printf("Comunidad %d \n", numComunidad);
					numCreadores = 0;
					numUsuarios = 0;
					numTotal = 0;
					usuariosComunidad = (struct Usuario**)malloc(sizeof(struct Usuario*) * subred.numUsuarios);
					//BFS.
					for(int j = 0; j < subred.numUsuarios; j++) {
						subred.usuario[j].visitado = 0;
					}
					cola = (struct Usuario**)malloc(sizeof(struct Usuario*) * subred.numUsuarios);
					sizeCola = 0;
					subred.usuario[i].visitado = 1;
					cola[sizeCola] = &subred.usuario[i];
					sizeCola += 1;
					while(sizeCola != 0) {
						//Extraemos el primer elemento de la cola.
						primero = cola[0];
						for(int j = 0; j < sizeCola - 1; j++) {
							cola[j] = cola[j + 1];
						}
						sizeCola -= 1;
						//Lo contamos como usuario de la comunidad y lo agregamos al vector.
						(*primero).compExplored = 1;
						usuariosComunidad[numTotal] = primero;
						numTotal += 1;
						if((*primero).esCreador == 1) {
							numCreadores += 1;
						} else {
							numUsuarios += 1;
						}
						//Recorremos sus vecinos.
						for(int j = 0; j < subred.numUsuarios; j++) {
							if(subred.conexion[(*primero).id][j] == 1) {
								if(subred.usuario[j].visitado == 0) {
									subred.usuario[j].visitado = 1;
									cola[sizeCola] = &subred.usuario[j];
									sizeCola += 1;
								}
							}
						}
					}
					printf("La comunidad %d tiene %d cuentas de usuarios.\n", numComunidad, numTotal);
					printf("Esta comunidad tiene %d creadores de contenido y tiene %d usuarios regulares.\n", numCreadores, numUsuarios);
					for(int j = 0; j < numTotal; j++) {
						printf("%s\n", (*usuariosComunidad[j]).nombre);
					}
									
					free(usuariosComunidad);
					free(cola);		
				}
			}
			
			
			//Liberamos la memoria dinamica de la matriz de aristas.
			for(int i = 0; i < subred.numUsuarios; i++) {
				free(subred.conexion[i]);
			}
			free(subred.conexion);
		} else {
			printf("No hay usuarios que cumplan con los criterios de busqueda.\n");
		}
		
		//Liberamos la memoria dinamica de la consulta.
		free(pais);
		free(interes);
		free(subred.usuario);
		
		while((c = getchar()) != '\n') {} //Limpiamos el buffer antes de leer.
		printf("Desea hacer otra consulta? (S/N): ");
		scanf("%c", &siono);
	} while(siono == 's' || siono == 'S');
	
	//Liberamos la memoria dinamica de la red.
	free(red.usuario);
	return 0;
}
