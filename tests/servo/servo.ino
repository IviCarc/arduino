#include <Servo.h>

Servo servo;

void setup() {
    servo.attach(6);
    Serial.begin(9600);
}

void loop() {
    servo.write(0);
    delay(20);
    Serial.println(servo.read());
}
