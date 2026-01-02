int val=0;
void setup() {
  // put your setup code here, to run once:
  //pinMode(11,INPUT);
    pinMode(2,INPUT);
    pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    val=digitalRead(2);
    if (val==LOW){
    digitalWrite(13,LOW);
    }
    else{
    digitalWrite(13,HIGH);
    }
}