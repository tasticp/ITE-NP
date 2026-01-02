int Led1 = 2;

void setup() {
  pinMode(Led1 , OUTPUT);
  digitalWrite(Led1,HIGH);
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Led1 , LOW);
  delay(1000);
  digitalWrite(Led1 , HIGH);
  delay(1000);
}