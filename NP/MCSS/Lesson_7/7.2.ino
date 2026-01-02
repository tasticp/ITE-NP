void setup() {
    // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    //Serial.begin(115200);
    Serial.begin(9600);
}
void loop() {
    analogWrite(3, 0);
    Serial.println("0%");
    delay(3000);
    analogWrite(3, 64);  //25% 63.74
    Serial.println("25%");
    delay(3000);
    analogWrite(3, 128);  //50% on127.5
    Serial.println("50%");
    delay(3000);
    analogWrite(3, 191);  //75% on  .25
    Serial.println("75%");
    delay(3000);
    analogWrite(3, 255);  //full on
    Serial.println("100%");
    delay(3000);
}