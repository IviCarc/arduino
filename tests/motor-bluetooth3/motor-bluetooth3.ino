#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(10, 11); // (TXD, RXD) of HC-05
char dato;

// PARTE MOTOR

#define VELOCIDAD 650
int CIRCUNFERENCIA = 15.71;    // MILIMETROS
float DISTANCIAPASO = 0.07855; // MILIMETROS

int steps = 2;
int direccion = 3;
int pasos = 200;

void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("LISTO");

  // PARTES MOTOR

  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);

  digitalWrite(direccion, HIGH);
}

// numeroTemporal guarda los numeros enviados hasta que se reciba un "/", en ese momento la variable se sobreescribe y el giro es ejecutado
String numeroTemporal = "";

float inputs[3];
int contador = 0;

int ready = 0; // Booleano indica si se recibieron los 3 números

void loop() {
  if (Bluetooth.available()) {
    dato = (Bluetooth.read());
    if (dato == '/') {
        inputs[contador] = numeroTemporal.toFloat();
        contador += 1;
        numeroTemporal = "";
        if (contador == 3) {
            ready = 1;
        }
    } else {
        numeroTemporal += dato; // Añade a numeroTemporal el último carácter enviado en caso de que no sea un "/" 
    }

  if (ready == 1) {

    for (int i = 0; i < inputs[2]; i++) {
      for (int j = 0; j<inputs[1] * 200; j++) {      //Equivale al numero de vueltas (200 es 360º grados) o micropasos
        digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
        digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
        delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.
      }
      delay(1000);
    }
        ready = 0;
        numeroTemporal = ""; // numeroTemporal debe sobreescribirse
        contador = 0;
        Serial.println("LISTO");
    }
  }
}
