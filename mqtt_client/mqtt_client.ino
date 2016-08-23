#include <WiFi.h>
#include "DHT11.h"
#include "PubSubClient.h"
byte server[] = {192, 168, 0, 39};
int port = 1883;
char clientid[MAC_ADDRESS_LENGTH + 1];
char topic[TOPIC_LENGTH + 1] = {'d', 'h', 't', '1', '1', '\0'};
char ssid[] = "TA-Edu-AP10";
char password[] = "td!160705";
int status = WL_IDLE_STATUS;
void msgReceived(char *topic, byte* payload, unsigned int uLen);
PubSubClient client(server, port, msgReceived);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
