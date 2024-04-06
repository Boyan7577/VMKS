#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// Motor Control Joystick Pins
const int joystickX = A0;
const int joystickY = A1;

// Servo Control Joystick Pins
const int servoJoystickX = A2;
const int servoJoystickY = A3;

void setup() {
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joystickX);
  int yValue = analogRead(joystickY);

  int xValueServo = analogRead(servoJoystickX);

  // Create data packet
  int data[3] = {xValue, yValue, xValueServo};

  // Send data packet
  radio.write(&data, sizeof(data));

  // Print joystick readings to serial monitor
  Serial.print("Motor Control - X Value: ");
  Serial.print(xValue);
  Serial.print("\tY Value: ");
  Serial.println(yValue);
  
  Serial.print("Servo Control - X Value: ");
  Serial.print(xValueServo);

  delay(100); // Adjust delay as needed for communication stability
}
