#include "motorControl.h"

void Motor1_Forward(int Speed){
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN1B, LOW);
  analogWrite(EN1, Speed);
}

void Motor1_Backward(int Speed){
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, HIGH);
  analogWrite(EN1, Speed);
}

void Motor1_Break(){
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, LOW);
}

void Motor2_Forward(int Speed){
  digitalWrite(IN2A, LOW);
  digitalWrite(IN2B, HIGH);
  analogWrite(EN2, Speed);
}

void Motor2_Backward(int Speed){
  digitalWrite(IN2A, HIGH);
  digitalWrite(IN2B, LOW);
  analogWrite(EN2, Speed);
}

void Motor2_Break(){
  digitalWrite(IN2A, LOW);
  digitalWrite(IN2B, LOW);
}

void Motor3_Forward(int Speed){
  digitalWrite(IN3A, LOW);
  digitalWrite(IN3B, HIGH);
  analogWrite(EN3, Speed);
}

void Motor3_Backward(int Speed){
  digitalWrite(IN3A, HIGH);
  digitalWrite(IN3B, LOW);
  analogWrite(EN3, Speed);
}

void Motor3_Break(){
  digitalWrite(IN3A, LOW);
  digitalWrite(IN3B, LOW);
}

void Motor4_Forward(int Speed){
  digitalWrite(IN4A, HIGH);
  digitalWrite(IN4B, LOW);
  analogWrite(EN4, Speed);
}

void Motor4_Backward(int Speed){
  digitalWrite(IN4A, LOW);
  digitalWrite(IN4B, HIGH);
  analogWrite(EN4, Speed);
}

void Motor4_Break(){
  digitalWrite(IN4A, LOW);
  digitalWrite(IN4B, LOW);
}

void Car_Left(int angle){
  Motor1_Backward(900);
  Motor2_Backward(900);
  Motor3_Forward(900);
  Motor4_Forward(900);
/*   angle *= 1000;
  while (angle--);
  Motor1_Break();
  Motor2_Break();
  Motor3_Break();
  Motor4_Break(); */
}

void Car_Right(int angle){
  Motor1_Forward(900);
  Motor2_Forward(900);
  Motor3_Backward(900);
  Motor4_Backward(900);
/*   angle *= 1000;
  while (angle--);
  Motor1_Break();
  Motor2_Break();
  Motor3_Break();
  Motor4_Break(); */
}

void Car_Forward(int speed){
  Motor1_Forward(speed);
  Motor2_Forward(speed);
  Motor3_Forward(speed);
  Motor4_Forward(speed);
}

void Car_Backward(int speed){
  Motor1_Backward(speed);
  Motor2_Backward(speed);
  Motor3_Backward(speed);
  Motor4_Backward(speed);
}
