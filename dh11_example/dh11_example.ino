#include "DHT11.h"
DHT11 dht11(2);
//input is pin 2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int error;
float temp, humidity;
if ((error = dht11.read(humidity, temp)) == 0) {
  Serial.print("temp: ");
  Serial.print(temp);
  Serial.print(" humidity: ");
  Serial.println(humidity);
}
}




