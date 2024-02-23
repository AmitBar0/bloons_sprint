#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "Servo.h"
#define CE_PIN 7
#define CSN_PIN 8
#define INTERVAL_MS_SIGNAL_LOST 1000
#define INTERVAL_MS_SIGNAL_RETRY 250

#define POS_JOYSTICK_THRESHOLD 600
#define NEG_JOYSTICK_THRESHOLD 400

const int STOP = 1500;
const int CW = STOP - 500;
const int CCW = STOP + 500;

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";
//NRF24L01 buffer limit is 32 bytes (max struct size)
struct payload {
   int rightValue;
   int leftValue;
};
payload payload;
unsigned long lastSignalMillis = 0;
Servo left;
Servo right;
void setup()
{
   Serial.begin(115200);
   radio.begin();
   //Append ACK packet from the receiving radio back to the transmitting radio
   radio.setAutoAck(false); //(true|false)
   //Set the transmission datarate
   radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
   //Greater level = more consumption = longer distance
   radio.setPALevel(RF24_PA_MIN); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
   //Default value is the maximum 32 bytes1
   radio.setPayloadSize(sizeof(payload));
   //Act as receiver
   radio.openReadingPipe(0, address);
   radio.startListening();
}
void loop()
{
    unsigned long currentMillis = millis();
    if (radio.available() > 0) {
     radio.read(&payload, sizeof(payload));
     Serial.println("Received");
     Serial.print("Data1:");
     Serial.println(payload.rightValue);
     Serial.print("Data2:");
     Serial.println(payload.leftValue);


     // move wheels
    if(payload.leftValue > POS_JOYSTICK_THRESHOLD){
        Serial.println(" left going forward ");
        left.writeMicroseconds(CW);
    }else if(payload.leftValue < NEG_JOYSTICK_THRESHOLD){
        Serial.println(" left going backwards ");
        left.writeMicroseconds(CCW);
    }else {
        Serial.println(" left stopped ");
        left.writeMicroseconds(STOP);
    }

    if(payload.rightValue > POS_JOYSTICK_THRESHOLD){
        Serial.println(" right going forward ");
        right.writeMicroseconds(CCW);
    }else if(payload.rightValue < NEG_JOYSTICK_THRESHOLD){
        Serial.println(" right going backwards ");
        right.writeMicroseconds(CW);
    }else {
        Serial.println(" right stopped ");
        right.writeMicroseconds(STOP);
    }


     lastSignalMillis = currentMillis;
    }
    if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST) {
     lostConnection();
    }
}
void lostConnection()
{
   Serial.println("We have lost connection, preventing unwanted behavior");
   delay(INTERVAL_MS_SIGNAL_RETRY);
}