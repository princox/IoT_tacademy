void setup() {
  // put your setup code here, to run once:
pinMode(2, INPUT); // voice
pinMode(8, INPUT); // human cognition
pinMode(13, INPUT); 
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int value = analogRead(0); //소리
int limit = digitalRead(2); // 그냥 소리 HIGH 되는지 감지
int humanCo = digitalRead(8); // 인체감지
int certainValue = 30; // 소리가 넘어야 하는 값
int certainValue2 = 1; // 신체
int certainValue3 = 1000; // 조도센서가 넘어야 하는 값
int lightOn = analogRead(5);

Serial.print("light : ");
Serial.print(lightOn);
Serial.print(" value : ");
Serial.println(value);

if(humanCo == 1){
  Serial.print("human contact on");
}else{
  Serial.print("No human contact");
}

if(value > certainValue && humanCo == certainValue2 && lightOn < certainValue3) {
digitalWrite(13, HIGH);

Serial.println("");
Serial.println("RRRRRRRRingMYYYYYYBelllll");
Serial.println("");

}

/***
 * mission code
 * value - voice
 */
//if(value > certainValue && humanCo == HIGH && ){}
 delay(1000);
}
