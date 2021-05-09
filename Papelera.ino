#include <Servo.h>
Servo serv;

int p = n;//n es el número del pin
int s = m;//m es el numero del pin
int ang = 0;
int estado = 0;
void apertura(int);
void setup()
{
	serv.attach(s);
	pinMode(p, INPUT);//EL PULSADOR
	serv.write(ang);//el servo estará a cero grados

}

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
