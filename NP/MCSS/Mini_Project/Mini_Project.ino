                                                  //how does cher see the monitor ?

/*================================================================================
; GLOBAL VARIABLES SECTION
================================================================================*/

// SERVO MOTOR DECLARATIONS
/*==============================================================================*/
#include <Servo.h>
Servo CumIn;                                // Servo for incoming cars (Pin D5)
Servo PullOut;                              // Servo for outgoing cars (Pin D6)
/*==============================================================================*/

// ANALOG PIN ASSIGNMENTS
/*==============================================================================*/
int CumInPeg = A0;                          // Analog sensor for incoming cars
int PullOutPeg = A1;                        // Analog sensor for outgoing cars
int Car1 = A2;                              // Analog sensor for car 1 detection
int Car1LED = A3;                           // LED indicator for car 1 status
/*==============================================================================*/

// DIGITAL PIN ASSIGNMENTS
/*==============================================================================*/
int LedA = 2;                               // Seven-segment display segment A
int LedB = 3;                               // Seven-segment display segment B
int LedC = 4;                               // Seven-segment display segment C
int LedD = A4;                              // Seven-segment display segment D
int LedE = A5;                              // Seven-segment display segment E
int LedF = 7;                               // Seven-segment display segment F
int LedG = 8;                               // Seven-segment display segment G
int LedDP = 9;                              // Seven-segment display decimal point
int POWER = 10;                             // Seven-segment display power supply
int ButtPlug = 11;                          // Help request button (INPUT_PULLUP)
int Ass = 12;                               // Help response button (INPUT_PULLUP)
int HelpLED = 13;                           // Help indicator LED
/*==============================================================================*/

// SYSTEM STATE VARIABLES
/*==============================================================================*/
bool isOpenToTryNewThings = true;          // Parking lot availability flag
int InsideUWU = 0;                         // Current number of cars inside
int CumInPegging = LOW;                    // Incoming car sensor state
int PullOutPegging = LOW;                  // Outgoing car sensor state    
int Car1Pegging = LOW;                     // Car 1 sensor state
int AssStatus = HIGH;                      // Help response button state
int buttStatus = HIGH;                     // Help request button state
int in = HIGH;                             // General input state variable
int Step = 0;                              // Debug step counter for troubleshooting
/*==============================================================================*/


/*==============================================================================*/
// SETUP FUNCTION - INITIALIZATION ROUTINE
/*==============================================================================*/
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);                                                    // Start Serial Monitor

  // Attach servo motors to their respective pins
  CumIn.attach(5);                                                       // Attach incoming gate servo to pin 5
  // CumIn.write(0);                                                     // Set servo to closed position (commented out)
  PullOut.attach(6);                                                     // Attach outgoing gate servo to pin 6
  // PullOut.write(0);                                                   ; Set servo to closed position (commented out)

  // CONFIGURE SEVEN-SEGMENT DISPLAY PINS
  /*==============================================================================*/
  pinMode(LedA , OUTPUT);                                                // Configure segment A as output
  pinMode(LedB , OUTPUT);                                                // Configure segment B as output
  pinMode(LedC , OUTPUT);                                                // Configure segment C as output
  pinMode(LedD , OUTPUT);                                                // Configure segment D as output
  pinMode(LedE , OUTPUT);                                                // Configure segment E as output
  pinMode(LedF , OUTPUT);                                                // Configure segment F as output
  pinMode(LedG , OUTPUT);                                                // Configure segment G as output
  pinMode(LedDP , OUTPUT);                                               // Configure decimal point as output
  pinMode(POWER , OUTPUT);                                               // Configure power pin as output
  /*==============================================================================*/

  // CONFIGURE CAR INDICATOR LED
  /*==============================================================================*/
  pinMode(Car1LED, OUTPUT);                                              // Configure Car1 LED as output
  /*==============================================================================*/

  // CONFIGURE INPUT BUTTONS WITH INTERNAL PULLUP RESISTORS
  /*==============================================================================*/
  pinMode(Ass, INPUT_PULLUP);                                            // Configure help response button
  pinMode(ButtPlug, INPUT_PULLUP);                                       // Configure help request button
  /*==============================================================================*/

  // INITIALIZE LED STATES
  /*==============================================================================*/
  digitalWrite(Car1LED, LOW);                                            // Turn off Car1 LED initially
  /*==============================================================================*/
}
/*==============================================================================*/

