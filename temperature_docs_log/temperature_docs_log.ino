
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClientSecure.h>


int iw = 0;

//------------------------------Dallas Temperature Instances--------------------------//

#define  ONE_WIRE_BUS   2             // Define a analog pin Number D7 for Dallas temperature 
OneWire onewire(ONE_WIRE_BUS);        // Create an instance of OneWire  
DallasTemperature sensors(&onewire);  // Create an instance of Dallas Temperature with reference OneWire Instance.

//----------------------------Google Sheet Data----------------------------------//
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";        // SHA1 fingerprint of the certificate, don't care with your GAS service
String GAS_ID = "AKfycbxeMAnUfhQB0WzN17lp3I83ue93h8m3mAkm8Jfdw5nAQR_txTU";   // Replace by your GAS service id 

//----------------------------Global Variables----------------------------------//
String readString;
float   temp;
String data;

//----------------------------Wifi Clasess----------------------------------//
WiFiServer server(81);          // Server starts in port number 81
WiFiClientSecure client1;       // Use WiFiClientSecure class to create TLS connection
ESP8266WiFiMulti wifiMulti; 



//----------------------------Connect Wifi Function----------------------------------//
void connectWiFiInit(void) {
  
  wifiMulti.addAP("Moto", "123@1234");        // add Wi-Fi networks you want to connect to
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
  Serial.print("Mac Address:\t");
  Serial.println(WiFi.macAddress());
  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
 
}


void setup() 
{
  Serial.begin(115200);
  connectWiFiInit();        //Connect to WIfi
  server.begin();                                               // Starting a server.
  Serial.println("HTTP Server Started!!!");
 }

void loop() 
{
  iw++;
  sensors.begin();                     // Start temperature Sensor.
  sensors.requestTemperatures();       // Request sensor values
  float ptemp = sensors.getTempCByIndex(0);        
  if(!(ptemp>=85 || ptemp <= -127))      // Ignore the invalid temperatures.
  {
    temp = ptemp;
  }
  
  
  sendData(temp);
 
  
  delay(60*1000);
  WiFiClient client = server.available();
  String req = client.readStringUntil('\r');
  if(req.indexOf("//"))
  {client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("<html><body><ul href=\"https://docs.google.com/spreadsheets/d/e/2PACX-1vQky0tYR-qL7hQE8nBV9z4ntWZq5e6Y6vQO1h_4qZuvhb_O2joMfg-WHXn6A7CgSG7ZdHr6gpHT6tQM/pubchart?oid=2075401417&format=interactive\">See charts</ul></body></html>"); //  do not forget this one

  
  }
}

// Function for Send data into Google Spreadsheet
void sendData(float tem)
{
  Serial.print("connecting to ");
  Serial.println(host);
  client1.connect(host, httpsPort);     //connect to google server
    
  
  String string_temperature =  String(tem, 3); 
  
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature;//+ "&humidity=" + string_humidity;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");               //print data into google sheets

  Serial.println("request sent");
  while (client1.connected()) {
  String line = client1.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
  }
  }
  
  Serial.println("closing connection");
}

