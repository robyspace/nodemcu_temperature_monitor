/* This program is a sending a temperature reading to a webserver .
 *    Program includes 
 *        - Create a webserver and make a webpage contains turn-on, turn-off buttons and a link to get the temperature reading 
 *          by using the temperature reading we are able to control the led's if temperature is below 10 and temperature is above 40degrees le will be blinking in on-off state.
 */ 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <OneWire.h>
#include <DallasTemperature.h>
#define  ONE_WIRE_BUS   2

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature sensors(&onewire);
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
float prevTemp = 0;
ESP8266WebServer server(81);    // Create a webserver object that listens for HTTP request on port 80


void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void setup(void)
{
  pinMode(13,OUTPUT);
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Moto", "123@1234");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Vistronics", "#VistroniX$");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED_ON",[](){               //Call and handle the LED_ON function
    digitalWrite(13,HIGH);
    server.send(200,"text/html","<html><h1>Your LED is Now Configured to ON....!!!</h1><br><br><a href = \"/\">Go back to main page</a></html>");
  });

  server.on("/LED_OFF",[](){            //Call and handle the LED_OFF function
    digitalWrite(13,LOW);
    server.send(200,"text/html","<html><h1>Your LED is Now Configured to OFF....!!!</h1><br><br><a href = \"/\">Go back to main page</a></html>");
  });

  server.on("/TEMP_NOW",[](){       //Call and handle the TEMP_NOW function
    sensors.begin();
    sensors.requestTemperatures();
    float   temp = sensors.getTempCByIndex(0);
    if(temp <= 10 || temp >=40)
    {
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      delay(1000);
    }
    String webString="Temperature: "+String(temp)+" F";
  
    server.send(200,"text/plain",webString);
  });
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<html><h1>Welcome to the My Web Page.</h1><br><h3>Please choose the button to turn on or off the led..</h3><br><a href=\"/LED_ON\"\"><button>Turn On </button></a><a href=\"/LED_OFF\"\"><button>Turn Off </button></a><br><br><a style = \"color:red\" href = \"/TEMP_NOW\">Get Current Temperature </a></html>");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
