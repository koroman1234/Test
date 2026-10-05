#include <IRremote.h>  // Для ИК-приемника
#include <Servo.h>     // Для сервопривода

const int IR_PIN = 2;      // Пин ИК-приемника (D9)
const int SERVO_PIN = 9;  // Пин сервопривода (D10)
int d = 180;

Servo servo;
bool isRotating = false;  // Флаг вращения

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);  // Инициализация ИК-приемника
  servo.attach(SERVO_PIN);   // Подключение сервопривода
  servo.write(180);           // Остановка сервопривода (90° = стоп)
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
      servo.write(d);  // Полная скорость в одну сторону (0 - в другую)
      Serial.println("Вращение вверх!");
      delay(50);
      }
    if (irValue == 0x52) {
      if (d > 80){
        d -=4;
      }
      servo.write(d);  // Полная скорость в одну сторону (0 - в другую)
      Serial.println("Вращение вниз!");
      delay(50);
      }
    IrReceiver.resume();  // Готов к следующей команде
  }
}