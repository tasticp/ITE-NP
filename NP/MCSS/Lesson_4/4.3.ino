void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(3)==HIGH){
    Serial.print("Motion detected!");
  }
}