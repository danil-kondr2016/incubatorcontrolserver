#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include "strings.h"

IPAddress address(192,168,4,1);
ESP8266WebServer server(address);
DNSServer dns;

unsigned long timer;

void handleRoot(void);
void handleCmds(void);
void handle404(void);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  while (!Serial);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(address, address, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Incubator");

  dns.setTTL(300);
  dns.start(53, "incubator.local", address);

  server.on("/", handleRoot);
  server.on("/control", handleCmds);
  server.onNotFound(handle404);
  server.begin();
}

void loop() {
  dns.processNextRequest();
  server.handleClient();
}

void handleCmds(void) {
  if (server.method() == HTTP_GET) {
    server.send(200, "text/plain", "method_get\r\n");
    return;
  }

  String cmd = server.arg("plain");
  String answer;
  for (int i = 0; i < cmd.length(); i++) {
    if (cmd[i] == '\r')
      continue;
    if (cmd[i] == '\n')
      break;
    Serial.print(cmd[i]);
  }
  Serial.print('\r');
  Serial.print('\n');
  timer = millis();
  while (!Serial.available()) {
    if ((millis() - timer) >= 1500) {
      server.send(200, "text/plain", "timeout\r\n");
      return;
    }
  }
  while (Serial.available()) {
    int inc = Serial.read();
    answer += (char)inc;
  }

  server.send(200, "text/plain", answer);
}

void handle404(void) {
  server.send(404, "text/html", msg404);
}

void handleRoot(void) {
  server.send(200, "text/html", msgWelcome);
}
