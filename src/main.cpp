#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <pgmspace.h>
#include <LittleFS.h>

#include "strings.h"

#define AP_NAME "Incubator"

IPAddress address(192,168,4,1);
IPAddress gateway(192,168,4,2);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer updater;
//DNSServer dns;

String sta_ssid, sta_password;

bool mdns_state = false;

unsigned long timer;

void handleRoot(void);
void handleCmds(void);
void handle404(void);

void handleSystemInfo(void);
void handleControlPanel(void);
void handleStaConf(void);

void setup() {
  Serial.begin(9600);

  File ssid_file = LittleFS.open("/SSID", "r");
  while (ssid_file.available()) {
    int inc = ssid_file.read();
    if (inc != -1)
      sta_ssid += (char)inc;
  }
  ssid_file.close();

  File password_file = LittleFS.open("/PASSWORD", "r");
  while (password_file.available()) {
    int inc = password_file.read();
    if (inc != -1)
      sta_password += (char)inc;
  }
  password_file.close();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(address, gateway, subnet);
  WiFi.softAP(AP_NAME, NULL, 1, false);
  if (sta_ssid != "" && sta_password != "") {
    int wifi_status;
    WiFi.begin(sta_ssid.c_str(), sta_password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(50);
    }
  }  

  //dns.setTTL(300);
  //dns.start(53, "incubator.local", address);

  mdns_state = MDNS.begin("incubator");
  if (mdns_state)
    MDNS.addService("incubator", "http", "tcp", 80);

  server.on("/", handleRoot);
  server.on("/system_info", handleSystemInfo);
  server.on("/control_panel", handleControlPanel);
  server.on("/staconf", handleStaConf);
  server.on("/control", handleCmds);
  server.onNotFound(handle404);
  updater.setup(&server);
  server.begin();
}

void loop() {
  if (mdns_state)
    MDNS.update();
//  dns.processNextRequest();
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

void handleControlPanel(void) {
  char _msg[1024] = {0};
  snprintf(_msg, 1024, msgControlPanel, 
            sta_ssid.c_str(), sta_password.c_str());
  server.send(200, "text/html", _msg);
}

void handleSystemInfo(void) {
  char _msg[1024] = {0};
  snprintf(_msg, 1024, msgSystemInfo, 
            sta_ssid.c_str(), WiFi.localIP().toString().c_str(),
            mdns_state ? "works" : "does not work");
  server.send(200, "text/html", _msg);
}

void handleStaConf(void) {
  String new_ssid = server.arg("ssid");
  String new_password = server.arg("password");

  sta_ssid = new_ssid;
  sta_password = new_password;

  File ssid_file = LittleFS.open("/SSID", "w");
  for (int i = 0; i < new_ssid.length(); i++)
    ssid_file.write(new_ssid[i]);
  ssid_file.close();
  
  File password_file = LittleFS.open("/PASSWORD", "w");
  for (int i = 0; i < new_password.length(); i++)
    password_file.write(new_password[i]);
  password_file.close();

  server.sendHeader("Location", "/control_panel");
  server.send(303);

  WiFi.disconnect();
  if (sta_ssid != "" && sta_password != "") {
    WiFi.begin(sta_ssid.c_str(), sta_password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(50);
    }
  }
}
