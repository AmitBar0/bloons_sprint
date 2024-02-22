#include <Servo.h>

const int STOP = 1500;
const int CW = center - 500;
const int CCW = center + 500;

Servo right;
Servo left;

String inByte;


void setup() {
  Serial.begin(9600);
  right.attach(9);
  left.attach(10);
}

void loop() {
  if (Serial.available()) {
    inByte = Serial.readStringUntil('\n'); // read data until newline
    // say what you got:
    Serial.print("received: ");
    Serial.print(inByte);
    if(input == 'r'){ // go right
      Serial.println(" going right ");
      left.writeMicroseconds(CW);
      right.writeMicroseconds(CCW);
    }else if(input == 'l'){ // go left
      Serial.println(" going left ");
      left.writeMicroseconds(CCW);
      right.writeMicroseconds(CW);
    }else if (input == 'f'){ // go forward
      Serial.println(" going forward ");
      left.writeMicroseconds(CW);
      right.writeMicroseconds(CW);
    }else if(input == 'b'){ // go backwards
      left.writeMicroseconds(CCW);
      right.writeMicroseconds(CCW);
    }else if(input == 's'){ // stop
      Serial.println(" sent Stopped ");
      left.writeMicroseconds(STOP);
      right.writeMicroseconds(STOP);
    }
  }
}
