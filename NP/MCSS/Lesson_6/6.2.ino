char SerialRx = 0;
void setup(){
Serial.begin(9600); //initialize baud rate at 9600bps
pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
}
void loop(){
    if (Serial.available() > 0) { //incoming data?
    SerialRx = Serial.read(); //receive data and store in SerialRx
        if(SerialRx == '0'){ //if receive data is ‘0’
            digitalWrite(12, LOW); //turn off LED
            Serial.println("green off, no.0");
        }
        else if(SerialRx == '1'){ ///if receive data is ‘1’
            digitalWrite(12, HIGH); //turn on LED
            Serial.println("green on, no.1");
        }
        else if(SerialRx == '2'){ ///if receive data is ‘3’
            digitalWrite(11, LOW); //turn off LED
            Serial.println("red off, no.2");
        }
        else if(SerialRx == '3'){
            digitalWrite(11, HIGH); //turn on LED
            Serial.println("red on, no.3");
        }
    }
}
