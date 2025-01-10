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
  int A2 = digitalRead(ENCODER_2A);
  int B2 = digitalRead(ENCODER_2B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A2 == HIGH) != (B2 == HIGH)) {
    encoder2_value++; //cw
  } else {
    encoder2_value--; //ccw
  }
}

void encoder3_isr() {
  int A3 = digitalRead(ENCODER_3A);
  int B3 = digitalRead(ENCODER_3B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A3 == HIGH) != (B3 == HIGH)) {
    encoder3_value++; //cw
  } else {
    encoder3_value--; //ccw
  }
}

void encoder4_isr() {
  int A4 = digitalRead(ENCODER_4A);
  int B4 = digitalRead(ENCODER_4B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A4 == HIGH) != (B4 == HIGH)) {
    encoder4_value++; //cw
  } else {
    encoder4_value--; //ccw
  }
}
