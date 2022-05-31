#include <stdio.h>
#include <ctype.h>

int CIRCUNFERENCIA = 15.71; // MILIMETROS
float DISTANCIAPASO = 0.07855; //MILIMETROS

int VELOCIDAD = 1400; // A mayor número menor velocidad
// !! NO BAJAR DE 600 !! //
int stepsNEMA = 2;
int direccionNEMA = 3;
int reset = 10;
int pasos = 200;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(stepsNEMA, OUTPUT); 
  pinMode(direccionNEMA, OUTPUT); 
  pinMode(reset, OUTPUT);
}

int mov = 10;

// the loop routine runs over and over again forever:
void loop() {


  digitalWrite(direccionNEMA, HIGH);
  delay(3000);

  float pasosAMover = mov / DISTANCIAPASO;

  for (int i = 0; i<400; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
    digitalWrite(stepsNEMA, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(stepsNEMA, LOW); // al A4988 de avanzar una vez por cada pulso de energia.  
    delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  } 

  digitalWrite(direccionNEMA, LOW);
  delay(3000);

  for (int i = 0; i<200; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
    digitalWrite(stepsNEMA, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(stepsNEMA, LOW); // al A4988 de avanzar una vez por cada pulso de energia.  
    delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  } 

}
