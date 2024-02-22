#include <Servo.h>

const int STOP = 1500;
const int CW = STOP - 500;
const int CCW = STOP + 500;
int pos = 0;
Servo right;
Servo left;

String inByte;


void setup() {
  Serial.begin(9600);
  right.attach(A0);
  left.attach(A1);
  Serial.setTimeout(10);
}

void loop() {
  if (Serial.available()) {
    inByte = Serial.readStringUntil('\n'); // read data until newline
    // say what you got:
    Serial.println("received: ");
    pos = inByte.toInt();
    if(pos == 0){ // go right
      Serial.println(" going right ");
      left.writeMicroseconds(CCW);
      right.writeMicroseconds(CCW);
    }else if(pos == 1){ // go left
      Serial.println(" going left ");
      left.writeMicroseconds(CW);
      right.writeMicroseconds(CW);
    }else if (pos == 2){ // go forward
      Serial.println(" going forward ");
      left.writeMicroseconds(CCW);
      right.writeMicroseconds(CW);
    }else if(pos == 3){ // go backwards
      left.writeMicroseconds(CW);
      right.writeMicroseconds(CCW);
    }else if(pos == 4){ // stop
      Serial.println(" sent Stopped ");
      left.writeMicroseconds(STOP);
      right.writeMicroseconds(STOP);
    }
  }
  Serial.flush();
}
