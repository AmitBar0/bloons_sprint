#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#define CE_PIN 7
#define CSN_PIN 8
#define INTERVAL_MS_TRANSMISSION 250

#define RIGHT_PIN A0
#define LEFT_PIN A1

// both X values
int rightValue = 0;
int leftValue = 0;

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

//NRF24L01 buffer limit is 32 bytes (max struct size)
struct payload {
   int rightValue;
   int leftValue;
};
payload payload;
void setup()
{
    Serial.begin(115200);
    radio.begin();
    //Append ACK packet from the receiving radio back to the transmitting radio
    radio.setAutoAck(false); //(true|false)
    //Set the transmission datarate
    radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
    //Greater level = more consumption = longer distance
    radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
    //Default value is the maximum 32 bytes
    radio.setPayloadSize(sizeof(payload));
    //Act as transmitter
    radio.openWritingPipe(address);
    radio.stopListening();
}
void loop()
{
    rightValue = analogRead(RIGHT_PIN);
    leftValue = analogRead(LEFT_PIN);

    Serial.print("right = ")
    Serial.print(rightValue);
    Serial.print("left = ")
    Serial.println(leftValue);

    payload.rightValue = rightValue;
    payload.leftValue = leftValue;

    radio.write(&payload, sizeof(payload));
    Serial.print("Data1:");
    Serial.println(payload.rightValue);
    Serial.print("Data2:");
    Serial.println(payload.leftValue);
    Serial.println("Sent");
    delay(INTERVAL_MS_TRANSMISSION);
}
