#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>


ESP8266WiFiMulti wifiMulti;

ESP8266WebServer server(80);

String INDEX_HTML = R"=====(
<!DOCTYPE HTML>
  <html lang="en">
    <head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <title>GODs Controler</title>
        </head>
          <body> 
            <form action="SetColor" method="POST">
              <input type="color" name="color" placeholder="color">
              <input type="submit" value="SetColor">
            </form>
          </body>
</html>
)=====";

void handleRoot();              
void handleSetColor();
void handleNotFound();

#define PIN D5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


void setColor(uint32_t c) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    }
}
void RGB() {
  int r,g,b;
   setColor(strip.Color(r,g,b));
}

void setup() { 
  Serial.begin(115200);
  strip.begin();
  strip.show();
  delay(10);

  Serial.println('\n');

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

  server.on("/off", []() {
    server.send(200, "text/html", INDEX_HTML);
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

  server.on("/mode0", []() {
    server.send(200, "text/html", INDEX_HTML);
    color1=4;
    Serial.print("Pressed: ");
    Serial.println("mode0");
    delay(1000);
  });
  server.on("/mode1", []() {
    server.send(200, "text/html", INDEX_HTML);
    Serial.print("Pressed: ");
    Serial.println("mode1");
    delay(1000);
  });
  server.on("/mode2", []() {
    server.send(200, "text/html", INDEX_HTML);
    Serial.print("Pressed: ");
    Serial.println("mode2");
    delay(1000);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}

void handleRoot() {                         
  server.send(200, "text/html", INDEX_HTML);
}

void handleSetColor() {                        
  if(server.arg("color") != NULL) {
    server.send(200, "text/html", INDEX_HTML);
    Serial.println(server.arg("color"));
    return;
  }
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

