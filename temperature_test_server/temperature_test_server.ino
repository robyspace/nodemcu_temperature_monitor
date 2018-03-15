
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------Dallas Temperature Instances--------------------------//

#define  ONE_WIRE_BUS   2             // Define a analog pin Number D7 for Dallas temperature 
OneWire onewire(ONE_WIRE_BUS);        // Create an instance of OneWire  
DallasTemperature sensors(&onewire);  // Create an instance of Dallas Temperature with reference OneWire Instance.

//------------------------------ESP8266 Instances-------------------------------------//

ESP8266WiFiMulti wifiMulti;           // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(81);          // Create a webserver object that listens for HTTP request on port 81

float   temp;
String data;

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

//------------------------------ESP8266 Handling Temperature Page ---------------------//

void handleRoot()
{
  String temperatureString = (String)temp;
  String title = "Temperature";
  String message;
  String cssClass  = "mediumhot";
  
  if(temp < 30)
    cssClass = "cold";
  else if(temp >40)
    cssClass  = "hot";  
message = "<html><head><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">";
       message += "<style>body{/*background: linear-gradient(to bottom, #fcdb88,#d32106);*/margin:0px;padding:0px;font-family:\"Helvetica Neue\", Helvetica, Arial;}";
       message += "#sidebar1{/*background: linear-gradient(to bottom, #fcdb88,#d32106);*/  width:200px;  height:100%;  display:block;  position:absolute;  left:-200px;  top:0px;  transition:left 0.3s linear;}";
       message += "#sidebar1.visible{  left:0px;  transition:left 0.3s linear;}";
       message += "ul{  margin:0px;  padding:0px;} ul li{  list-style:none;}";
       message += "ul li a{ /*background: linear-gradient(to bottom, #fcdb88,#d32106); */ color:black;  border-bottom:1px solid White;  display:block;  width:180px;  padding:10px;  text-decoration: none;}";
       message += "#sidebar-btn{  display:inline-block;  vertical-align: middle;  width:20px;  height:15px;  cursor:pointer;  margin:20px;  position:absolute;  top:0px;  right:-60px;}";
       message += "#sidebar-btn span{  height:1px;  background:white;  margin-bottom:5px;  display:block;}#sidebar-btn span:nth-child(2){  width:75%;}";
       message += "#sidebar-btn span:nth-child(3){  width:50%;}h1 { font-size: 90px;font-weight: 400; margin: 0;}";
       message += ".cold {background: linear-gradient(to bottom, #7abcff, #0665e0 );}";
       message += ".mediumhot {background: linear-gradient(to bottom, #81ef85,#057003);}";
       message += ".hot {background: linear-gradient(to bottom, #fcdb88,#d32106);}";
       message += "</style></head><body class=\"" + cssClass + "\"> ";
       message += "<h1 style =\"color: #fff;font-family: 'Advent Pro';font-weight: 400;left: 50%;position: absolute;text-align: center;top: 40%;transform: translateX(-50%) translateY(-50%);\" >Temperature </h1>";
       message += "<h1 style = \"color: #fff;font-family: 'Advent Pro';font-weight: 400;left: 45%;position: absolute;text-align: center;top: 60%;transform: translateX(-50%) translateY(-50%);\" id = \"data\"></h1><h1 style =\"color: #fff;font-family: 'Advent Pro';font-weight: 400;left: 60%;position: absolute;text-align: center;top: 60%;transform: translateX(-50%) translateY(-50%);\"><large>&deg;C</large></h1>";
       message += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
       message += "<script>$(document).ready(function(){$('#sidebar-btn').click(function(){$('#sidebar').toggleClass('visible'); });  });</script></body></script>";
       message += "<script>\r\n";
       message += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
       message += "function loadData(url, callback){\r\n";
       message += "var xhttp = new XMLHttpRequest();\r\n";
       message += "xhttp.onreadystatechange = function(){\r\n";
       message += " if(this.readyState == 4 && this.status == 200){\r\n";
       message += " callback.apply(xhttp);\r\n";
       message += " }\r\n";
       message += "};\r\n";
       message += "xhttp.open(\"GET\", url, true);\r\n";
       message += "xhttp.send();\r\n";
       message += "}\r\n";
       message += "function updateData(){\r\n";
       message += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
       message += "}\r\n";
       message += "function w3_open() {\r\n";
       message += "document.getElementById(\"mySidebar\").style.display = \"block\";\r\n";
       message += "}\r\n";
       message += "function w3_close() {\r\n";
       message += "document.getElementById(\"mySidebar\").style.display = \"none\";\r\n";
       message += "}\r\n";
       message += "</script>\r\n";
       message += "</html>";

  
    server.send(200,"text/html",message);
}
void handleNotFound()
{
  String NotFoundPage = "<html>"\
  "<img width = \"100%\" height = \"80%\" src= \"https://cdn.dribbble.com/users/1022481/screenshots/3018253/404-snow.gif\" alt=\"404 Error!Not Found\"></img>"\
  "<h2 style = \"color:grey;text-align :center;font-size:30\">Oops! We can't seem to find a page you are looking for!</h2>"\
  "</html>";
  server.send(404,"text/html",NotFoundPage);
  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  pinMode(13,OUTPUT);           // Configure the LED Pin as OUTPUT
  connectWiFiInit();
   server.on("/data.txt",[](){                        // Storing temperature data in a data.txt server
    data = (String)temp;
    server.send(200,"text/plain",data);
  });
  server.on("/",handleRoot);     // Serves a root page of the server
  server.onNotFound(handleNotFound);                            // serves a page when server is not Found
  server.begin();                                               // Starting a server.
  Serial.println("HTTP Server Started!!!");
  
}

void loop() {
  // put your main code here, to run repeatedly:
   server.handleClient();               // Handle Clients Requests.
 sensors.begin();                     // Start temperature Sensor.
 sensors.requestTemperatures();       // Request sensor values
 float ptemp = sensors.getTempCByIndex(0);        
 if(!(ptemp>=85 || ptemp <= -127))      // Ignore the invalid temperatures.
 {
   temp = ptemp;
 }
}
