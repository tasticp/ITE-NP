int Led1 = 2;
int Led2 = 3;
void setup() {
    pinMode(Led1 , OUTPUT);
    pinMode(Led2 , OUTPUT);
    digitalWrite(Led1,HIGH);
    digitalWrite(Led2,HIGH);
    // put your setup code here, to run once:
}
void loop(){
    digitalWrite(Led1,LOW);
    digitalWrite(Led2,HIGH);
    delay(1000);
    digitalWrite(Led1,HIGH);
    digitalWrite(Led2,LOW);
    delay(1000);
}