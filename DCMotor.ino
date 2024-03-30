
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N

const int ENB_PIN = 10; // the Arduino pin connected to the EN2 pin L298N for Motor B
const int IN3_PIN = 3; // the Arduino pin connected to the IN3 pin L298N for Motor B
const int IN4_PIN = 4; // the Arduino pin connected to the IN4 pin L298N for Motor B

void setup() {
  // initialize digital pins as outputs.
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
}

void loop() {
  digitalWrite(IN1_PIN, HIGH); // Control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW);  // Control motor A spins clockwise

  digitalWrite(IN3_PIN, HIGH); // Control Motor B (clockwise)
  digitalWrite(IN4_PIN, LOW);  // Control Motor B (clockwise)

  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(ENA_PIN, speed); // control the speed
    analogWrite(ENB_PIN, speed); // Control speed of Motor B
    delay(10);
  }

  delay(1000); // rotate at maximum speed 1 seconds in in clockwise direction

  // change direction
  digitalWrite(IN1_PIN, LOW);   // control Motor A spins anti-clockwise
  digitalWrite(IN2_PIN, HIGH);  // control Motor A spins anti-clockwise
  
  digitalWrite(IN3_PIN, LOW);   // Control Motor B (anti-clockwise)
  digitalWrite(IN4_PIN, HIGH);  // Control Motor B (anti-clockwise)

  delay(1000); // rotate at maximum speed 1 seconds in in anti-clockwise direction

  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(ENA_PIN, speed);  // control the speed
    analogWrite(ENB_PIN, speed); // Control speed of Motor B
    delay(10);
  }

  delay(1000); // stop motor 1 second
}
