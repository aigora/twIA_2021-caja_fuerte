#include <Servo.h>
#define Pinboton 22
#define Azul 38
#define Amarillo 42
#define Rojo 50
#define Echo 32
#define Trigger 34
 
Servo serv;
Servo myserv;
 
int val, val2 = 270;
int estado = 0;
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 30.0;           
const float umbral2 = 20.0;
const float umbral3 = 10.0;
float distancia = 0.0;

void apertura(int);
void cierre(int);
void iniciarTrigger();
float calcularDist();
void apagarLEDs();
void llenadoyprensado(float, int);
 
void setup() 
{ 
  Serial.begin(9600);
  serv.attach(26);
  serv.attach(31);
  pinMode(Pinboton, INPUT);
  pinMode(Azul, OUTPUT);
  pinMode(Amarillo, OUTPUT);
  pinMode(Rojo, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);     
} 
 
void loop() 
{ 
  estado = digitalRead(Pinboton);
  if (estado == HIGH) {
    apertura(estado);
  }else{
    cierre(estado);
  }
   // Preparamos el sensor de ultrasonidos
  iniciarTrigger();
 
  // Obtenemos la distancia
  float distancia = calcularDist();
 
  // Apagamos todos los LEDs
  apagarLEDs();
 
  // Lanzamos alerta si estamos dentro del rango de peligro
  if (distancia < umbral1)
  {
    // Lanzamos alertas
    llenadoyprensado(distancia, val2);
  }
}

void apertura(int estado)
{    
   val = 120;
   serv.write(val);
   delay(1000);
}

void cierre(int estado)
{
  val = 0;
  serv.write(val);
}

void apagarLEDs()
{
  // Apagamos todos los LEDs
  digitalWrite(Azul, LOW);
  digitalWrite(Amarillo, LOW);
  digitalWrite(Rojo, LOW);
}

void llenadoyprensado(float distancia, int val2)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    val2 = 180;
    digitalWrite(Azul, HIGH);
    serv.attach(26);
    myserv.write(val2);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    val2 = 180;
    digitalWrite(Amarillo, HIGH);
    serv.attach(26);
    myserv.write(val2);
  }
  else if (distancia <= umbral3)
  {
    val2 = 0;
    digitalWrite(Rojo, HIGH);
    serv.detach();
    myserv.attach(31);
    myserv.write(val2);
    delay(50);
  }
}

float calcularDist()
{
  unsigned long tiempo = pulseIn(Echo, HIGH);
 
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}

void iniciarTrigger()
{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
 
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(Trigger, LOW);
}
