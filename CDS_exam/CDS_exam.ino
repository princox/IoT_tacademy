void setup() {
  // put your setup code here, to run once:

  pinMode(5, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int adc_value = analogRead(5);
 float cds_volt = adc_value * (5.0 / 1023.0);
 
 Serial.print("CDS : ");
 Serial.print(cds_volt);
 Serial.print("(V) -> ADC : ");
 Serial.println(adc_value);
 delay(500);
}
