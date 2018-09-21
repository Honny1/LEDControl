#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

#include "index.h"


ESP8266WiFiMulti wifiMulti;

ESP8266WebServer server(80);



void handleRoot();              
void handleSetColor();
void handleNotFound();

#define PIN D5
#define ON                N/A
#define OFF               3
 
#define RED               4
#define GREEN             5
#define BLUE              6
#define WHITE             7
 
#define ORANGE            8
#define YELLOW_DARK       9
#define YELLOW_MEDIUM     10
#define YELLOW_LIGHT      11
 
#define GREEN_LIGHT       12
#define GREEN_BLUE1       13
#define GREEN_BLUE2       14
#define GREEN_BLUE3       15
 
#define BLUE_RED          16
#define PURPLE_DARK       17
#define PURPLE_LIGHT      18
#define PINK              19
 
unsigned long rgb = 0;
byte r,g,b;
int color1=6;
int color2=6;
int color5=999;
int BRIGHTNESS=50;
int BRIGHTNESS1=10;
byte LED1COLOR[] = { 0xFF, 0xFF, 0xFF };
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void colorConverter(String value){
     LED1COLOR[0]= value.substring(0,2).toInt();
     LED1COLOR[1]=value.substring(2,4).toInt();
     LED1COLOR[2]= value.substring(4,6).toInt();
}
void brightnessPlus(){
  BRIGHTNESS+=10;
  if(BRIGHTNESS>100){
    BRIGHTNESS=100;
    }
}
void brightnessMinus(){
  BRIGHTNESS-=10;
  if(BRIGHTNESS<0){
    BRIGHTNESS=0;
    }
}
void setColor(uint32_t c) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    }
}
void RGB(unsigned long value) {
   r = value >> 16; 
   g = (value >> 8) & 0xFF; 
   b = value & 0xFF; 
   setColor(strip.Color(r,g,b));
}
void ledColor(int color) {
  switch (color) {
    case OFF :
      r = g = b = 0;
      break;    
    case RED           : RGB(0x00FF0000); break;
    case GREEN         : RGB(0x0000FF00); break;
    case BLUE          : RGB(0x000000FF); break;
    case WHITE         : RGB(0x00FFFFFF); break;
    case ORANGE        : RGB(0x00FF7F00); break;
    case YELLOW_DARK   : RGB(0x00FFAA00); break;
    case YELLOW_MEDIUM : RGB(0x00FFD400); break;
    case YELLOW_LIGHT  : RGB(0x00FFFF00); break;       
    case GREEN_LIGHT   : RGB(0x0000FFAA); break;
    case GREEN_BLUE1   : RGB(0x0000FFFF); break;
    case GREEN_BLUE2   : RGB(0x0000AAFF); break;
    case GREEN_BLUE3   : RGB(0x000055FF); break;
    case BLUE_RED      : RGB(0x00000080); break;
    case PURPLE_DARK   : RGB(0x003F0080); break;
    case PURPLE_LIGHT  : RGB(0x007A00BF); break;
    case PINK          : RGB(0x00FF00FF); break;
  }
}
void setup() { 
  Serial.begin(115200);
  strip.begin();
  strip.show();
  delay(10);

  Serial.println('\n');

  wifiMulti.addAP("ISSWF1", "xstudent25isswf100");  

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { 
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           

  if (MDNS.begin("LedControl")) {              
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
 
  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/SetColor", HTTP_POST, handleSetColor); // Call the 'handleLogin' function when a POST request is made to URI "/login"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.on("/off", []() {
    server.send(200, "text/html", INDEX_HTML);
    color2=color1;
    color1=3;
    Serial.print("Pressed: ");
    Serial.println("off");
    delay(1000);
  });
  server.on("/on", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=color2;
    Serial.print("Pressed: ");
    Serial.println("on");
    delay(1000);
  });
  server.on("/red", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=4;
    Serial.print("Pressed: ");
    Serial.println("red");
    delay(1000);
  });
  server.on("/green", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=5;
    Serial.print("Pressed: ");
    Serial.println("green");
    delay(1000);
  });
  server.on("/blue", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=6;
    Serial.print("Pressed: ");
    Serial.println("blue");
    delay(1000);
  });
  server.on("/white", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=7;
    Serial.print("Pressed: ");
    Serial.println("white");
    delay(1000);
  });

  server.on("/red1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=8;
    Serial.print("Pressed: ");
    Serial.println("red1");
    delay(1000);
  });
  server.on("/green1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=12;
    Serial.print("Pressed: ");
    Serial.println("green1");
    delay(1000);
  });
  server.on("/blue1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=16;
    Serial.print("Pressed: ");
    Serial.println("blue1");
    delay(1000);
  });
  server.on("/red2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=9;
    Serial.print("Pressed: ");
    Serial.println("red2");
    delay(1000);
  });
  server.on("/green2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=13;
    Serial.print("Pressed: ");
    Serial.println("green2");
    delay(1000);
  });
  server.on("/blue2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=17;
    Serial.print("Pressed: ");
    Serial.println("blue2");
    delay(1000);
  });
  server.on("/red3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=10;
    Serial.print("Pressed: ");
    Serial.println("red3");
    delay(1000);
  });
  server.on("/green3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=14;
    Serial.print("Pressed: ");
    Serial.println("green3");
    delay(1000);
  });
  server.on("/blue3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=18;
    Serial.print("Pressed: ");
    Serial.println("blue3");
    delay(1000);
  });
  server.on("/red4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=11;
    Serial.print("Pressed: ");
    Serial.println("red4");
    delay(1000);
  });
  server.on("/green4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=15;
    Serial.print("Pressed: ");
    Serial.println("green4");
    delay(1000);
  });
  server.on("/blue4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=19;
    Serial.print("Pressed: ");
    Serial.println("blue4");
    delay(1000);
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
   if(color1!=color5){
    color5=color1;
    ledColor(color1);
  }
  if(BRIGHTNESS!=BRIGHTNESS1){
    BRIGHTNESS1=BRIGHTNESS;
    ledColor(color1);
    strip.setBrightness(BRIGHTNESS);
    strip.show();
  }
  server.handleClient();
}

void handleRoot() {                         
  server.send(200, "text/html", INDEX_HTML);
}

void handleSetColor() {                        
  if(server.arg("color") != NULL) {
    server.send(200, "text/html", INDEX_HTML);
    colorConverter(server.arg("color"));
    setColor(strip.Color(LED1COLOR[0],LED1COLOR[1],LED1COLOR[2]));
    return;
  }
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

