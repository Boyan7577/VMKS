#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// Motor A Pins
const int ENA_PIN = 9; // EN1 pin of L298N
const int IN1_PIN = 6; // IN1 pin of L298N
const int IN2_PIN = 5; // IN2 pin of L298N

// Motor B Pins
const int ENB_PIN = 10; // EN2 pin of L298N
const int IN3_PIN = 3; // IN3 pin of L298N
const int IN4_PIN = 4; // IN4 pin of L298N

// Current speed of motors
int currentSpeed = 80;

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int data[2];
    radio.read(&data, sizeof(data));

    int xValue = data[0];
    int yValue = data[1];

    int mappedYSpeed = map(yValue, 0, 1023, -currentSpeed, currentSpeed);
    int mappedXSpeed = map(xValue, 0, 1023, -currentSpeed, currentSpeed);

    int motorSpeedA = mappedYSpeed;
    int motorSpeedB = mappedYSpeed;

    if (xValue < 400) {
      motorSpeedA = 0;
      motorSpeedB += mappedXSpeed;
    } else if (xValue > 600) {
      motorSpeedB = 0;
      motorSpeedA -= mappedXSpeed;
    }

    analogWrite(ENA_PIN, abs(motorSpeedA));
    analogWrite(ENB_PIN, abs(motorSpeedB));

    if (motorSpeedA > 0) {
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
    } else {
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
    }

    if (motorSpeedB > 0) {
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, LOW);
    } else {
      digitalWrite(IN3_PIN, LOW);
      digitalWrite(IN4_PIN, HIGH);
    }
  }
}