/*==============================================================================*/
// MAIN LOOP - SYSTEM CONTROL ROUTINE
/*==============================================================================*/
void loop() {
  INSIDEUWU();                                                // Check current car count inside
  IsFull();                                                   // Process incoming cars if space available
  delay(100);                                                 // 100ms delay for system stability
  INSIDEUWU();                                                // Re-check car count after processing
  PullOutGame();                                              // Process outgoing cars if any present
  delay(100);                                                 // 100ms delay for system stability
  IsCarHere();                                                // Check Car1 sensor for vehicle detection
  delay(50);                                                  // 50ms delay for sensor reading stability
}
/*==============================================================================*/

/*==============================================================================*/
// INCOMING CAR PROCESSING FUNCTION
/*==============================================================================*/
void Creampie() {                    // Process incoming cars when space is available
  //Step = 100; step();                // Set debug step to 100
  IsHelpNeeded();                    // Check for help requests
  
  // Read incoming car sensor
  int SomeoneWantsToCumIn = analogRead(CumInPeg);
  
  // Check if sensor detects a car (threshold > 500)
  if (SomeoneWantsToCumIn > 500) {
      Serial.print("Someone Wants To Cum In: ");
      Serial.println(SomeoneWantsToCumIn);
      //Step = 101; step();            // Set debug step to 101
      
      // GATE OPERATION SEQUENCE
      /*==============================================================================*/
      CumIn.write(90);               // Open incoming gate (90 degrees)
      delay(2000);                   // Hold gate open for 2 seconds
      CumIn.write(0);                // Close incoming gate (0 degrees)
      /*==============================================================================*/
      
      // UPDATE CAR COUNT
      /*==============================================================================*/
      InsideUWU = InsideUWU + 1;     // Increment internal car counter
      Serial.print("Cars inside: ");
      Serial.println(InsideUWU);
      /*==============================================================================*/
      
      IsHelpNeeded();                // Check for help requests after operation
      //Step = 102; step();            // Set debug step to 102
  }
  
  SevenSeg();                        // Update seven-segment display
  IsHelpNeeded();                    // Final help check
}
/*==============================================================================*/

/*==============================================================================*/
// OUTGOING CAR PROCESSING FUNCTION
/*==============================================================================*/
void PullOutGame() {              // Process outgoing cars when any are present

  //Step = 200; step();             // Set debug step to 200
  IsHelpNeeded();                 // Check for help requests

  // Read outgoing car sensor
  int SomeoneAfraidOfCommitment = analogRead(PullOutPeg);
  
  // Check if sensor detects a car (threshold > 500)
  if (SomeoneAfraidOfCommitment > 500) {
    Serial.print("Someone Wants To Pull Out: ");
    Serial.println(SomeoneAfraidOfCommitment);
    //Step = 201; step();           // Set debug step to 201

    // Check if there are cars inside to process
    if (InsideUWU > 0) {
      //Step = 202; step();         // Set debug step to 202
      
      // GATE OPERATION SEQUENCE
      /*==============================================================================*/
      PullOut.write(90);          // Open outgoing gate (90 degrees)
      delay(2000);                // Hold gate open for 2 seconds
      PullOut.write(0);           // Close outgoing gate (0 degrees)
      /*==============================================================================*/
      
      // UPDATE CAR COUNT
      /*==============================================================================*/
      InsideUWU--;                // Decrement internal car counter
      /*==============================================================================*/
      
      // Exit function after successful operation
      return;
    }

    // ERROR HANDLING - UNBALANCED STATE
    /*==============================================================================*/
    // Check for unbalanced state only if InsideUWU is NOT > 0
    if (InsideUWU == 0) {        // Use '==' for comparison, not '='
      //Step = 203; step();         // Set debug step to 203
      Serial.print("There seems to be an unbalanced amount of cars, there should have this amount right now: ");
      Serial.println(InsideUWU);
      IsHelpNeeded();             // Check for help requests
      //Step = 205; step();         // Set debug step to 205
    }
    /*==============================================================================*/

    IsHelpNeeded();               // Check for help requests
    IsCarHere();                  // Check if car 1 is present
  }

  SevenSeg();                     // Update seven-segment display
  IsHelpNeeded();                 // Final help check
}
/*==============================================================================*/

