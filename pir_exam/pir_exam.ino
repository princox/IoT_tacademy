void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int sensor = digitalRead(2);
 if ( sensor == HIGH ){
  Serial.println("Detected Sensor");
  digitalWrite(5,HIGH);
 } else {
  Serial.println("....");
  digitalWrite(5,LOW);
 }
}
