int i;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    for (int j=1 ; j<=100 ; j=j+3){
        Serial.println(j);
        delay(10);
    }
    delay(10);
        for (int j=1 ; j<=100 ; j=j-3){
        Serial.println(j); 
        delay(10);
        }
    }
}