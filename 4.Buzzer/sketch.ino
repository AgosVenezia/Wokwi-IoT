int buzzer = 4;

void setup() {
  
  pinMode(buzzer, OUTPUT);

}

void loop() {
  
  tone(buzzer, 800);
  delay(500);
  noTone(buzzer);
  delay(500);
  
}
