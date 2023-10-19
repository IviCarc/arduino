#include <PWMServo.h>

#include <Wire.h>
#include <SoftwareSerial.h>
// #include <Servo.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial Bluetooth(3, 2);
// (RXD, TXD) del arduino

LiquidCrystal_I2C lcd(0x27, 16, 2);
char dato;

// SG90 PIN 6

// PARTE MOTOR

int velocidadNEMA = 2500;
float DIAMETRO = 0.90;                       // CM
float CIRCUNFERENCIA = DIAMETRO * PI;        // CM
float DISTANCIAPASO = CIRCUNFERENCIA / 200;  // CM

int stepsNEMA = 10;
int direccionNEMA = 11;
int pasos = 200;

// Servo servoMotor;
PWMServo servoMotor;

int gradosPelado = 117;
int gradosCorte = 180;
int gradosReposo = 0;

void moverMotor(float largoCorte) {
  for (float j = 0; j < (largoCorte / DISTANCIAPASO); j++) {
    digitalWrite(stepsNEMA, HIGH);
    digitalWrite(stepsNEMA, LOW);
    delayMicroseconds(velocidadNEMA);  // Regula la velocidad, cuanto mas bajo mas velocidad.
  }
}

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("NASHE");
  Serial.println("HOLA");
  
  // PARTES MOTOR

  pinMode(stepsNEMA, OUTPUT);
  pinMode(direccionNEMA, OUTPUT);

  digitalWrite(direccionNEMA, LOW);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LISTO");
}

// numeroTemporal guarda los numeros enviados hasta que se reciba un "/", en ese momento la variable se sobreescribe y el giro es ejecutado
String numeroTemporal = "";

float inputs[3];  // [longitud, cantidad, largo pelado]
int contador = 0;

int ready = 0;  // Booleano indica si se recibieron los 2 números

void loop() {
  if (Bluetooth.available() > 0) {
    dato = (Bluetooth.read());
    // Serial.println(dato);
    if (dato == '.' || dato == '0' || dato == '1' || dato == '2' || dato == '3' || dato == '4' || dato == '5' || dato == '6' || dato == '7' || dato == '8' || dato == '9' || dato == '/') {
      if (dato == '/') {
        inputs[contador] = numeroTemporal.toFloat();
        Serial.println(numeroTemporal);
        contador += 1;
        numeroTemporal = "";
        if (contador == 3) {
          ready = 1;
        }
      } else {
        numeroTemporal += dato;  // Añade a numeroTemporal el último carácter enviado en caso de que no sea un "/"
      }
    }
  }

  if (ready == 1) {

    servoMotor.attach(9);  // CABLE AZUL

    float largoCable = inputs[0];
    float cantCables = inputs[1];
    float largoPelado = inputs[2];

    lcd.clear();
    lcd.print("CORTANDO ");
    lcd.print(largoCable);
    lcd.print("CM");

    // CANTIDAD DE CABLES NEMA

    for (int i = 0; i < cantCables; i++) {
      Bluetooth.print(i + 1);
      lcd.setCursor(0, 1);
      lcd.print("Avance: ");
      lcd.print(i + 1);
      lcd.print("/");
      lcd.print(int(cantCables));

      Serial.println(largoCable);
      Serial.println(cantCables);

      servoMotor.write(gradosReposo);
      delay(500);

      moverMotor(largoPelado);

      servoMotor.write(gradosPelado);
      delay(500);

      servoMotor.write(gradosReposo);
      delay(500);

      moverMotor(largoCable - 2 * largoPelado);

      servoMotor.write(gradosPelado);
      delay(500);
      
      servoMotor.write(gradosReposo);
      delay(500);

      moverMotor(largoPelado);

      servoMotor.write(gradosCorte);
      delay(1500);

      servoMotor.write(gradosReposo);
    }
    delay(500);
    Bluetooth.print('0');
    lcd.setCursor(0, 1);
    ready = 0;
    numeroTemporal = "";  // numeroTemporal debe sobreescribirse
    contador = 0;
    Serial.println("LISTO");
    lcd.clear();
    lcd.print("LISTO");

    servoMotor.detach();  // CABLE AZUL
  }
}