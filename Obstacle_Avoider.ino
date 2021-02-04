//basic obstacle avoiding car
//Charlie Cox


//    Left motor truth table
//  ENA         IN1               IN2         Description  
//  LOW   Not Applicable    Not Applicable    Motor is off
//  HIGH        LOW               LOW         Motor is stopped (brakes)
//  HIGH        HIGH              LOW         Motor is on and turning forwards
//  HIGH        LOW               HIGH        Motor is on and turning backwards
//  HIGH        HIGH              HIGH        Motor is stopped (brakes)

//    Right motor truth table
//  ENB         IN3             IN4         Description  
//  LOW   Not Applicable   Not Applicable   Motor is off
//  HIGH        LOW             LOW         Motor is stopped (brakes)
//  HIGH        LOW             HIGH        Motor is on and turning forwards
//  HIGH        HIGH            LOW         Motor is on and turning backwards
//  HIGH        HIGH            HIGH        Motor is stopped (brakes)  

//    The direction of the car's movement
//  Left motor    Right motor     Description  
//  stop(off)     stop(off)       Car is stopped
//  forward       forward         Car is running forwards
//  forward       backward        Car is turning right
//  backward      forward         Car is turning left
//  backward      backward        Car is running backwards
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#include "SR04.h"
#include <Servo.h>

#define TRIG_PIN A5
#define ECHO_PIN A4 

Servo cameraServo;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int Echo = A4;
int Trig = A5;    

  //function definitions
  void forward(){
    digitalWrite(ENA, HIGH);  
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.print("Forward!");
  }
  void backward(){
    digitalWrite(ENA, HIGH);  
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.print("Backward!");
  }
  void left(int degree){
    int b = 200 - ((180 - degree) * 2);
    digitalWrite(ENA, HIGH);  
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.print("Left!");
    Serial.print(b);
    delay(b);
  }
  void right(int degree){
    int b = 200 - (degree * 2);
    digitalWrite(ENA, HIGH);  
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.print("Right!");
    Serial.print(b);
    delay(b);
  }
    void brake(){
    digitalWrite(ENA, HIGH);  
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("Brakes!");
    delay(2000);
  }
  int determine(){
    int degree;
    long highest = 0;
    cameraServo.write(0);
    delay(1000);
    for(int i = 0; i <= 180; i+=5)
    {
      delay(10);
      cameraServo.write(i);
      digitalWrite(Trig, LOW);
      delayMicroseconds(2);
      digitalWrite(Trig, HIGH);
      delayMicroseconds(20);
      digitalWrite(Trig, LOW);
      long b = pulseIn(Echo, HIGH);
      long c = b / 58;
      delay(10);
      Serial.println(c);
      if(c > highest)
      {
        highest = c;
        degree = i;
      }
      delay(10);
    }
    cameraServo.write(90);
    delay(500);
    Serial.println("highest is: ");
    Serial.println(highest);
    Serial.println("degree is: ");
    Serial.println(degree);
    return degree;
  }

  

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(ENA, LOW);  
  digitalWrite(ENB, LOW);

  cameraServo.attach(3);
  cameraServo.write(90);
  digitalWrite(Trig, HIGH);
  digitalWrite(Echo, HIGH);
  Serial.begin(9600);
   delay(10);
}

void loop() {
   a = sr04.Distance();
   Serial.println(a);
   int degree = -1;
   forward();
   if( a < 40 )
   {
    brake();
    degree = determine();
    Serial.println("degree in main is: ");
    Serial.println(degree);
      if (degree >= 90)
      {
          left(degree);
      }
      if ((degree <= 89) && (degree >= 0))
      {
         right(degree);
      }
   }

   

}
