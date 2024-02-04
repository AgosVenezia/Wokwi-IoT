int led = 16;

void setup() {
  
  pinMode(led, OUTPUT);

}

void loop() {
  
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500); // this speeds up the simulation

}
