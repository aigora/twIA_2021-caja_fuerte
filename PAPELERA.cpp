// PAPELERA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
//Funciones que vamos a utilizar

int apertura();
void cierre();
int prensadobajada();
void prensadosubida();

int main() {
	int cont = 0;
	do {
		apertura();
		cont++;
	} while (cont <= 4);
	//temporizador
	prensadobajada();
	cont = 0;
}
int apertura() {
	//Al pulsar el botón, se activa el servomotor
	//Temporizador
	//Llamamos a la función cierre
	return 1;
}
void cierre() {
	//El servomotor vuelve a su estado original
}
int prensadobajada() {
	//Se acciona el motor para simular una prensa
	//Temporizador
	//Llamamos a la función prensadosubida
	return 1;
}
void prensadosubida() {
	//El motor vuelve a su estado original
}


