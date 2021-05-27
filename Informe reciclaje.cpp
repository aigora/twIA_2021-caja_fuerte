#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	float kilos;
	int veces;
}PAP;
void informe(FILE* , PAP*, int);
int main() {
	FILE* f;
	PAP *p;
	errno_t err;
	int i = 5;//variable que se recibiría desde arduino que recopilaría las veces que se ha prensado la basura, esto es un ejemplo para mostrar su funcionamiento 
	err = fopen_s(&f, "Reciclaje.txt", "w+");
	if (err == 0) {
		printf("El archivo Reciclaje.txt está abierto\n");
	}
	else {
		printf("El archivo Reciclaje.txt NO está abierto\n");
	}
	p = (PAP*)malloc(i * sizeof(PAP));
	informe(f, p, i);
	fprintf(f, "Gracias por cuidar del medio ambiente\n");
	if (fclose(f) == NULL) {
		printf("\n Archivo cerrado correctamente\n");
	}
	else {
		printf("\n Error en el cierre del archivo\n");
	}
	system("pause");
}
void informe(FILE *fi, PAP* v, int x) {
	int j;
	float tot = 0.0;
	for (j = 0; j < x; j++) {
		(v + j)->veces = j + 1;
		(v + j)->kilos = 0.25; 
		tot += (v + j)->kilos;
		fprintf(fi, "Has reciclado %d veces,  %f kilos. Eso equivale a %f kilos totales hoy\n", (v + j)->veces, (v + j)->kilos, tot);
	}
	free(v);
}
