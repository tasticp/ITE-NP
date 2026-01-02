void setup() {
    // put your setup code here, to run once:
    pinMode( LED_BUILTIN ,OUTPUT);
}
void loop() {
    digitalWrite(LED_BUILTIN,LOW);
    delay(2000);
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
}