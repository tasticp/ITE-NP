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
    H();
    delay(1000);
    L();
    delay(1000);
}
void H(){
    digitalWrite(LedA , HIGH);
    digitalWrite(LedB , LOW);
    digitalWrite(LedC , LOW);
    digitalWrite(LedD , HIGH);
    digitalWrite(LedE , LOW);//on
    digitalWrite(LedF , LOW);
    digitalWrite(LedG , LOW);
    digitalWrite(LedDP , HIGH);
}
void L(){
    digitalWrite(LedA , HIGH);
    digitalWrite(LedB , HIGH);
    digitalWrite(LedC , HIGH);
    digitalWrite(LedD , LOW);
    digitalWrite(LedE , LOW);
    digitalWrite(LedF , LOW);
    digitalWrite(LedG , HIGH);
    digitalWrite(LedDP , HIGH);
}
