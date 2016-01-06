/*
This project is called Wheelchair training system.

The pin configuration is as follow:
Arduino    Models
----------------------------------------
PD0(TX)    BT RX
PD1(RX)    BT TX
PD2        
PD3(PWM)   L298 IN1
PD4        L298 ENA
PD5(PWM)   L298 IN2
PD6(PWM)   L298 IN3
PD7        L298 ENB
PD8
PD9(PWM)   L298 IN4
PD10(PWM)  Ultrasound1 echo (center)
PD11(PWM)  Ultrasound1 trig (center)
*/
//#include <Ultrasonic.h>

#define BTTX       0
#define BTRX       1
#define IN1        3
#define ENA        10
#define IN2        5
#define IN3        6
#define ENB        11
#define IN4        9
//#define UltraEch1  12
//#define UltraTrig1 13
int PWM_MAX_FB = 150; // PWM for "forward" and "backward" command
int PWM_MAX_LR = 150; // PWM for "left" and "right" command
int duration = 1200;
int distance = 0;
char data;

//Ultrasonic ultrasonic1(UltraTrig1,UltraEch1);

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  //pinMode(UltraEch1, INPUT);
  //pinMode(UltraTrig1, OUTPUT);
  Serial.begin(9600);
  reset();
}

void loop() {
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  while(1){
    if (Serial.available() > 0) {
      char incomingByte = 0;
      incomingByte = Serial.read();
      switch (incomingByte) {
        case '1':
          Serial.println("forward");
          //if(checkUltra1()){
            forward();
          //}
          break;
        case '2':
          Serial.println("backward");
          backward();
          break;
        case '3':
          Serial.println("left");
          left();
          break;
        case '4':
          Serial.println("right");
          right();
          break;
        case '5':
          if(PWM_MAX_FB < 245){
            PWM_MAX_FB = PWM_MAX_FB + 10;
            Serial.print("Foward-Back speed=");
            Serial.println(PWM_MAX_FB);
          }
          break;
        case '6':
          if(PWM_MAX_FB > 50){
            PWM_MAX_FB = PWM_MAX_FB - 10;
            Serial.print("Foward-Back speed=");
            Serial.println(PWM_MAX_FB);
          }
          break;
        case '7':
          if(PWM_MAX_LR < 245){
            PWM_MAX_LR = PWM_MAX_LR + 10;
            Serial.print("Left-Right speed=");
            Serial.println(PWM_MAX_LR);
          }
          break;
        case '8':
          if(PWM_MAX_LR > 50){
            PWM_MAX_LR = PWM_MAX_LR - 10;
            Serial.print("Left-Right speed=");
            Serial.println(PWM_MAX_LR);
          }
          break; 
        /*  
        case '9':
          distance = (int)checkUltra1();
          Serial.print(distance);
          break;
        */
        case 'a':
          if(duration <= 3000){
             duration += 300;
             Serial.print("duration=");
             Serial.println(duration);
           }
           break;
        case 'b':
          if(duration > 1000){
             duration -= 300;
             Serial.print("duration=");
             Serial.println(duration);
          }
          break;
        /*
        case 'c':
          Serial.print(duration);
          break;  
        case 'd':
          Serial.print(PWM_MAX_FB);
          break;
        case 'e':
          Serial.print(PWM_MAX_LR);
          break;
        */
        default:
          Serial.println(incomingByte);
          break;
        }
      }
   }
}

void backward(){
    analogWrite(ENA,255);
    analogWrite(ENB,255);
    analogWrite(IN1, PWM_MAX_FB);
    analogWrite(IN2, 0);
    analogWrite(IN3, PWM_MAX_FB);
    analogWrite(IN4, 0);
    delay(duration);
    reset();
    delay(100);
}

void forward(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
  analogWrite(IN1, 0);
  analogWrite(IN2, PWM_MAX_FB);
  analogWrite(IN3, 0);
  analogWrite(IN4, PWM_MAX_FB);
  delay(duration);
  reset();
  delay(100);
}

void right(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
    analogWrite(IN1, 0);
    analogWrite(IN2, PWM_MAX_LR);
    analogWrite(IN3, PWM_MAX_LR);
    analogWrite(IN4, 0);
    delay(1200);
    reset();
    delay(100);
}

void left(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
    analogWrite(IN1, PWM_MAX_LR);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, PWM_MAX_LR);
    delay(1200);
    reset();
    delay(100);
}

void reset(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

/*
int checkUltra1(){
  float cmMsec;
  int check = 0;
  
  long microsec = ultrasonic1.timing();
  cmMsec = ultrasonic1.convert(microsec, Ultrasonic::CM);
  
  if(cmMsec > 30){
    check = 1;
  }else{
    check = 0;
  }
  
  return check;
}
*/
