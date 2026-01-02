int LedA = 2; //A
int LedB = 3; //B
int LedC = 4; //C
int LedD = 5; //D
int LedE = 6; //E
int LedF = 7; //F
int LedG = 8; //G //pin10
int LedDP = 9; //DP
int POWER = 10; //5V

void setup() {
pinMode(LedA , OUTPUT);
pinMode(LedB , OUTPUT);
pinMode(LedC , OUTPUT);
pinMode(LedD , OUTPUT);
pinMode(LedE , OUTPUT);
pinMode(LedF , OUTPUT);
pinMode(LedG , OUTPUT);
pinMode(LedDP , OUTPUT);
pinMode(POWER , OUTPUT);
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(POWER,HIGH);
  zero();
  delay(500);
  oneDot();
  delay(500);
  two();
  delay(500);
  threeDot();
  delay(500);
  four();
  delay(500);
  fiveDot();
  delay(500);
  six();
  delay(500);
  sevenDot();
  delay(500);
  eight();
  delay(500);
  nineDot();
  delay(500);
}
void zero(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , LOW);//on
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , HIGH);
  digitalWrite(LedDP , HIGH);
}
void oneDot(){
  digitalWrite(LedA , HIGH);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , HIGH);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , HIGH);
  digitalWrite(LedG , HIGH);
  digitalWrite(LedDP , LOW);
}
void two(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , HIGH);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , LOW);
  digitalWrite(LedF , HIGH);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , HIGH);
}
void threeDot(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , HIGH);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , LOW);
}
void four(){
  digitalWrite(LedA , HIGH);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , HIGH);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , HIGH);
}
void fiveDot(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , HIGH);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , LOW);
}
void six(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , HIGH);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , LOW);
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , HIGH);
}
void sevenDot(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , HIGH);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , HIGH);
  digitalWrite(LedG , HIGH);
  digitalWrite(LedDP , LOW);
}
void eight(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , LOW);
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , HIGH);
}
void nineDot(){
  digitalWrite(LedA , LOW);
  digitalWrite(LedB , LOW);
  digitalWrite(LedC , LOW);
  digitalWrite(LedD , LOW);
  digitalWrite(LedE , HIGH);
  digitalWrite(LedF , LOW);
  digitalWrite(LedG , LOW);
  digitalWrite(LedDP , LOW);
}
