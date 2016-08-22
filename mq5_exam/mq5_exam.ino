void setup() {
  // put your setup code here, to run once:
pinMode(2, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int value = analogRead(0);
int limit = digitalRead(2);

Serial.println(value);
Serial.println(limit);
if(limit == HIGH) {
Serial.println("HIGH"); 
}
 delay(1000);
}
