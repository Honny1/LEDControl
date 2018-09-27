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

#define NUM_LEDS          60
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
bool RAINBOW;
bool TwinkleRandom;
bool Strobe;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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
  setColor(strip.Color(r,g,b));
}
void setup() { 
  Serial.begin(115200);
  strip.begin();
  strip.show();
  delay(10);

  Serial.println('\n');
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("Hony", "9E6wi76j");  

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

   server.on("/Strobe", []() {
    server.send(200, "text/html", INDEX_HTML);
    RAINBOW=false;
    TwinkleRandom=false;
    Strobe=true;
    while(Strobe){strobe();}
    Serial.print("Pressed: ");
    Serial.println("Strobe");
    delay(1000);
  });
  server.on("/TwinkleRandom", []() {
    server.send(200, "text/html", INDEX_HTML);
    RAINBOW=false;
    TwinkleRandom=true;
    Strobe=false;
    setColor(strip.Color(0,0,0));
    while(TwinkleRandom){twinkleRandom(20, 100);}
    Serial.print("Pressed: ");
    Serial.println("TwinkleRandom");
    delay(1000);
  });
  server.on("/RAINBOW", []() {
    server.send(200, "text/html", INDEX_HTML);
    RAINBOW=true;
    TwinkleRandom=false;
    Strobe=false;
    while(RAINBOW){rainbow(20);}
    Serial.print("Pressed: ");
    Serial.println("RAINBOW");
    delay(1000);
  });
  server.on("/lightup", []() {
    server.send(200, "text/html", INDEX_HTML);
    brightnessPlus();
    RAINBOW=false;
    TwinkleRandom=false;
    Strobe=false;
    Serial.print("Pressed: ");
    Serial.println("up");
    delay(1000);
  });
  server.on("/lightdown", []() {
    server.send(200, "text/html", INDEX_HTML);
    brightnessMinus();
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("down");
    delay(1000);
  });
  server.on("/off", []() {
    server.send(200, "text/html", INDEX_HTML);
    color2=color1;
    color1=3;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("off");
    delay(1000);
  });
  server.on("/on", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=color2;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("on");
    delay(1000);
  });
  server.on("/red", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=4;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("red");
    delay(1000);
  });
  server.on("/green", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=5;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("green");
    delay(1000);
  });
  server.on("/blue", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=6;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("blue");
    delay(1000);
  });
  server.on("/white", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=7;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("white");
    delay(1000);
  });

  server.on("/red1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=8;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("red1");
    delay(1000);
  });
  server.on("/green1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=12;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("green1");
    delay(1000);
  });
  server.on("/blue1", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=16;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("blue1");
    delay(1000);
  });
  server.on("/red2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=9;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("red2");
    delay(1000);
  });
  server.on("/green2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=13;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("green2");
    delay(1000);
  });
  server.on("/blue2", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=17;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("blue2");
    delay(1000);
  });
  server.on("/red3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=10;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("red3");
    delay(1000);
  });
  server.on("/green3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=14;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("green3");
    delay(1000);
  });
  server.on("/blue3", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=18;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("blue3");
    delay(1000);
  });
  server.on("/red4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=11;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("red4");
    delay(1000);
  });
  server.on("/green4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=15;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
    Serial.print("Pressed: ");
    Serial.println("green4");
    delay(1000);
  });
  server.on("/blue4", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=19;
    RAINBOW=false;
    Strobe=false;
    TwinkleRandom=false;
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
  RAINBOW=false;
  Strobe=false;
  TwinkleRandom=false;                         
  server.send(200, "text/html", INDEX_HTML);
}

void handleSetColor() {                        
  RAINBOW=false;
  Strobe=false;
  TwinkleRandom=false;
  if(server.arg("color") != NULL) {
    //server.send(200, "text/html", INDEX_HTML);
    
    String hexstring =server.arg("color");
    long number = (long) strtol( &hexstring[0], NULL, 16);
    r = number >> 16;
    g = (number & 0x00ff00) >> 8;
    b = (number & 0x0000ff);
    setColor(strip.Color(r,g,b));
    server.arg("color")=hexstring;
    server.send(200, "text/html", INDEX_HTML);
    return;
  }
}

void handleNotFound(){
  RAINBOW=false;
  Strobe=false;
  TwinkleRandom=false;
  server.send(404, "text/plain", "404: Not found"); 
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      server.handleClient();
    }
    strip.show();
    delay(wait);
  }
}

void twinkleRandom(int Count, int SpeedDelay) {
  for (int i=0; i<Count; i++) {
     server.handleClient();
     strip.setPixelColor(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     strip.show();
     delay(SpeedDelay);
   }
  server.handleClient();
  delay(SpeedDelay);
}
void strobe(){ 
 server.handleClient();
 setColor(strip.Color(0,0,0));
 delay(50);
 setColor(strip.Color(r,g,b));
 delay(50);
}
