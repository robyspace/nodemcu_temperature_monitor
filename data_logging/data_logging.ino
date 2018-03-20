/*I going to write small code which can create one text file 
 * and store it in the SPI Flash and 
 * get those data whatever is there in text file.
 * I'm going to write small code which can create one text file 
 * and store it in the SPI Flash and we can get the get the data 
 * and print in the serial monitor. 
 * 
 */

#include "FS.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define  ONE_WIRE_BUS   2             // Define a analog pin Number for Dallas temperature 
OneWire onewire(ONE_WIRE_BUS);        // Create an instance of OneWire  
DallasTemperature sensors(&onewire);  // Create an instance of Dallas Temperature with reference OneWire Instance.

float temp;
File f;
bool status1;
String filename = "/temp_readings_spi.txt";
String write_status;
String read_status;

//------------------------------ESP8266 SPIFFS Read Function -------------------------//
String reading_data(String filename)
{
  String data;
   bool ok = SPIFFS.begin();                            // Starts  a SPI File System.
   if (ok) 
   {
      Serial.println("ok");
      bool exist = SPIFFS.exists(filename);
      if (exist) {
        Serial.println("The file exists!");
      File f = SPIFFS.open(filename, "r");
      if (!f)
      {
        Serial.println("Some thing went wrong trying to open the file...");
      }
      else 
      {
        Serial.println("====== Reading from SPIFFS file =========");
        int s = f.size();
        Serial.printf("Size=%d\r\n", s);
        data = f.readString();
        //Serial.println(data);
        f.close();
        return data;
      }
    }
    else {
      Serial.println("No such file found.");
      return "no file";
    }
  }
}

//------------------------------ESP8266 SPIFFS Write Function -------------------------//
String write_temp_data(float temp1)
{

   bool ok = SPIFFS.begin();                            // Starts  a SPI File System.
   if (ok) 
   {
      Serial.println("ok");
      bool exist = SPIFFS.exists(filename);
      if (exist) 
      {
        Serial.println("The file exists!");
        File f = SPIFFS.open(filename, "a");
        if (!f)
        {
          Serial.println("Some thing went wrong trying to open the file...");
        }
        else 
        {
          Serial.println("====== Writing to SPIFFS file =========");
          //Serial.println(temp);
          f.println(temp1);
          f.close();
        }
        return "Write Successfully!!";
      }
      else 
      {
        Serial.println("No such file found.");
        return "no file";
      }
   }
}

void setup() {
    // put your setup code here, to run once:
    
    Serial.begin(115200);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.begin();                     // Start temperature Sensor.
  sensors.requestTemperatures();       // Request sensor values
  float ptemp = sensors.getTempCByIndex(0);        
  if(!(ptemp>=85 || ptemp <= -127))      // Ignore the invalid temperatures.
  {
    temp = ptemp;
  }
  write_status = write_temp_data(temp);
  Serial.println(write_status);
  read_status = reading_data(filename);
  Serial.println(read_status);
}
