#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Motor control pins
#define IN1A 38
#define IN1B 40
#define IN2A 42
#define IN2B 44
#define EN1 2 // PWM1
#define EN2 3 // PWM2

#define IN3A 46
#define IN3B 48
#define IN4A 50
#define IN4B 52
#define EN3 4 // PWM3
#define EN4 5 // PWM4

// Function prototypes

void Motor1_Forward(int Speed);
void Motor1_Backward(int Speed);
void Motor1_Break();

void Motor2_Forward(int Speed);
void Motor2_Backward(int Speed);
void Motor2_Break();

void Motor3_Forward(int Speed);
void Motor3_Backward(int Speed);
void Motor3_Break();

void Motor4_Forward(int Speed);
void Motor4_Backward(int Speed);
void Motor4_Break();

#endif