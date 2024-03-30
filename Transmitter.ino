#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

// Joystick Pins
const int joystickX = A0;
const int joystickY = A1;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  //radio.stopListening();
}

void loop() {
  int xValue = analogRead(joystickX);
  int yValue = analogRead(joystickY);

  // Create data packet
  int data[2] = {xValue, yValue};

  // Send data packet
  radio.write(&data, sizeof(data));

  // Print joystick readings to serial monitor
  Serial.print("X Value: ");
  Serial.print(xValue);
  Serial.print("\tY Value: ");
  Serial.println(yValue);

  delay(50); // Adjust delay as needed for communication stability
}
