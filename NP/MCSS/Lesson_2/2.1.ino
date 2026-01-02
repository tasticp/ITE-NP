int i;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    i = 0;
    Serial.println("execute setup");
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(10);
    Serial.print("execute loop() number ");
    Serial.println(i++);
}