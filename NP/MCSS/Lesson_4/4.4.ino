int val1=0;
int val2=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  val1=digitalRead(10);
  val2=digitalRead(11);
  
  if(val1 == HIGH){
    digitalWrite(9,HIGH);
  }
  else{
    digitalWrite(9,LOW);
  }

  if(val2 == HIGH){
    digitalWrite(8,LOW);
  }
  else{
    digitalWrite(8,HIGH);
  }
  
}
