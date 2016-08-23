#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>

char ssid[] = "TA-Edu-AP10";
char password[] = "td!160705";
int status = WL_IDLE_STATUS;
WiFiServer server(80);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wifi Shield Error");
    while (true);
  }

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
    delay(3000);
  }

  Serial.println("Wi-Fi AP Connected!");
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (client) {
    while (client.available()) client.read(); // 클라이언트의 요청 정보를 수신
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type:text/html");
    client.println("Connection:close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<H1>Wi-Fi Shield WebServer Exam</H1>");
    client.println("</html>");
    client.println(""); client.stop();
  }
}










