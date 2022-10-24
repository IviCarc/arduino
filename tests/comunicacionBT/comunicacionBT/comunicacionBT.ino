#include <SoftwareSerial.h>

SoftwareSerial bluetooth(3,2);

float DIAMETRO = 0.97; // CM
float CIRCUNFERENCIA = DIAMETRO * PI;    // CM
float DISTANCIAPASO = CIRCUNFERENCIA / 200; // CM

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(10, OUTPUT);
}

int contador = 0;
float inputs[2];
String numeroTemporal = "";
char caracter;
int ready = 0;

void loop() {
  if (bluetooth.available() > 0) {
    caracter = bluetooth.read();
    if (caracter == '/') {
      inputs[contador] = numeroTemporal.toFloat();
      numeroTemporal = "";
      contador++;
      if (contador == 2) {
        ready = 1;
      }
    } else {
      numeroTemporal += caracter;
    }
  }

  if (ready == 1) {
    for (int i = 0; i < inputs[1]; i++) {
      for (int j = 0; j < inputs[0] / DISTANCIAPASO; j++) {
        digitalWrite(10, HIGH);
        digitalWrite(10, LOW);
        delayMicroseconds(1700);
      }
      bluetooth.print(i + 1);
    }
    delay(500);
    bluetooth.println('0');
    ready = 0;
    numeroTemporal = "";
    contador = 0;
  }
  // put your main code  here, to run repeatedly:
}