/*==============================================================================*/
// PARKING LOT AVAILABILITY CHECK FUNCTION
/*==============================================================================*/
void IsFull() {
  // Check if parking lot has available space
  if (isOpenToTryNewThings == true){
    Creampie();                    // Process incoming cars if space is available
  }
}
/*==============================================================================*/

/*==============================================================================*/
// HELP REQUEST MONITORING FUNCTION
/*==============================================================================*/
void IsHelpNeeded() {                          // Monitor for help requests and flash LED
  buttStatus = digitalRead(ButtPlug);          // Read help request button state
  //Step = 300; step();                          // Set debug step to 300
  
  // Check if help button is pressed (LOW due to INPUT_PULLUP)
  if (buttStatus == LOW) {
    //Step = 301; step();                        // Set debug step to 301
    Serial.println("Assistance is wanted!");
    Flash();                                   // Start LED flashing sequence
  }
  else {
    digitalWrite(HelpLED , LOW);               // Turn off help LED when no request
    //Step = 302; step();                        // Set debug step to 302
  }
  delay(100);                                  // 100ms delay for button debouncing
}
/*==============================================================================*/

/*==============================================================================*/
// HELP LED FLASHING FUNCTION
/*==============================================================================*/
void Flash(){
  Step = 400; step();               // Set debug step to 400
  AssStatus = digitalRead(Ass);     // Read help response button state
  
  // Flash LED until help response button is pressed
  while (AssStatus == HIGH){        // While button is NOT pressed (HIGH due to INPUT_PULLUP)
    //Step = 401; step();             // Set debug step to 401
    digitalWrite(HelpLED , LOW);    // Turn LED off
    delay(1000);                    // Wait 1 second
    digitalWrite(HelpLED , HIGH);   // Turn LED on
    delay(1000);                    // Wait 1 second
    AssStatus = digitalRead(Ass);   // Re-read button state
  }
  
  // Help response received
  //Step = 402; step();               // Set debug step to 402
  Serial.println("Someone Has Responded to the Call");    
  digitalWrite(HelpLED , LOW);      // Turn off help LED
}
/*==============================================================================*/

/*==============================================================================*/
// CAR COUNT MONITORING FUNCTION
/*==============================================================================*/
void INSIDEUWU(){                   // Monitor and validate car count inside parking lot
  //Step = 500; step();               // Set debug step to 500
  Serial.print("Cars inside: ");
  Serial.println(InsideUWU);
  
  // Check car count and set parking lot availability
  if (InsideUWU < 5){              // If less than 5 cars inside
    isOpenToTryNewThings = true;    // Allow incoming cars
    //Step = 501; step();             // Set debug step to 501
  }
  else if (InsideUWU == 5){        // If exactly 5 cars inside (FIXED: was '=' assignment)
    isOpenToTryNewThings = false;   // Prevent incoming cars (lot is full)
    Step = 502; step();             // Set debug step to 502
  }
  else{                             // Should never happen (error condition)
    Step = 503; step();             // Set debug step to 503
    MoreThen5();                    // Handle overflow condition
  }
}
/*==============================================================================*/

