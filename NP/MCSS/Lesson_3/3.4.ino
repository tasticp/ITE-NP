int motor = 2;

void setup() {
  pinMode(motor , OUTPUT);
  digitalWrite(motor,HIGH);
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor , LOW);
  delay(5000);
  digitalWrite(motor , HIGH);
  delay(5000);
}