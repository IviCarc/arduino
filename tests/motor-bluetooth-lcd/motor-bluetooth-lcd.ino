#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>


SoftwareSerial Bluetooth(3, 2); 
// (RXD, TXD) del arduino
// TXD: CABLE VERDE 
// RXD: CABLE MARRÓN 
LiquidCrystal_I2C lcd(0x27,16,2);
char dato;

// SG90 PIN 6

// PARTE MOTOR

int velocidadNEMA = 7000;
float DIAMETRO = 0.97; // CM
float CIRCUNFERENCIA = DIAMETRO * PI;    // CM
float DISTANCIAPASO = CIRCUNFERENCIA / 200; // CM

int stepsNEMA = 10; // CABLE VERDE
int direccionNEMA = 11; // CABLE GRIS
int pasos = 200;

Servo servoMotor; 

void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(9600);
<<<<<<< HEAD
  Serial.println("NASHE");
=======
  Serial.println("HOLA");
>>>>>>> 4fc7992acf17d6295fc22be87d61ffe0f49e3615
  servoMotor.attach(9); // CABLE AZUL

  // PARTES MOTOR

  pinMode(stepsNEMA, OUTPUT);
  pinMode(direccionNEMA, OUTPUT);

  digitalWrite(direccionNEMA, LOW);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LISTO");
}

// numeroTemporal guarda los numeros enviados hasta que se reciba un "/", en ese momento la variable se sobreescribe y el giro es ejecutado
String numeroTemporal = "";

float inputs[2]; // [ancho, longitud, cantidad]
int contador = 0;

int ready = 0; // Booleano indica si se recibieron los 3 números

void loop() {
  if (Bluetooth.available()) {
    dato = (Bluetooth.read());
<<<<<<< HEAD
    Serial.println(dato);
=======
    Serial.println("DATO");    
>>>>>>> 4fc7992acf17d6295fc22be87d61ffe0f49e3615
    if (dato == '/') {
        inputs[contador] = numeroTemporal.toFloat();
        contador += 1;
        numeroTemporal = "";
        if (contador == 2) {
            ready = 1;
        }
    } else {
        numeroTemporal += dato; // Añade a numeroTemporal el último carácter enviado en caso de que no sea un "/" 
    }

  if (ready == 1) {
    lcd.clear();
    lcd.print("CORTANDO ");
    lcd.print(int(inputs[0]));
    lcd.print("CM");

    // CANTIDAD DE CABLES NEMA

    for (int i = 0
    ; i < inputs[1]; i++) {
 
      servoMotor.write(0);
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print(i);
      lcd.print("/");
      lcd.print(int(inputs[1]));

      // LARGO CABLES NEMA

      for (float j = 0; j< (inputs[0] /  DISTANCIAPASO); j++) {     
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
Máximo Corriente Nema17 = 0,80 Amp
*/
