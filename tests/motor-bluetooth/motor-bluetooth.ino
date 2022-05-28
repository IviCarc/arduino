#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <ctype.h>

SoftwareSerial Bluetooth(10, 11); // (TXD, RXD) of HC-05
char data;
int n = 0;
char text;

// PARTE MOTOR

#define VELOCIDAD 1700
int CIRCUNFERENCIA = 15.71;    // MILIMETROS
float DISTANCIAPASO = 0.07855; // MILIMETROS

int steps = 2;
int direccion = 3;
int pasos = 200;

void setup()
{
  Bluetooth.begin(9600);
  Bluetooth.print("HOLA");
  Serial.begin(9600);
  Serial.println("LISTO");

  // PARTE MOTOR

  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
}

String mm = "";
int isValid = 0;

void loop() {
  if (Bluetooth.available()) {
    data = (Bluetooth.read());
    Serial.println(data);
    if (data == '/') {
      isValid = 1;
    }
    else {
      mm += data;
      isValid = 0;
    }

  Serial.write(isValid);

  if (isValid == 1) {
      Serial.println("LISTO");
      Serial.println(mm);
      isValid = 0;
    }
  }

  // digitalWrite(direccion, HIGH);
  // delay(3000);

  // float pasosAMover = mov / DISTANCIAPASO;

  // for (int i = 0; i<pasosAMover; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  // {
  //   digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
  //   digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
  //   delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  // }
}
