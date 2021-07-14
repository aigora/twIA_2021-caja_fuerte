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
int cont1, cont2 = 0, cont3 = 0, p, c;
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
void llenadoyprensado(float, int, int, int);
void procesar_mensaje(int, int, int);

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
        cont1++;
    }
    else {
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
      p=0;
        // Lanzamos alertas
        llenadoyprensado(distancia, val2, cont2, cont3);
        if (distancia <= umbral2)
        {
          if(distancia <= umbral3)
          {
            cont3++;
            p++;
            delay(2000);
              if(distancia < umbral2 && p > 0)
            {
              c++;
            }
          }
        }
    }
    if (Serial.available() > 0)  // Si hay mensajes procedentes del PC
    {  
        procesar_mensaje(cont1, cont3, c);
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

void llenadoyprensado(float distancia, int val2, int cont2, int cont3)
{
    if (distancia < umbral1 && distancia >= umbral2)
    {
        val2 = 180;
        digitalWrite(Azul, HIGH);
        serv.attach(26);
    }
    else if (distancia < umbral2 && distancia > umbral3)
    {
        val2 = 180;
        digitalWrite(Amarillo, HIGH);
        if(cont2 > 0)
        {
      serv.detach();
      myserv.detach();
      cont3=0;
        }
    }
    else if (distancia <= umbral3)
    {
      cont2=0;
        val2 = 180;
        digitalWrite(Rojo, HIGH);
        serv.detach();
        myserv.attach(31);
        myserv.write(val2);
        delay(500);
        cont2++;
        myserv.write(0);
    }
}

float calcularDist()
{
    unsigned long tiempo = pulseIn(Echo, HIGH);

    float distancia = tiempo * 0.000001 * sonido / 2.0;
    //Serial.print(j);
    //Serial.print("cm");
    //Serial.println();
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

void procesar_mensaje(int cont1, int cont3, int c)
{
    int numero;
    String cadena = Serial.readStringUntil('\n'); // Lee mensaje
    String valor = Serial.readStringUntil('\n');  // Lee valor
    numero = valor.toInt();  // Transforma valor a entero
    if (cadena.equals("GET_ESTADO"))
    {
        Serial.println("Veces_que_se_ha_arrojado_basura_en_este_contenedor_desde_la_ultima_compactacion ");
        Serial.println(cont1);
    }
    else if (cadena.equals("GET_COMP"))
    {
        Serial.println("Compactaciones ");
        Serial.println(cont3);
    }
    else if (cadena.equals("GET_ALERTA"))
    {
      if(c==0)
      {
        Serial.println("No_hay_alertas ");
      }
      else
      {
        Serial.println("ALERTA.Incompresible ");
      }
    }
}
