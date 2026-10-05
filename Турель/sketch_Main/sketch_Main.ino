#include <IRremote.h>  // Для ИК-приемника
#include <Servo.h>     // Для сервопривода

const int IR_PIN = 9;      // Пин ИК-приемника (D9)
const int SERVO1 = 10;  // Пин сервопривода (D10)
const int SERVO2 = 11;
const int SERVO3 = 12;
int d = 180;

Servo servo1;
Servo servo2;
Servo servo3;
bool isRotating = false;  // Флаг вращения

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);  // Инициализация ИК-приемника
  servo1.attach(SERVO1);
  servo2.attach(SERVO2);
  servo3.attach(SERVO3);
  servo1.write(90);           // Остановка сервопривода (90° = стоп)
  servo2.write(90); 
  servo3.write(90); 
  Serial.println("Готов! Нажмите кнопку 0x1C для старта/стопа.");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irValue = IrReceiver.decodedIRData.command;
    Serial.println(irValue);

    if (irValue == 0x18) {
      if (d < 180){
        d +=4;
      }
      servo1.write(d);  // Полная скорость в одну сторону (0 - в другую)
      Serial.println("Вращение вверх!");
      delay(50);
      }
    if (irValue == 0x52) {
      if (d > 80){
        d -=4;
      }
      servo1.write(d);  // Полная скорость в одну сторону (0 - в другую)
      Serial.println("Вращение вниз!");
      delay(50);
      }
    if (irValue == 0x1C) {
        servo2.write(100);  // Полная скорость в одну сторону (0 - в другую)
        Serial.println("Вращение запущено!");
        delay(120);
        servo2.write(90);
      }
    if (irValue == 0x5A) {
        servo3.write(80);  // Полная скорость в одну сторону (0 - в другую)
        Serial.println("Вращение на право!");
        delay(50);
        servo3.write(90);  
        }
    if (irValue == 0x8) {
        servo3.write(100);  // Полная скорость в одну сторону (0 - в другую)
        Serial.println("Вращение не лево!");
        delay(50);
        servo3.write(90);
        }
    IrReceiver.resume();  // Готов к следующей команде
  }
}