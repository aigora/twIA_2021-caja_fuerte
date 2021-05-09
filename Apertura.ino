// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Apertura.ino
    Created:	27/04/2021 20:39:53
    Author:     PRUEBA\Jorge
*/

// Define User Types below here or use a .h file
//



// Define Function Prototypes that use User Types below here or use a .h file
//
#include <Servo.h>
Servo serv;

// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
int p = n;//n es el número del pin
int s = m;//m es el numero del pin
int ang = 0;
int estado = 0;
void apertura(int);
void setup()
{
	serv.attach(s);//s es el numero del pin 
	pinMode(p, INPUT);//EL PULSADOR
	serv.write(ang);//el servo estará a cero grados

}

// Add the main program code into the continuous loop() function
void loop()
{
	estado = digitalRead(p);//LEER PULSADOR
	if (estado == HIGH /*&& dist.sensor>=0*/) {
		apertura(ang);
	}
}
void apertura(int an) {
	for (an = 0; an < 45; an++) {
		serv.write(an);//se abre lentamente a 45 grados
	}
}
