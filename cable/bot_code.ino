#include <Servo.h>

const int STOP = 1500;
const int CW = STOP - 500;
const int CCW = STOP + 500;
int pos = 0;
Servo right;
Servo left;

const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

String inByte;


void setup() {
  Serial.begin(9600);
  right.attach(A0);
  left.attach(A1);
  Serial.setTimeout(10);

  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
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

  // digitalWrite(trigPin, LOW);  
	// delayMicroseconds(2);  
	// digitalWrite(trigPin, HIGH);  
	// delayMicroseconds(10);  
	// digitalWrite(trigPin, LOW);  

  // duration = pulseIn(echoPin, HIGH);
  // distance = (duration*.0343)/2;
  // Serial.prnit("beep ");
  // Serial.println(distance);
  // delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

