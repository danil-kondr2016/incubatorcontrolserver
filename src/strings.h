#ifndef STRINGS_H
#define STRINGS_H

#include <pgmspace.h>

#define DOCTYPE_HTML4 "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">"
#define FOOTER  "<p><i>IncubatorServer " __DATE__ " " __TIME__ "</p></i>"

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
  "<hr>\r\n" FOOTER "\r\n"
  "</body>\r\n"
  "</html>\r\n";

 

#endif