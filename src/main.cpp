#include <Arduino.h>
#include "encoder.h"
#include "motorControl.h"

int n = 20;
int v2 = 0;
int v4 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(ENCODER_1A, INPUT_PULLUP);
  pinMode(ENCODER_2A, INPUT_PULLUP);
  pinMode(ENCODER_3A, INPUT_PULLUP);
  pinMode(ENCODER_4A, INPUT_PULLUP);

  pinMode(IN1A, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(IN2A, OUTPUT);
  pinMode(IN2B, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(IN3A, OUTPUT);
  pinMode(IN3B, OUTPUT);
  pinMode(EN3, OUTPUT);

  pinMode(IN4A, OUTPUT);
  pinMode(IN4B, OUTPUT);
  pinMode(EN4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_1A), encoder1_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_2A), encoder2_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_3A), encoder3_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_4A), encoder4_isr, RISING);


}

void loop() {
  // put your main code here, to run repeatedly:
  // tinh goc quay: angle = (pulsesCurrent) * 360/(RPM: so xung tren 1 vong)
  //Tinh goc quay khi quay hon 1 vong
  // int pulsesCurrenRound = encoder1_value % 666;
  

  Serial.println("Encoder 1 value: " + String(encoder1_value) + "\tSo vong quay: " + String(encoder1_value/333) + "\tGoc quay: " + String(((encoder1_value % 333) * 360 ) / 333) );
  Serial.println("Encoder 2 value: " + String(encoder2_value) + "\tSo vong quay: " + String(encoder2_value/333) + "\tGoc quay: " + String(((encoder2_value % 333) * 360 ) / 333) );
  Serial.println("Encoder 3 value: " + String(encoder3_value) + "\tSo vong quay: " + String(encoder3_value/333) + "\tGoc quay: " + String(((encoder3_value % 333) * 360 ) / 333) );
  Serial.println("Encoder 4 value: " + String(encoder4_value) + "\tSo vong quay: " + String(encoder4_value/333) + "\tGoc quay: " + String(((encoder4_value % 333) * 360 ) / 333) );
  Serial.println(n);
  Serial.println("---------------------");

  v2 = abs(encoder2_value / 333);
  v4 = abs(encoder4_value / 333);

  if (v4 > 0 && v4 < 20){
    Car_Forward(700);
  }
  else if (v4 < 24) {
    Car_Left(0);
  }
  else if (v4 < 40){
    Car_Forward(700);
  }
  else if (v2 < 40){
    Car_Right(0);
  }
  else Car_Forward(700);
  delay(200);

}
