//Marcelo Fern�ndez Solano 2019347928
//Steven Vega Zu�iga
//NaviTEC
/* Descripci�n: NaviTEC es un sistema el cual puede ser utilizado para que los ni�os registren sus cartas 
				navide�as y ademas Santa y sus ayudantes puedan consultar estas cartas para procesarlas.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct ninho{ //Nodo con caracteristicas de un ni�o
    int corre;
    char cedula[10];
    char nombre[50];
    char apellido[50];
    char nombreUsuario[30];
    char residencia[50];
    char correo[50];
    char fechaNacimiento[15];
    char edad[6];
    char necesidadesEspeciales[50];
    char comportamientoNinho[20];
    struct nodo *sig;
};

typedef struct ninho *ListaNinho;
ListaNinho p, cabeza;
ListaNinho getnodo();

int buscarCedula(char cedula[10]);
void registrarNinho(ListaNinho p, char cedula[10], char nombre[50], char apellido[50], char nombreUsuario[30], char residencia[50], char correo[50], char fechaNacimiento [15], char edad[6], char necesidadesEspeciales[50], char comportamietoNinho[20], int i);
//void consultarMiembro(char cedulaConsulta[8]);

ListaNinho getnodo(){
    ListaNinho p;
    p = (ListaNinho)malloc(sizeof(struct ninho));
    if(p == NULL){
		printf("Memoria Insuficiente\a\n");
 	}
    return p;
}

//Funcion para buscar si cedula ha sido registrada anteriormente
int buscarCedula(char cedula[10]){
	
	int resultado = 0;
	
	FILE *fp;
	fp = fopen("listaNinhos.csv", "r");
	
	if(fp == NULL){
		printf("Error al cargar el archivo, intente verificar si el archivo existe o permanece abierto\n");
	}
	
	char line[998];
	
	while(fgets(line, sizeof(line), fp)){ // Realiza una tokenizacion linea por linea
		
		char *token;
		
		token = strtok(line, ","); // Tokeniza la linea a partir de ","
		
		if(strcmp(token, cedula) == 0){ // Compara la cedula con el token
			resultado++;
		}
	}
	return resultado;
}

//Funcion para registrar un ni�o nuevo
void registrarNinho(ListaNinho p, char cedula[10], char nombre[50], char apellido[50], char nombreUsuario[30], char residencia[50], char correo[50], char fechaNacimiento [15], char edad[6], char necesidadesEspeciales[50], char comportamientoNinho[20], int i){
	ListaNinho q;

	if(p == NULL) //En caso de p vacia
    	printf("ERROR, lista vacia\n\a");
	else{
		q = getnodo();
		strcpy(q->cedula, cedula);
		strcpy(q->nombre, nombre);
		strcpy(q->apellido, apellido);
		strcpy(q->nombreUsuario, nombreUsuario);
		strcpy(q->residencia, residencia);
		strcpy(q->correo, correo);
		strcpy(q->fechaNacimiento, fechaNacimiento);
		strcpy(q->edad, edad);
		strcpy(q->necesidadesEspeciales, necesidadesEspeciales);
		strcpy(q->comportamientoNinho, comportamientoNinho);
		
		// Persistencia de datos de nuevo miembro en listaMiembros.csv
		FILE *fp;
		fp = fopen("listaNinhos.csv", "a");
		
		if(fp == NULL){ //En caso de no exixtir el archivo listaMiembros.csv
			printf("Error al cargar el archivo, intente verificar si el archivo existe o permanece abierto\n");
		}
		
		else{
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", q->cedula, q->nombre, q->apellido, q->nombreUsuario, q->residencia, q->correo, q->fechaNacimiento, q->edad, q->necesidadesEspeciales, q->comportamientoNinho);
		
			fclose(fp); //cierra el archivo y finaliza el guardado en memoria
			fp = 0;
			
			printf("\nMiembro ingresado exitosamente\n");
		}
		
		/*q->corre = i;
		q->sig = p->sig;
		p->sig = q;
		p = p->sig;*/
	}
}

//Funcion para consultar ni�o 
char cedulaConsulta[10];

void consultarNinho(char cedulaConsulta[10]){
	
	int miembrosEncontrados = 0;
	
	FILE *fp;
	fp = fopen("listaNinhos.csv", "r");
	
	if(fp == NULL){
		printf("Error al cargar el archivo, intente verificar si el archivo existe o permanece abierto\n");
	}
	
	char line[998];
	
	while(fgets(line, sizeof(line), fp)){
		
		char *token;
		
		token = strtok(line, ",");
		
		if(strcmp(token,cedulaConsulta) == 0){
		
			while(token != NULL){
				printf("%12s", token);
				token = strtok(NULL, ",");
			}
			miembrosEncontrados++;
			printf("\n");
		}
	}
	
	if(miembrosEncontrados == 0){
		printf("Lo sentimos, la cedula que ingreso no se encuentra registrada\n\n");
	}
}

