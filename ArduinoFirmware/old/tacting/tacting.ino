#define tactingPin0 PA0
#define tactingPin1 PA1
void setup() {
  DDRA = B11111110;
  PORTA = B00000000;
  // put your setup code here, to run once:
  /*pinMode(tactingPin0, OUTPUT);
  pinMode(tactingPin1, OUTPUT);
  digitalWrite(tactingPin0, LOW);
  digitalWrite(tactingPin1, LOW);*/
}

void loop() {
  PORTD = A00000001;//digitalWrite(tactingPin0, HIGH);
  //delay(1);
  PORTD = A00000000;//digitalWrite(tactingPin0, LOW);
  //delay(1);
}
