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
    if(i==1){
        for (int j=3 ; j<330 ; j+=3 ){
            if(j != 9){
            Serial.print("execute loop() number ");
            Serial.println(j);
            }
            if(j==9){
            j = j+3;
            Serial.print("execute loop() number ");
            Serial.println(j);
            }
    }
    i++;
}