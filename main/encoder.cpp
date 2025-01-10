#include "encoder.h"

volatile int encoder1_value = 0;
volatile int encoder2_value = 0;
volatile int encoder3_value = 0;
volatile int encoder4_value = 0;

void encoder1_isr() {
  int A = digitalRead(ENCODER_1A);
  int B = digitalRead(ENCODER_1B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A == HIGH) != (B == HIGH)) {
    encoder1_value++; //cw
  } else {
    encoder1_value--; //ccw
  }
}

void encoder2_isr() {
  if (digitalRead(ENCODER_2B) == 0)
    encoder2_value++;
  else 
    encoder2_value--;
}

void encoder3_isr() {
  if (digitalRead(ENCODER_3B) == 0)
    encoder3_value++;
  else 
    encoder3_value--;
}

void encoder4_isr() {
  if (digitalRead(ENCODER_4B) == 0)
    encoder4_value++;
  else 
    encoder4_value--;
}
