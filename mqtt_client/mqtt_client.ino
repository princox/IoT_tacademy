#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT11.h"
#include "PubSubClient.h"
byte server[] = {192, 168, 0, 39};
int port = 1883;
char clientid[64];
char topic[10 + 1] = {'d', 'h', 't', '1', '1', '\0'};
char ssid[] = "TA-Edu-AP10";
char password[] = "td!160705";
int status = WL_IDLE_STATUS;
void msgReceived(char *topic, byte* payload, unsigned int uLen);
PubSubClient client(server, port, msgReceived, wificlient);
DHT11 dht11(3);

void setup() {
  // put your setup code here, to run once:
  // 와이파이 쉴드에 접속하고, 성공하면 MQTT 서버에 연결한다
  Serial.begin(9600);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi Shield Error);
                   while(true); }
  while(status != WL_CONNECTED) {
 status = WiFi.begin(ssid, password);
 delay(3000);
 }
 Serial.println("Wi - Fi AP Connected");
 sprintf(clientId, "arduino");
 if ( client.connect(clientId) ) {
 sprintf(topic, "dht11");
 client.subscribe(topic);
 int error;
 float temp.humidity;
 if (( error = dht11.read(humidity, temp)) == 0 ) {
 char message[64] = "";
 sprintf(message, " {\"temp\":%.3f,\"humidity\":%.3f}", temp.humidity);
 client.publish(topic,)
}
  }
}
void msgReceived(char* topic, byte* payload, unsigned int uLen) {
  for (int i = 0; i < uLen; i++) Serial.print(payload[i]);
}


void loop() {
  // put your main code here, to run repeatedly:

}
