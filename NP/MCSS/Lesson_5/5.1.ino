int sensorPin = 0;
float voltagecalc;
void setup() {
  Serial.begin(9600);
}
void loop() {
  int reading = analogRead(sensorPin);  //getting reading from the TMP36
  Serial.print("Digital value:");
  Serial.print(reading);
  voltagecalc = reading / 1024.0 * 5;
  Serial.print(" Voltage:");
  Serial.println(voltagecalc);
  delay(100);
  if (voltagecalc >= 4 && voltagecalc <= 5) {

    digitalWrite(13, LOW);
    delay(2000);
    digitalWrite(13, HIGH);
    delay(2000);
  }


  else if (voltagecalc >= 3 && voltagecalc < 4) {
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
  } else if (voltagecalc >= 2 && voltagecalc < 3) {
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
  }

  else if (voltagecalc >= 1 && voltagecalc < 2) {
    digitalWrite(13, LOW);
    delay(250);
    digitalWrite(13, HIGH);
    delay(250);
  } else if (voltagecalc >= 0 && voltagecalc < 1) {
    digitalWrite(13, LOW);
    delay(125);
    digitalWrite(13, HIGH);
    delay(125);
  }
}
