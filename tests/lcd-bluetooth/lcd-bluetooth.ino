#include <Wire.h>  
#include <SoftwareSerial.h>
#include <stdio.h>
#include <ctype.h>

SoftwareSerial Bluetooth(10,11);      // (TXD, RXD) of HC-05
char BT_input;
int n = 0;
char text;

void setup() 
{
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.print("HOLA");
}


void loop()  
{
  if (Bluetooth.available())
  {
    BT_input=(Bluetooth.read());
    Serial.write(BT_input);
    /*if (isalpha(BT_input) != 0 || isdigit(BT_input) !=0 || BT_input == ' ') {
        text = BT_input;
        Serial.print(text);
      }*/
  }
}
