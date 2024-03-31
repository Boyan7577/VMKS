const int flamepin=A2;
const int buzpin=11;
const int threshold=200;// sets threshold value for flame sensor
int flamesensvalue=0; // initialize flamesensor reading

void setup() 
{
  Serial.begin(9600);
  pinMode(flamepin,INPUT);
  pinMode(buzpin,OUTPUT);
}

void loop() {
  flamesensvalue=analogRead(flamepin); // reads analog data from flame sensor
  if (flamesensvalue<=threshold) 
  { // compares reading from flame sensor with the threshold value
    tone(buzpin,100);
    delay(1000); //stops program for 1 second
  }
  else
  {
    noTone(buzpin);
  }
}
