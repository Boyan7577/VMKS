#define RELAY_PIN 12 // Pin connected to the relay module

void setup() {
  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as an output
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); // Activate the relay
  delay(2000); // Wait for 2 seconds
  
  digitalWrite(RELAY_PIN, LOW); // Deactivate the relay
  delay(2000); // Wait for another 2 seconds
}