/*==============================================================================*/
// OVERFLOW ERROR HANDLING FUNCTION
/*==============================================================================*/
void MoreThen5(){
  Step = 504; step();               // Set debug step to 504
  
  // Check for overflow condition
  if (InsideUWU > 5) {
    Step = 505; step();             // Set debug step to 505
    Serial.println("There are more than 5 cars inside, this is not allowed.");
    isOpenToTryNewThings = false;   // Prevent further actions if over capacity
    Step = 506; step();             // Set debug step to 506
  }
}
/*==============================================================================*/

/*==============================================================================*/
// SEVEN-SEGMENT DISPLAY CONTROL FUNCTION
/*==============================================================================*/
void SevenSeg(){                                // Update display to show number of empty spaces
  if (InsideUWU == 0){                         // CarPark Empty (show "F" for Full)
    Full();
  }
  if (InsideUWU == 1){                         // 1 car inside (show "4" for 4 empty spaces)
    four();
  }
  if (InsideUWU == 2){                         // 2 cars inside (show "3" for 3 empty spaces)
    three();
  }
  if (InsideUWU == 3){                         // 3 cars inside (show "2" for 2 empty spaces)
    two();
  }
  if (InsideUWU == 4){                         // 4 cars inside (show "1" for 1 empty space)
    one();
  }
  if (InsideUWU == 5){                         // CarPark Full (show "0" for 0 empty spaces)
    zero();
  }
}
/*==============================================================================*/

