#include <Servo.h> 

const int s1 = 100;
const int s2 = 135 + 90;
const int s3 = 70;
const int s4 = 60 - 90;
const int s5 = 145;
const int s6 = 67 - 90;
const int s7 = 55;
const int s8 = 140 + 90;
int servo1 = 13;
int servo2 = 12;
int servo3 = 14;
int servo4 = 27;
int servo5 = 26;
int servo6 = 25;
int servo7 = 33;
int servo8 = 32;
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo Servo7;
Servo Servo8;
float legCornerTop;
float legCornerBottom;

float startPositionFrontTop;
float startPositionFrontBottom;
float startPositionBackTop;
float startPositionBackBottom;

float frontRearCornerTop;
float frontRearCornerBottom;
float frontCornerTop;
float frontCornerBottom;
float frontMiddleCornerTop;
float frontMiddleCornerBottom;
float frontBeforeCornerTop;
float frontBeforeCornerBottom;

float backMiddleCornerTop;
float backMiddleCornerBottom;
float backRearCornerTop;
float backRearCornerBottom;
float backCornerTop;
float backCornerBottom;
float backBeforeCornerTop;
float backBeforeCornerBottom;

int numberOfSteps = 40;   //Количество шагов
float h = 6;
float l = 0;
float B;
int d = 1;
float s;
int pauseFlag1;
int pauseFlag2;
int pauseFlag3;
int pauseFlag4;
int k1;
int k2;
int k3;
int k4;
String direction = "forward";
int directionLeftLegs;
int directionRightLegs;
int const x = 5;
static unsigned long previousMillis = 0; // Время последнего обновления
const unsigned long interval = 50;       // Интервал между шагами (мс)
static int i1 = 0;                       // Текущие шаги
static int i2 = 10;  
static int i3 = 20;
static int i4 = 30;
struct Degrees {
  float servTop;
  float servBottom;
};
Degrees adjustment[4];
Degrees calculateDegrees(float h, float l);
//-----------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("------------");

  Servo1.attach(servo1);
  Servo2.attach(servo2);
  Servo3.attach(servo3);
  Servo4.attach(servo4);
  Servo5.attach(servo5);
  Servo6.attach(servo6);
  Servo7.attach(servo7);
  Servo8.attach(servo8);
  legCornerTop = calculateDegrees(5.5, 0).servTop;//Верхний верхний угол
  legCornerBottom = calculateDegrees(5.5, 0).servBottom;//Нижний верхний угол
//--------------# Перед #---------------
  frontRearCornerTop = calculateDegrees(7, -4).servTop; //Верхний стартовый угол
  frontRearCornerBottom = calculateDegrees(7, -4).servBottom; //Нижний стартовый угол
  frontBeforeCornerTop = calculateDegrees(7, 1).servTop; //Верхний передний угол
  frontBeforeCornerBottom = calculateDegrees(7, 1).servBottom; //Нижний передний угол
  frontMiddleCornerTop = calculateDegrees(7, 0).servTop;
  frontMiddleCornerBottom = calculateDegrees(7, 0).servBottom;
  frontCornerTop = (calculateDegrees(7, 1).servTop - calculateDegrees(7, -4).servTop) / numberOfSteps; //Верхний шаг
  frontCornerBottom = (calculateDegrees(7, 1).servBottom - calculateDegrees(7, -4).servBottom) / numberOfSteps;//Нижный шаг
  
