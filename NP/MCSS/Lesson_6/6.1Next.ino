int two = 2;
int twelve =12;
bool buttonStatus;
int ButtonWas;
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,  INPUT_PULLUP);
pinMode(12, OUTPUT);
int ButtonWas = LOW;/////////HIGH is it was and is pressed
digitalWrite(twelve,LOW);
}

void loop() {
// put your main code here, to run repeatedly:
    if((ButtonWas == HIGH)&&(digitalRead(two) == HIGH)){
        Serial.println("Buttonstatus: Released ");
        digitalWrite(twelve,LOW);
        ButtonWas = LOW;
    }
    else if((ButtonWas == LOW)&&(digitalRead(two) == LOW)){
        Serial.println("Buttonstatus: Pressed ");
        digitalWrite(twelve,HIGH);
        ButtonWas = HIGH;
    }
}
