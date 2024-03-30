// Motor A Pins
const int ENA_PIN = 9; // EN1 pin of L298N
const int IN1_PIN = 6; // IN1 pin of L298N
const int IN2_PIN = 5; // IN2 pin of L298N

// Motor B Pins
const int ENB_PIN = 10; // EN2 pin of L298N
const int IN3_PIN = 3; // IN3 pin of L298N
const int IN4_PIN = 4; // IN4 pin of L298N

// Joystick Pins
const int joystickX = A0;
const int joystickY = A1;

// Current speed of motors
int currentSpeed = 80;

void setup() {
  // Set motor pins as outputs
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
}

void loop() {
  // Read joystick values
  int xValue = analogRead(joystickX);
  int yValue = analogRead(joystickY);
  
  // Map joystick Y value to motor speed
  int mappedYSpeed = map(yValue, 0, 1023, -currentSpeed, currentSpeed);
  
  // Map joystick X value to motor speed
  int mappedXSpeed = map(xValue, 0, 1023, -currentSpeed, currentSpeed);

  // Calculate individual motor speeds based on joystick position
  int motorSpeedA = mappedYSpeed;
  int motorSpeedB = mappedYSpeed;

  // Adjust individual motor speeds based on joystick X position
  if (xValue < 400) {
    motorSpeedA = 0; // Stop motor A
    motorSpeedB += mappedXSpeed; // Motor B rotates faster
  } else if (xValue > 600) {
    motorSpeedB = 0; // Stop motor B
    motorSpeedA -= mappedXSpeed; // Motor A rotates faster
  }

  // Set motor speed
  analogWrite(ENA_PIN, abs(motorSpeedA));
  analogWrite(ENB_PIN, abs(motorSpeedB));

  // Set direction for Motor A based on motorSpeedA
  if (motorSpeedA > 0) {
    digitalWrite(IN1_PIN, HIGH); // Forward direction
    digitalWrite(IN2_PIN, LOW);
  } else {
    digitalWrite(IN1_PIN, LOW);  // Backward direction
    digitalWrite(IN2_PIN, HIGH);
  }

  // Set direction for Motor B based on motorSpeedB
  if (motorSpeedB > 0) {
    digitalWrite(IN3_PIN, HIGH); // Forward direction
    digitalWrite(IN4_PIN, LOW);
  } else {
    digitalWrite(IN3_PIN, LOW);  // Backward direction
    digitalWrite(IN4_PIN, HIGH);
  }
}
