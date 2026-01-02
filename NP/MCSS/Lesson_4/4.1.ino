void setup() {
    // put your setup code here, to run once:
    pinMode(11,INPUT);
    pinMode(12,OUTPUT);
}
void loop() {
    // put your main code here, to run repeatedly:
    if(digitalRead(11)==LOW){
    digitalWrite(12,LOW);
    }
}