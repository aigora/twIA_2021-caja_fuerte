/*#define MAX_BUFFER 200
#define MAX_INTENTOS_READ 4
#define MS_ENTRE_INTENTOS 250
#define SI 1
#define NO 0*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
//#include "SerialClass/SerialClass.h"
#define N 50
typedef struct {
	char codigo[N], calle[N], localidad[N];
	int num, postal, GPS[3];
}PAP;
void inicializar(PAP*, int);
void alta(PAP*);
void modificar(PAP*, int, char*);
void baja(PAP*, PAP*, int, char*);
void datos(PAP*, int, char*);
void lista(PAP*, int);
/*void configura(void);
void arduino(void);
void Talk_with_Arduino(Serial* Arduino);
void Send_to_hw(Serial*, char*);
int Receive_from_hw(Serial* Arduino, char* BufferEntrada);
int Send_and_Receive(Serial* Arduino, const char* msg_out, int valor_out, char* msg_in, int* valor_in);*/
int main() {
	int op, cant, i, j = 0;
	char nom[N]; 
	PAP* pa, * paux;
	printf("¿Cuantos contenedores posee su sistema?\n");
	scanf_s("%d", &cant);
	pa = (PAP*)malloc(cant * sizeof(PAP));
	inicializar(pa, cant);
	system("pause");
	system("cls");
	do {
		j = 0;
		printf("\t\t\tBIENVENIDO\n");
		printf("\t\t\t¿Que desea hacer?\n\t\t\t\t1. Dar de alta un nuevo contenedor\n\t\t\t\t2. Dar de baja un contenedor\n\t\t\t\t3. Modificar\n\t\t\t\t4. Consultar datos de un contenedor\n\t\t\t\t5. Consultar estado de un contenedor\n\t\t\t\t6. Salir\n");
		scanf_s("%d", &op);
		if (op > 6 || op <= 0) {
			printf("Operacion inexistente.\n");
			system("pause");
		}
		else {
			switch (op) {
			case 1:
				cant += 1;
				pa = (PAP*)realloc(pa, cant * sizeof(PAP));
				alta((pa + (cant - 1)));
				printf("Dada de alta realizada\n");
				system("pause");
				break;
			case 2:
				if (cant == 0) {
					printf("No hay contenedores disponbles.\n");
				}
				else {
					printf("ELIMINAR CONTENEDOR\n");
					printf("¿Cual es el codigo de el que desea dar de baja:\n");
					getchar();
					gets_s(nom);
					for (i = 0; i < cant; i++) {
						if (strcmp(nom, (pa + i)->codigo) == 0) {
							cant -= 1;
							paux = (PAP*)malloc((cant) * sizeof(PAP));
							baja(pa, paux, cant + 1, nom);
							pa = (PAP*)realloc(pa, cant * sizeof(PAP));
							pa = paux;
							j++;
						}
					}
					if (j == 0) {
						printf("Contenedor inexistente.\n");
					}
					else {
						printf("Dada de baja realizada\n");
					}
				}
				system("pause");
				break;
			case 3:
				if (cant == 0) {
					printf("No hay contenedores disponbles.\n");
				}
				else {
					printf("Introduzca el codigo del contenedor cuyos datos quiere modificar:\n");
					getchar();
					gets_s(nom);
					for (i = 0; i < cant; i++) {
						if (strcmp(nom, (pa + i)->codigo) == 0) {
							modificar(pa, cant, nom);
							j++;
						}
					}
					if (j == 0) {
						printf("Contenedor inexistente.\n");
					}
					else {
						printf("Modificacion realizada\n");
					}
				}
				system("pause");
				break;
			case 4:
				if (cant == 0) {
					printf("No hay contenedores disponbles.\n");
				}
				else {
					printf("¿Cual es el codigo del contenedor del cual quiere ver sus datos?:\n");
					getchar();
					gets_s(nom);
					for (i = 0; i < cant; i++) {
						if (strcmp(nom, (pa + i)->codigo) == 0) {
							datos(pa, cant, nom);
							j++;
						}
					}
					if (j == 0) {
						printf("Contenedor inexistente.\n");
					}
				}
				system("pause");
				break;
			case 5:
				if (cant == 0) {
					printf("No hay contenedores disponbles.\n");
				}
				else {
					//arduino();
				}
				system("pause");
				break;
			}
		}
		system("cls");
	} while (op != 6);
	lista(pa, cant);
	free(pa);
	system("pause");
}
void inicializar(PAP *v, int can) {
	int i, j;
	for (i = 0; i < can; i++) {
		printf("CONTENEDOR %d\n", i + 1);
		printf("Introduzca el codigo del contenedor:\n");
		if (i == 0) {
			getchar();//a partir del sugundo bucle ya no es necesario porque ya no salta de linea, y al dejarlo tomaba un caracter de la palabra escrita
		}
		gets_s((v + i)->codigo);
		printf("Introduzca la localidad donde se encuentra:\n");
		gets_s((v + i)->localidad);
		printf("Introduzca la calle o avenida donde se encuentra:\n");
		gets_s((v + i)->calle);
		printf("Introduzca el numero de portal (o el más cercano):\n");
		scanf_s("%d", &(v + i)->num);
		printf("Introduzca el codigo postal de donde se encuentra:\n");
		scanf_s("%d", &(v + i)->postal);
		getchar();
		printf("Introduzca las coordenadas GPS de su ubicacion:\n");
		for (j = 0; j < 3; j++) {
			if (j == 0) {
				printf("Grados:\n");
			}
			else if (j == 1) {
				printf("Minutos:\n");
			}
			else {
				printf("Segundos:\n");
			}
			scanf_s("%d", &(v + i)->GPS[j]);
		}
		getchar();
	}
}
void alta(PAP* v) {
	int i, j;
	printf("NUEVO CONTENEDOR\n");
	printf("Introduzca el codigo del nuevo contenedor\n");
	getchar();
	gets_s(v->codigo);
	printf("Introduzca la localidad donde se encuentra:\n");
	gets_s(v->localidad);
	printf("Introduzca la calle o avenida donde se encuentra:\n");
	gets_s(v->calle);
	printf("Introduzca el numero de portal (o el mas cercano):\n");
	scanf_s("%d", &v->num);
	printf("Introduzca el codigo postal de donde se encuentra:\n");
	scanf_s("%d", &v->postal);
	getchar();
	printf("Introduzca las coordenadas GPS de su ubicacion:\n");
	for (j = 0; j < 3; j++) {
		if (j == 0) {
			printf("Grados:\n");
		}
		else if (j == 1) {
			printf("Minutos:\n");
		}
		else {
			printf("Segundos:\n");
		}
		scanf_s("%d", &v->GPS[j]);
	}
	getchar();
}
void baja(PAP* vie, PAP* nue, int can, char* cod) {
	int i, m = 0;
	for (i = 0; i < can; i++) {
		if (strcmp(cod, (vie + i)->codigo) != 0) {
			*(nue + m) = *(vie + i);
			m++;
		}
	}
}
void modificar(PAP* m, int c,char* cod) {
	int i, j, o = 0;
	for (i = 0; i < c; i++) {
		if (strcmp(cod, (m + i)->codigo) == 0) {
			printf("¿Que dato desea modificar?\n1.Codigo\n2.Localidad\n3.Calle o avenida\n4.Numero de portal\n5.Codigo postal\n3.Coordenadas GPS\n");
			scanf_s("%d", &o);
			if (o == 1) {
				printf("Introduzca el nuevo codigo:\n");
				getchar();
				gets_s((m + i)->codigo);
			}
			else if (o == 2) {
				printf("Introduzca la nueva localidad:\n");
				getchar();
				gets_s((m + i)->localidad);
			}
			else if (o == 3) {
				printf("Introduzca la nueva calle o avenida:\n");
				getchar();
				gets_s((m + i)->calle);
			}
			else if (o == 4) {
				printf("Introduzca el numero de protal:\n");
				scanf_s("%d", &(m + i)->num);
			}
			else if (o == 5) {
				printf("Introduzca el nuevo codigo postal:\n");
				scanf_s("%d", &(m + i)->postal);
			}
			else {
				printf("Introduzca las nuevas coordenadas GPS:\n");
				for (j = 0; j < 3; j++) {
					if (j == 0) {
						printf("Grados:\n");
					}
					else if (j == 1) {
						printf("Minutos:\n");
					}
					else {
						printf("Segundos:\n");
					}
					scanf_s("%d", &(m + i)->GPS[j]);
				}
			}
		}
	}
}
void datos(PAP* d, int c, char* cod) {
	int i, s = 0;
	for (i = 0; i < c; i++) {
		if (strcmp(cod, (d + i)->codigo) == 0) {
			printf("Codigo: %s\nDireccion postal: %s, n%d\n\t\t %d %s\nCoordenadas GPS: %d grados %d minutos %d segundos\n", (d + i)->codigo, (d + i)->calle, (d + i)->num, (d + i)->postal, (d + i)->localidad, (d + i)->GPS[0], (d + i)->GPS[1], (d + i)->GPS[2]);
		}
	}
}
void lista(PAP *l, int ca) {
	FILE* list;
	int i;
	errno_t err1;
	err1 = fopen_s(&list, "Listado.txt", "w+");
	if (err1 == 0) {
		printf("El archivo Listado.txt está abierto\n");
	}
	else {
		printf("El archivo Listado.txt NO está abierto\n");
	}
	for (i = 0; i < ca; i++) {
		fprintf(list, "Datos contenedor %d\n\tCodigo: %s\n\tDireccion postal: %s, n%d\n\t\t\t %d %s\n\tCoordenadas GPS: %d grados %d minutos %d segundos\n", i+1, (l + i)->codigo, (l + i)->calle, (l + i)->num, (l + i)->postal, (l + i)->localidad, (l + i)->GPS[0], (l + i)->GPS[1], (l + i)->GPS[2]);
	}
	if (fclose(list) == NULL) {
		printf("El archivo Listado.txt ha sido cerrado correctamente\n");
	}
	else {
		printf("Error en el cierre del archivo Listado.txt\n");
	}
}
/*void arduino(void) {
	Serial* Arduino;
	char puerto[] = "COM3"; //Puerto serie al que está conectado Arduino
	configura();
	Arduino = new Serial((char*)puerto);  // Establece la conexión con Arduino
	Talk_with_Arduino(Serial * Arduino);
}
void configura(void)
{
	setlocale(LC_ALL, "spanish");
}
void Talk_with_Arduino(Serial* Arduino)
{
	//char BufferSalida[MAX_BUFFER];
	char BufferEntrada[MAX_BUFFER];
	int bytesReceive, numero_recibido;

	if (Arduino->IsConnected()) // Si hay conexión con Arduino 
	{

		// Para enviar un mensaje y obtener una respuesta se utiliza la función Send_and_Receive
		// El mensaje está formado por un texto y un entero
		// El mensaje que se recibe está formado también por un texto y un entero.
		// Parámetros de la función:
		// El primero es la referencia a Arduino
		// El segundo es el mensaje que se desea enviar
		// El tercero es un entero que complementa al mensaje que se desea enviar
		// El cuarto es el vector de char donde se recibe la respuesta
		// El quinto es la referencia donde se recibe el entero de la respuesta
		// IMPORTANTE: El mensaje de respuesta que emite Arduino  debe incluir un espacio en blanco separando respuesta de valor
		// La función devuelve un entero con los bytes recibidos. Si es cero no se ha recibido nada.

		bytesReceive = Send_and_Receive(Arduino, "GET_ESTADO", -1, BufferEntrada, &numero_recibido);
		if (bytesReceive == 0)
			printf("No se ha recibido respuesta al mensaje enviado\n");
		else
			printf("Mensaje recibido %s %d\n", BufferEntrada, numero_recibido);
	}
	else
		printf("La comunicación con la plataforma hardware no es posible en este momento\n"); // Req 3
}
int Send_and_Receive(Serial* Arduino, const char* msg_out, int valor_out, char* msg_in, int* valor_in)
{
	char BufferSalida[MAX_BUFFER];
	char BufferEntrada[MAX_BUFFER];
	char* ptr;
	int bytesReceive;

	sprintf_s(BufferSalida, "%s\n%d\n", msg_out, valor_out);
	Send_to_hw(Arduino, BufferSalida);
	bytesReceive = Receive_from_hw(Arduino, BufferEntrada);
	if (bytesReceive != 0)
	{
		ptr = strpbrk(BufferEntrada, " ");
		if (ptr == NULL)
			*valor_in = -1;
		else
		{
			*valor_in = atoi(ptr);
			*ptr = '\0';
		}
		strcpy_s(msg_in, MAX_BUFFER, BufferEntrada);
	}
	return bytesReceive;
}
// Envía un mensaje a la plataforma hardware
void Send_to_hw(Serial* Arduino, char* BufferSalida)
{
	Arduino->WriteData(BufferSalida, strlen(BufferSalida));
}

//Recibe (si existe) un mensaje de la plataforma hardware
//Realiza MAX_INTENTOS_READ para evitar mensajes recortados
int Receive_from_hw(Serial* Arduino, char* BufferEntrada)
{
	int bytesRecibidos, bytesTotales = 0;
	int intentos_lectura = 0;
	char cadena[MAX_BUFFER];

	BufferEntrada[0] = '\0';
	while (intentos_lectura < MAX_INTENTOS_READ)
	{
		cadena[0] = '\0';
		bytesRecibidos = Arduino->ReadData(cadena, sizeof(char) * (MAX_BUFFER - 1));
		if (bytesRecibidos != -1)
		{
			cadena[bytesRecibidos] = '\0';
			strcat_s(BufferEntrada, MAX_BUFFER, cadena);
			bytesTotales += bytesRecibidos;
		}
		intentos_lectura++;
		Sleep(MS_ENTRE_INTENTOS);
	}
	return bytesTotales;
}*/