//--------------# Зад #---------------
  backRearCornerTop = calculateDegrees(7, -1).servTop; //Верхний стартовый угол
  backRearCornerBottom = calculateDegrees(7, -1).servBottom; //Нижний стартовый угол
  backBeforeCornerTop = calculateDegrees(7, 4).servTop; //Верхний передний угол
  backBeforeCornerBottom = calculateDegrees(7, 4).servBottom; //Нижний передний угол
  backMiddleCornerTop = calculateDegrees(7, 0).servTop;
  backMiddleCornerBottom = calculateDegrees(7, 0).servBottom;
  backCornerTop = (calculateDegrees(7, 4).servTop - calculateDegrees(7, -1).servTop) / numberOfSteps; //Верхний шаг
  backCornerBottom = (calculateDegrees(7, 4).servBottom - calculateDegrees(7, -1).servBottom) / numberOfSteps;//Нижный шаг
  
}
//----------------------------------
void loop() {

  unsigned long currentMillis = millis();
  k1 = 1;
  k2 = 1;
  k3 = 1;
  k4 = 1;
  if (i1 >= numberOfSteps/ 5 ){
    k1 = -1;
  }
  if (i2 >= numberOfSteps/ 5 ){
    k2 = -1;
  }
  if (i3 >= numberOfSteps/ 5 ){
    k3 = -1;
  }
  if (i4 >= numberOfSteps/ 5 ){
    k4 = -1;
  }
  if (direction == "forward"){
    d = 1;
    startPositionFrontTop = frontRearCornerTop;
    startPositionFrontBottom = frontRearCornerBottom;
    startPositionBackTop = backRearCornerTop;
    startPositionBackBottom = backRearCornerBottom;
  }
  if (direction == "back"){
    d = -1;
    startPositionFrontTop = frontBeforeCornerTop;
    startPositionFrontBottom = frontBeforeCornerBottom;
    startPositionBackTop = backBeforeCornerTop;
    startPositionBackBottom = backBeforeCornerBottom;
  }
  /*
  if (direction == "Left"){
  	
  }
  if (direcrion == "Rait"){
  	
  }
  if (direction == "Stop"){
  	
  }
  */
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Обновляем время последнего шага

    // Устанавливаем углы для сервоприводов
    //-----------------# Нога №1 #------------------
    if (pauseFlag1 > 0){
      pauseFlag1--;
    }
    else {
      Servo1.write(s1 + (frontCornerTop * i1)* directionLeftLegs + startPositionFrontTop);
      Servo2.write(s2 + ((frontCornerBottom * i1) * k1) * directionLeftLegs - startPositionFrontBottom);
      i1++;
      if (i1 >= numberOfSteps) {
        Servo1.write(s1 + legCornerTop);
        Servo2.write(s2 - legCornerBottom);
        i1 = 0; // Сбрасываем счётчик, если достигли конца
        pauseFlag1= 3;
      }
    }
    //-----------------# Нога №2 #------------------
    if (pauseFlag2 > 0){
      pauseFlag2--;
    }
    else {
      Servo3.write(s3 - (frontCornerTop * i2) * directionRightLegs - startPositionFrontTop);
      Servo4.write(s4 - ((frontCornerBottom * i2) * k2) * directionRightLegs + startPositionFrontBottom);
      i2++;
      if (i2 >= numberOfSteps) {
        Servo3.write(s3 - legCornerTop);
        Servo4.write(s4 + legCornerBottom);
        i2 = 0; // Сбрасываем счётчик, если достигли конца
        pauseFlag2= 3;
      }
    }

    //-----------------# Нога №3 #------------------
    if (pauseFlag3 > 0){
      pauseFlag3--;
    }
    else {
      Servo5.write(s5 - (backCornerTop * i3) * directionRightLegs - startPositionBackTop);
      Servo6.write(s6 - ((backCornerBottom * i3)* k3) * directionRightLegs + startPositionBackBottom);
      i3++;
      if (i3 >= numberOfSteps) {
        Servo5.write(s5 - legCornerTop);
        Servo6.write(s6 + legCornerBottom);
        i3 = 0; // Сбрасываем счётчик, если достигли конца
        pauseFlag3= 3;
      }
    }
    //-----------------# Нога №4 #------------------
    if (pauseFlag4 > 0){
      pauseFlag4--;
    }
    else {
      Servo7.write(s7 + (backCornerTop * i4) *directionLeftLegs + startPositionBackTop);
      Servo8.write(s8 + ((backCornerBottom * i4)* k4) * directionLeftLegs - startPositionBackBottom);
      i4++;
      if (i4 >= numberOfSteps) {
        Servo7.write(s7 + legCornerTop);
        Servo8.write(s8 - legCornerBottom);
        i4 = 0; // Сбрасываем счётчик, если достигли конца
        pauseFlag4= 3;
      }
    }
  }
}
//-----------------------------------------------------------
Degrees calculateDegrees(float h, float l) {х
  Degrees result;
  float b = (sqrt(h * h + l * l));
  float G = degrees(acos(((2 * x * x) - b * b) / (2 * x * x)));
  if (l > 0) {
    B = ((180 - G) / 2) + degrees(acos(h / b));
  } 
  else {
    B = ((180 - G) / 2) - degrees(acos(h / b));
  }
  result.servTop = B;
  result.servBottom = G;
  return result;
}