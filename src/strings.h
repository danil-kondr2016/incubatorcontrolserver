#ifndef STRINGS_H
#define STRINGS_H

#include <pgmspace.h>

#define DOCTYPE_HTML4 "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">"
#define FOOTER  "<p><i>IncubatorServer " __DATE__ " " __TIME__ "</i></p>"

const char msg404[] PROGMEM =
  DOCTYPE_HTML4 "\r\n"
  "<html>\r\n"
  "<head><title>Error</title></head>\r\n"
  "<body>\r\n"
  "<h1 align=\"center\">Error 404: page not found</h1>\r\n"
  "<hr>\r\n" FOOTER "\r\n"
  "</body>\r\n"
  "</html>\r\n";

const char msgWelcome[] PROGMEM = 
  DOCTYPE_HTML4 "\r\n"
  "<html>\r\n"
  "<head><title>Incubator</title></head>\r\n"
  "<body>\r\n"
  "<h1 align=\"center\">The IoT-incubator</h1>\r\n"
  "<p align=\"center\">Created by Kondratenko Daniel in 2021</p>\r\n"
  "<hr>\r\n"
  "<p align=\"center\">"
  "[<a href=\"/wifi_info\">Wi-Fi information</a>]&nbsp;"
  "[<a href=\"/control_panel\">Wi-Fi configuration</a>]\r\n"
  "</p><hr>\r\n" FOOTER "\r\n"
  "</body>\r\n"
  "</html>\r\n";

const char msgControlPanel[] PROGMEM = 
  DOCTYPE_HTML4 "\r\n"
  "<html>\r\n"
  "<head><title>Wi-Fi configuration | Incubator</title></head>\r\n"
  "<body>\r\n"
  "<h1 align=\"center\">The IoT-incubator</h1>\r\n"
  "<p align=\"center\">Created by Kondratenko Daniel in 2021</p>\r\n"
  "<hr>\r\n"
  "<p align=\"center\">[<a href=\"/\">"
  "Back to main page</a>"
  "]\r\n"
  "<hr>\r\n"
  "<form method=\"POST\" action=\"/staconf\">\r\n"
  "<p>Wi-Fi access point name (SSID) "
  "<input type=\"text\" name=\"ssid\" value=\"%s\"></p>\r\n"
  "<p>Wi-Fi access point password "
  "<input type=\"password\" name=\"password\" value=\"%s\"></p>\r\n"
  "<p><input type=\"submit\" value=\"Accept\"></p>\r\n"
  "<hr>\r\n" FOOTER "\r\n"
  "</body>\r\n"
  "</html>\r\n";

const char msgWiFiInfo[] PROGMEM = 
  DOCTYPE_HTML4 "\r\n"
  "<html>\r\n"
  "<head><title>Wi-Fi information | Incubator</title></head>\r\n"
  "<body>\r\n"
  "<h1 align=\"center\">The IoT-incubator</h1>\r\n"
  "<p align=\"center\">Created by Kondratenko Daniel in 2021</p>\r\n"
  "<hr>\r\n"
  "<p align=\"center\">[<a href=\"/\">"
  "Back to main page</a>"
  "]\r\n"
  "<hr>\r\n"
  "<p><b>Wi-Fi station SSID:</b> &nbsp; %s</p>\r\n"
  "<p><b>Wi-Fi station local ID:</b> &nbsp; %s</p>\r\n"
  "<hr>\r\n" FOOTER "\r\n"
  "</body>\r\n"
  "</html>\r\n";

#endif
