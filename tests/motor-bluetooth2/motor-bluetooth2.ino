#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(10, 11); // (TXD, RXD) of HC-05
char data;
int n = 0;
char text;

// PARTE MOTOR

#define VELOCIDAD 3000
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

  // PARTE MOTOR

  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);

  digitalWrite(direccion, HIGH);
}

// mm guarda los numeros enviados hasta que se reciba un "/", en ese momento la variable se sobreescribe y el giro es ejecutado
String mm = "";
int isValid = 0; // Booleano indica si se recibió el carácter "/"

void loop() {
  if (Bluetooth.available()) {
    data = (Bluetooth.read());
    Serial.println(data);
    if (data == '/') {
      isValid = 1; // Al recibir un carácter "/" sobreescribe la variable
    }
    else {
      mm += data; // Añade a mm el último carácter enviado en caso de que no sea un "/" 
      isValid = 0; // Esta linea permite enviar números de más de un dígito
    }

  if (isValid == 1) {
      Serial.println("LISTO");
      Serial.println(mm);

      int vueltas = mm.toFloat() * 200;

      for (int i = 0; i<vueltas; i++) {      //Equivale al numero de vueltas (200 es 360º grados) o micropasos
        digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
        digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
        delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.
      }
      
      isValid = 0;
      mm = ""; // mm debe sobreescribirse
 
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
