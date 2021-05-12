#include <Servo.h>
Servo serv;
boolean sensor; //Variable almacena el estado del sensor (activado/desactivado)

int p = n;//n es el número del pin
int s = m;//m es el numero del pin
int ang = 0;
int estado = 0;

int PIR= 2 //Establece el pin 2 para el sensor PIR
int mot= 3 //Establece el pin 3 para el motor
int dato=1;
	
void apertura(int);
void prensadobajada(int);
void cierre(int);
void prensadosubida(int);

void setup()
{
	serv.attach(s);
	pinMode(p, INPUT);//EL PULSADOR
	serv.write(ang);//el servo estará a cero grados
	
	pinMode(PIR,INPUT); //Establece el pin del sensor como entrada
	pinMode(mot,OUTPUT); // Establece el pin del motor como salida
        Serial.begin(9600); //Definimos la velocidad de transferencia a 9600

}

void loop()
{
	estado = digitalRead(p);//LEER PULSADOR
	if (estado == HIGH /*&& dist.sensor>=0*/) {
		apertura(ang);
	}
	
	
	sensor=digitalRead(PIR); //Guarda el estado del sensor en la variable
        if(sensor==HIGH) //Si el sensor es activado
        {
           prensadobajada(dato);
        }
	
	prensadosubida(dato); //No depende del sensor
	
	estado = digitalRead(p);//LEER PULSADOR
	if (estado == LOW) {
		cierre(an);
	}
}
void apertura(int an) {
	for (an = 0; an < 45; an++) {
		serv.write(an);//se abre lentamente a 45 grados
	}
}

void prensadobajada(int dato)
{
        while (Serial.available()) //Mientras el puerto serie este accesible
        {
            byte dato = Serial.read();  //Guardamos en dato el valor leído del puerto serie
            if (dato==1)
	    {  
               digitalWrite(mot,HIGH); //Si es '1' ponemos el motor en marcha
            }
             
         }
 }
void cierre(int an){
	for (an = 45; an < 0; an--) {
		serv.write(an);//se cierra lentamente a 0 grados
	}
}

void prensadosubida(int dato)
{
	while(Serial.available())
	{
		byte dato=Serial.read();
		if(dato==1)
		{
			digitalWrite(mot,LOW); //Se necesita otro pin?
		}
	}
}