/*==============================================================================*/
// SEVEN-SEGMENT DISPLAY PATTERN FUNCTIONS
/*==============================================================================*/
void zero(){                      // Display "0" pattern (all segments except G)
  digitalWrite(LedA , LOW);       // Segment A ON
  digitalWrite(LedB , LOW);       // Segment B ON
  digitalWrite(LedC , LOW);       // Segment C ON
  digitalWrite(LedD , LOW);       // Segment D ON
  digitalWrite(LedE , LOW);       // Segment E ON
  digitalWrite(LedF , LOW);       // Segment F ON
  digitalWrite(LedG , HIGH);      // Segment G OFF
  digitalWrite(LedDP , HIGH);     // Decimal point OFF
}
/*==============================================================================*/
void Full(){                                              // Display "F" pattern (Full of Free spaces parking lot)
  digitalWrite(LedA , LOW);       // Segment A ON
  digitalWrite(LedB , HIGH);      // Segment B OFF
  digitalWrite(LedC , HIGH);      // Segment C OFF
  digitalWrite(LedD , HIGH);      // Segment D OFF
  digitalWrite(LedE , LOW);       // Segment E ON
  digitalWrite(LedF , LOW);       // Segment F ON
  digitalWrite(LedG , LOW);       // Segment G ON
  digitalWrite(LedDP , HIGH);     // Decimal point OFF
}
/*==============================================================================*/
void one(){                       // Display "1" pattern
  digitalWrite(LedA , HIGH);      // Segment A OFF
  digitalWrite(LedB , LOW);       // Segment B ON
  digitalWrite(LedC , LOW);       // Segment C ON
  digitalWrite(LedD , HIGH);      // Segment D OFF
  digitalWrite(LedE , HIGH);      // Segment E OFF
  digitalWrite(LedF , HIGH);      // Segment F OFF
  digitalWrite(LedG , HIGH);      // Segment G OFF
  digitalWrite(LedDP , HIGH);     // Decimal point OFF
}
/*==============================================================================*/
void two(){                       // Display "2" pattern
  digitalWrite(LedA , LOW);       // Segment A ON
  digitalWrite(LedB , LOW);       // Segment B ON
  digitalWrite(LedC , HIGH);      // Segment C OFF
  digitalWrite(LedD , LOW);       // Segment D ON
  digitalWrite(LedE , LOW);       // Segment E ON
  digitalWrite(LedF , HIGH);      // Segment F OFF
  digitalWrite(LedG , LOW);       // Segment G ON
  digitalWrite(LedDP , HIGH);     // Decimal point OFF
}
/*==============================================================================*/
void three(){                     // Display "3" pattern
  digitalWrite(LedA , LOW);       // Segment A ON
  digitalWrite(LedB , LOW);       // Segment B ON
  digitalWrite(LedC , LOW);       // Segment C ON
  digitalWrite(LedD , LOW);       // Segment D ON
  digitalWrite(LedE , HIGH);      // Segment E OFF
  digitalWrite(LedF , HIGH);      // Segment F OFF
  digitalWrite(LedG , LOW);       // Segment G ON
  digitalWrite(LedDP , HIGH);     // Decimal point OFF
}
/*==============================================================================*/
void four(){                      // Display "4" pattern
  digitalWrite(LedA , HIGH);      // Segment A OFF
  digitalWrite(LedB , LOW);       // Segment B ON
  digitalWrite(LedC , LOW);       // Segment C ON
  digitalWrite(LedD , HIGH);      // Segment D OFF
  digitalWrite(LedE , HIGH);      // Segment E OFF
  digitalWrite(LedF , LOW);       // Segment F ON
  digitalWrite(LedG , LOW);       // Segment G ON
  digitalWrite(LedDP , HIGH);     // Decimal point OFF 
}
/*==============================================================================*/
void fiveDot(){                    // Display "5." pattern (with decimal point)
  digitalWrite(LedA , LOW);       // Segment A ON
  digitalWrite(LedB , HIGH);      // Segment B OFF
  digitalWrite(LedC , LOW);       // Segment C ON
  digitalWrite(LedD , LOW);       // Segment D ON
  digitalWrite(LedE , HIGH);      // Segment E OFF
  digitalWrite(LedF , LOW);       // Segment F ON
  digitalWrite(LedG , LOW);       // Segment G ON
  digitalWrite(LedDP , LOW);      // Decimal point ON
}
/*==============================================================================*/
void six(){                        // Display "6" pattern
  digitalWrite(LedA , LOW);        // Segment A ON
  digitalWrite(LedB , HIGH);       // Segment B OFF
  digitalWrite(LedC , LOW);        // Segment C ON
  digitalWrite(LedD , LOW);        // Segment D ON
  digitalWrite(LedE , LOW);        // Segment E ON
  digitalWrite(LedF , LOW);        // Segment F ON
  digitalWrite(LedG , LOW);        // Segment G ON
  digitalWrite(LedDP , HIGH);      // Decimal point OFF
}
/*==============================================================================*/
// DEBUG STEP TRACKING FUNCTION
/*==============================================================================*/
void step() {
  Serial.print("Step: ");
  Serial.println(Step);
  // This function is used to print the current step for debugging purposes
  // It prints the value of the Step variable to the Serial Monitor
  // This can help track the flow of the program and identify where issues may arise
  // The Step variable is incremented at various points in the code 
  // to indicate the current state or action being performed
  // This is useful for troubleshooting and understanding the program's execution flow
}
/*==============================================================================*/

/*==============================================================================*/
// CAR 1 SENSOR DETECTION FUNCTION
/*==============================================================================*/
void IsCarHere(){
  Car1Pegging = analogRead(Car1);              // Read Car1 sensor analog value
  // Threshold of 500 for car detection (adjust based on your sensor)
  if (Car1Pegging > 500) {                     // Check if sensor detects a car
    Serial.println("=== CAR DETECTED ===");
    Serial.println("Scenario: Car 1 sensor detected a vehicle");
    Serial.print("Sensor value: ");
    Serial.println(Car1Pegging);
    Serial.println("Action: Turning on Car1 LED indicator");
    digitalWrite(Car1LED, HIGH);                // Turn on Car1 LED indicator
    Step = 600; step();                         // Set debug step to 600
  }
  else if (Car1Pegging < 500){
    digitalWrite(Car1LED, LOW);                 // Turn off Car1 LED indicator
    //Step = 601; step();                         // Set debug step to 601
  }
}
/*==============================================================================*/