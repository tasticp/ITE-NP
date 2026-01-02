/*Question
  Design an Arduino-based circuit with two LEDs, two push buttons, and a potentiometer. The system should work as follows:

  When Button 1 is pressed, the brightness of the Red LED is controlled by the potentiometer's position.

  When Button 2 is pressed, the brightness of the Green LED is controlled by the potentiometer's position.

  If neither button is pressed, both LEDs should be off.

  Implement current sinking configuration for the LEDs (LEDs turn ON when the microcontroller pin is LOW).

  Circuit Schematic Explanation
  Potentiometer: Connected as a voltage divider between 5V and GND, with its wiper connected to an analog input pin (e.g., A0).

  Red LED: Connected with its cathode to Arduino digital PWM pin (e.g., pin 9) and anode connected through a resistor (~220Ω) to 5V (current sinking).

  Green LED: Connected similarly with cathode to PWM pin (e.g., pin 10), anode via resistor to 5V.

  Button 1 & Button 2: Each connected between a digital input pin (e.g., pin 2 and pin 3) and 5V, with external pull-down resistors (10kΩ) to GND to read LOW when unpressed and HIGH when pressed.

  Arduino Code
*/
const int potPin = A0;        // Analog pin for potentiometer
const int redLedPin = 9;      // PWM pin for red LED (cathode side)
const int greenLedPin = 10;   // PWM pin for green LED (cathode side)
const int button1Pin = 2;     // Digital input for Button 1
const int button2Pin = 3;     // Digital input for Button 2

void setup() {
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(button1Pin, INPUT);  // with external pull-down resistor
    pinMode(button2Pin, INPUT);  // with external pull-down resistor

  // Turn both LEDs off initially (HIGH = off in sinking config)
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
}

void loop() {
    int potValue = analogRead(potPin);  // Read 0-1023 from potentiometer

  // Map pot value to PWM range 0-255
    int brightness = map(potValue, 0, 1023, 0, 255);

    bool button1Pressed = (digitalRead(button1Pin) == HIGH);
    bool button2Pressed = (digitalRead(button2Pin) == HIGH);

    if (button1Pressed && !button2Pressed) {
    // Control Red LED brightness, Green LED off
    analogWrite(redLedPin, 255 - brightness);    // inverted because LOW = ON
    digitalWrite(greenLedPin, HIGH);              // off
    }
    else if (button2Pressed && !button1Pressed) {
    // Control Green LED brightness, Red LED off
    analogWrite(greenLedPin, 255 - brightness);  // inverted for sinking
    digitalWrite(redLedPin, HIGH);                // off
    }
    else {
    // If no button or both pressed, turn both LEDs off
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    }
}
/*Summary
When Button 1 is pressed alone, the red LED's brightness varies based on the potentiometer.

When Button 2 is pressed alone, the green LED's brightness varies.

When both buttons or no button is pressed, LEDs are off.

LEDs are wired in a current sinking configuration, so PWM values are inverted.

Buttons are read as HIGH when pressed via external pull - down resistors.

If you want, I can provide a simple hand - drawn schematic image or a detailed wiring diagram with component values. Would you like that ?
*/
