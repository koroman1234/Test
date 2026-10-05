#include <IRremote.h>  // Для ИК-приемника
#include <Servo.h>     // Для сервопривода

const int IR_PIN = 2;      // Пин ИК-приемника (D9)
const int SERVO_PIN = 9;  // Пин сервопривода (D10)

Servo servo;
bool isRotating = false;  // Флаг вращения

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);  // Инициализация ИК-приемника
  servo.attach(SERVO_PIN);   // Подключение сервопривода
  servo.write(90);           // Остановка сервопривода (90° = стоп)
  Serial.println("Готов! Нажмите кнопку 0x1C для старта/стопа.");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irValue = IrReceiver.decodedIRData.command;
    Serial.println(irValue);

    if (irValue == 0x5A) {


        servo.write(80);  // Полная скорость в одну сторону (0 - в другую)
        Serial.println("Вращение на право!");
        delay(50);
        servo.write(90);
          
        }
    if (irValue == 0x8) {


        servo.write(100);  // Полная скорость в одну сторону (0 - в другую)
        Serial.println("Вращение не лево!");
        delay(50);
        servo.write(90);
          
        }
    IrReceiver.resume();  // Готов к следующей команде
  }
}