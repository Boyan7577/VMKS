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

// Water Pump Control Joystick Pin
const int pumpControlPin = 2; // Connect to the second joystick pin

bool pumpOn = false; // Variable to track pump state

void setup() {
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.begin(9600);
  pinMode(pumpControlPin, INPUT_PULLUP); // Set the pin to input with internal pull-up resistor
}

void loop() {
  int xValue = analogRead(joystickX);
  int yValue = analogRead(joystickY);

  int xValueServo = analogRead(servoJoystickX);

  // Read the state of the pump control joystick
  bool pumpButtonPressed = digitalRead(pumpControlPin) == LOW;

  // Create data packet
  int data[4] = {xValue, yValue, xValueServo, pumpButtonPressed};

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
