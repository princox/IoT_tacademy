#include "DHT11.h"
DHT11 dht11(4); //온습도계 4포트

void setup() {
  // put your setup code here, to run once:
  // 핀 모드는 아날로그는 쓰지 않고 디지털만 쓰면 된다
pinMode(13, OUTPUT);  // digitalWrite // pinMode INPUT - digitalRead
pinMode(7, INPUT);
pinMode(6, INPUT); // 인체감지
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, INPUT);
Serial.begin(9600);   // 보드레이트 통신 속도
}

void loop() {
  // put your main code here, to run repeatedly:
int MICsound = analogRead(0); //소리감지. 
int soundDigitalOut = digitalRead(7); //소리 읽기
int humanCo = digitalRead(6); // 인체감지
int gas = analogRead(1);
float temp, humidity;
dht11.read(humidity, temp);
int light = analogRead(2);
digitalWrite(2, HIGH);
delay(1000);
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
delay(1000);
digitalWrite(3, LOW);
Serial.print("sound : "); Serial.print(MICsound);
Serial.print(" / human : "); if(humanCo==1){Serial.print("detected");}else{Serial.print("not detected");}
Serial.print(" / humidity: "); Serial.print(humidity);
Serial.print(" / gas: "); Serial.print(gas);
Serial.print(" / light: "); Serial.print(light);
Serial.println();


delay(80);
}
