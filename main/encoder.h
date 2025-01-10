#ifndef ENCODER_H
#define ENCODER_H


#include <Arduino.h>

// Encoder pins
#define ENCODER_1A 18 // Encoder A for Left Front Wheel
#define ENCODER_2A 19 // Encoder A for Left Rear Wheel
#define ENCODER_3A 20 // Encoder A for Right Front Wheel
#define ENCODER_4A 21 // Encoder A for Right Rear Wheel

#define ENCODER_1B 31 // Encoder B for Left Front Wheel
#define ENCODER_2B 33 // Encoder B for Left Rear Wheel
#define ENCODER_3B 35 // Encoder B for Right Front Wheel
#define ENCODER_4B 37 // Encoder B for Right Rear Wheel


extern volatile int encoder1_value;
extern volatile int encoder2_value;
extern volatile int encoder3_value;
extern volatile int encoder4_value;


// Global variables
extern volatile int posi;

// Function prototypes
void encoder1_isr();
void encoder2_isr();
void encoder3_isr();
void encoder4_isr();

#endif
