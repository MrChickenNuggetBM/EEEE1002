void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  Wire.begin();
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop() {
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  Serial.println("high");
  delay(3000);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  Serial.println("low");
  delay(3000);
}
