/*
 * I'm going to write small code which can create one text file 
 * and ask the input from the user using serial monitor and display those data in serial monitor.
 * 
 */

#include "FS.h"

File f;

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
String write_temp_data(String filename)
{
  String data;
   bool ok = SPIFFS.begin();                            // Starts  a SPI File System.
   if (ok) 
   {
      Serial.println("ok");
      bool exist = SPIFFS.exists(filename);
      if (!exist) 
      {
        File f = SPIFFS.open(filename, "w+");
        if (!f)
        {
          Serial.println("Some thing went wrong trying to open the file...");
        }
        else 
        {
          Serial.println("====== Writing to SPIFFS file =========");
          //Serial.println(temp);
          Serial.println("Enter your text");
          if(Serial.available()>0)
          {
            data = Serial.read();
          }
          f.println(data);
          f.close();
        }
        return "Write Successfully!!";
      }
      else 
      {
        Serial.println("File Already exists!!!");
        return "no file";
      }
   }
}

void setup() {
    // put your setup code here, to run once:
    String filename;
    Serial.begin(115200);
  
    Serial.println("Enter a file name you want to create: ");
    while(Serial.available())
    {
      filename = Serial.readString();
    }
    String write_status = write_temp_data(filename);
    Serial.println(write_status);
    String read_status = reading_data(filename);
    Serial.println(read_status);
}

void loop() {
  // put your main code here, to run repeatedly:

}
