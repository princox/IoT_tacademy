void setup() {
  // put your setup code here, to run once:
  // 강사님 예제코

  pinMode(5, INPUT); //인체감지
  pinMode(6, INPUT); //소리감지
  pinMode(7, OUTPUT); //부저pinMode(5, INPUT); //인체감지
  pinMode(6, INPUT); //소리감지
  pinMode(7, OUTPUT); //부저
}

void loop() {
  // put your main code here, to run repeatedly:
  int pir = digitalRead(5); //인체감지 정보
  int sound = digitalRead(6); //소리감지 정보
  int sound_value = analogRead(0); //소리감지 값
  int cdr_value = analogRead(5); //조도 값

  Serial.print(“pir: ”); Serial.println(pir);
  Serial.print(“sound: ”); Serial.println(sound);
  Serial.print(“sound value”); Serial.println(sound value);
  Serial.print(“cdr value: ”); Serial.println(cdr value);
  delay(1000);

  if (pir == HIGH && sound_value > 400 && cdr_value < 1000) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  delay(1000);
}
