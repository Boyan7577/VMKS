const int buzzer = 11;

void setup()
{
  pinMode(buzzer, OUTPUT);
}
void loop()
{
  tone(buzzer, 1000); // 1KHz
  delay(1000);       
  noTone(buzzer);     // Stop
  delay(1000);      
}   
