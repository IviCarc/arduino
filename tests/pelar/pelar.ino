#include <Servo.h>

Servo ServoMotor;

int velocidadNEMA = 1500;
float DIAMETRO = 0.97;                       // CM
float CIRCUNFERENCIA = DIAMETRO * PI;        // CM
float DISTANCIAPASO = CIRCUNFERENCIA / 200;  // CM

int stepsNEMA = 10;      // CABLE VERDE
int direccionNEMA = 11;  // CABLE GRIS
int pasos = 200;

int gradosPelado = 160;
int gradosCorte = 180;
int gradosReposo = 20;

void moverMotor(float largoCorte) {
    for (float j = 0; j < (largoCorte / DISTANCIAPASO); j++) {
      digitalWrite(stepsNEMA, HIGH);
      digitalWrite(stepsNEMA, LOW);
      delayMicroseconds(velocidadNEMA);  // Regula la velocidad, cuanto mas bajo mas velocidad.
  }
}

void setup() {
  ServoMotor.attach(9);
  ServoMotor.write(gradosReposo);

  pinMode(stepsNEMA, OUTPUT);
  pinMode(direccionNEMA, OUTPUT);

  digitalWrite(direccionNEMA, LOW);
}

void loop() {
  ServoMotor.write(gradosReposo);
  delay(500);
  moverMotor(1);
  ServoMotor.write(gradosPelado);
  delay(500);
  ServoMotor.write(gradosReposo);
  delay(500);
  moverMotor(3);
  ServoMotor.write(gradosPelado);
  delay(500);
  ServoMotor.write(gradosReposo);
  delay(500);
  moverMotor(1);
  ServoMotor.write(gradosCorte);
  delay(1000);
}