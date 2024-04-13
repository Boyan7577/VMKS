#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

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

// Buzzer Pin
const int BUZZER_PIN = 11;

// LED Pins
const int LED1_PIN = 45;
const int LED2_PIN = 36;
const int LED3_PIN = 43;
const int LED4_PIN = 38;
const int LED5_PIN = 40;

// Water Pump Relay Pin
const int PUMP_RELAY_PIN = 12; // Connect to the relay control pin

// Current speed of motors
int currentSpeed = 80;

// Flame sensor Pin
const int FLAME_SENSOR_PIN = A0;

// Servo motor pin
const int SERVO_PIN = 2;

Servo servo;

bool pumpOn = false;
bool fireDetected = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);

  pinMode(FLAME_SENSOR_PIN, INPUT);

   pinMode(PUMP_RELAY_PIN, OUTPUT); // Set the pump relay pin as output

  servo.attach(SERVO_PIN);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  // Turn on LED1 and LED3
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
}

void loop() 
{
  if (radio.available()) {
    int data[4];
    radio.read(&data, sizeof(data));

    int xValue = data[0];
    int yValue = data[1];
    int xValueServo = data[2];
    bool pumpButtonPressed = data[3];

    // Reverse the joystick values
    xValue = 1023 - xValue;
    yValue = 1023 - yValue;

    // Print joystick readings to serial monitor
    Serial.print("Motor Control - X Value: ");
    Serial.println(xValue);
    Serial.print("\tY Value: ");
    Serial.println(yValue);
    
    Serial.print("Servo Control - X Value: ");
    Serial.println(xValueServo);

    int mappedYSpeed = map(yValue, 0, 1023, -currentSpeed, currentSpeed);
    int mappedXSpeed = map(xValue, 0, 1023, -currentSpeed, currentSpeed);
    int mappedXServo = map(xValueServo, 0, 1023, 45, 135); // Map x-axis value to servo angle
    servo.write(mappedXServo);

    int motorSpeedA = mappedYSpeed;
    int motorSpeedB = mappedYSpeed;

    if (xValue < 400) {
      motorSpeedA = 0;
      motorSpeedB += mappedXSpeed;
    } 
    else if (xValue > 600) 
    {
      motorSpeedB = 0;
      motorSpeedA -= mappedXSpeed;
      
    }

    analogWrite(ENA_PIN, abs(motorSpeedA));
    analogWrite(ENB_PIN, abs(motorSpeedB));

    if (motorSpeedA > 0) 
    {
      digitalWrite(IN1_PIN, HIGH); // Forward direction
      digitalWrite(IN2_PIN, LOW);
      // Turn on LED4 and LED5 when moving backward
      digitalWrite(LED4_PIN, HIGH);
      digitalWrite(LED5_PIN, HIGH);
    }
     
    else 
    {
      digitalWrite(IN1_PIN, LOW); // Backward direction
      digitalWrite(IN2_PIN, HIGH);

      digitalWrite(LED4_PIN, LOW);
      digitalWrite(LED5_PIN, LOW);
    }

    if (motorSpeedB > 0) 
    {
      digitalWrite(IN3_PIN, HIGH); // Forward direction
      digitalWrite(IN4_PIN, LOW);

      digitalWrite(LED4_PIN, HIGH);
      digitalWrite(LED5_PIN, HIGH);
    } 
    else 
    {
      digitalWrite(IN3_PIN, LOW); // Backward direction
      digitalWrite(IN4_PIN, HIGH);

      digitalWrite(LED4_PIN, LOW);
      digitalWrite(LED5_PIN, LOW);
    }

  // Control the water pump relay
    if (pumpButtonPressed) {
      if (!pumpOn) {
        digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the water pump
        pumpOn = true;
      } else {
        digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the water pump
        pumpOn = false;
      }
    }
  }

  // Check flame sensor
  int flameSensorValue = analogRead(FLAME_SENSOR_PIN);
  if (flameSensorValue <= 500) 
  {
    // Fire detected
    digitalWrite(LED2_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // Make a constant sound
    fireDetected = true;
  } 
  else if (fireDetected) 
  {
    // Fire extinguished
    digitalWrite(LED2_PIN, LOW);
    noTone(BUZZER_PIN);
    fireDetected = false;
  }
}
