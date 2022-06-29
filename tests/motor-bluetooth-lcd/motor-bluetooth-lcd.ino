#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>


SoftwareSerial Bluetooth(10, 11); // (TXD, RXD) of HC-05
LiquidCrystal_I2C lcd(0x27,16,2);
char dato;

// PARTE MOTOR

int velocidadNEMA = 2000;
int velocidadEM = 20;
int DIAMETRO = 50; // MM
float CIRCUNFERENCIA = DIAMETRO * PI;    // MILIMETROS
float DISTANCIAPASO = CIRCUNFERENCIA / 200; // MILIMETROS

int stepsNEMA = 2;
int direccionNEMA = 3;
int pasos = 200;
int stepsEM= 4;
int direccionEM= 5;

Servo servoMotor; 

void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("LISTO");
  servoMotor.attach(12);

  // PARTES MOTOR

  pinMode(stepsNEMA, OUTPUT);
  pinMode(direccionNEMA, OUTPUT);

  digitalWrite(direccionNEMA, HIGH);

  pinMode(stepsEM,OUTPUT);
  pinMode(direccionEM,OUTPUT);

  digitalWrite(direccionEM, HIGH);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LISTO");
}

// numeroTemporal guarda los numeros enviados hasta que se reciba un "/", en ese momento la variable se sobreescribe y el giro es ejecutado
String numeroTemporal = "";

float inputs[3]; // [ancho, longitud, cantidad]
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
    lcd.clear();
    lcd.print("CORTANDO");
    

  // MOTOR PEQUEÑO

  for (int j = 0; j<inputs[0] * 48; j++) { 
        digitalWrite(stepsEM, HIGH);
        digitalWrite(stepsEM, LOW);
        delay(velocidadEM);     // Regula la velocidad, cuanto mas bajo mas velocidad.
        
   }

    // CANTIDAD DE CABLES NEMA

    for (int i = 0; i < inputs[2]; i++) {
      servoMotor.write(0);
      delay(2000);

      // LARGO CABLES NEMA

      for (float j = 0; j< (inputs[1] /  DISTANCIAPASO) * 10; j++) {     
        digitalWrite(stepsNEMA, HIGH);  
        digitalWrite(stepsNEMA, LOW);
        delayMicroseconds(velocidadNEMA);  // Regula la velocidad, cuanto mas bajo mas velocidad.
      }
      servoMotor.write(180);
      delay(2000);
      
    }
        ready = 0;
        numeroTemporal = ""; // numeroTemporal debe sobreescribirse
        contador = 0;
        Serial.println("LISTO");
        lcd.clear();
        lcd.print("LISTO");
    }
    servoMotor.write(0);
  }
}

/*CONSUMOS Y VOLTAJES
NEMA 17 a 17 VOLTIOS = 0,30 Amp
EM600 a 9 VOLTIOS = 0,14 Amp
Máximo Corriente Nema17 = 0,80 Amp
*/
