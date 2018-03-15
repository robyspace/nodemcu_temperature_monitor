/* In this program we are going to test a Dallas Temperature Sensor with NodeMCU Module. 
 *  here, we are using Onewire.h and DallasTemeperature.h Library.
 *  we need to connect ds18b20/ds1820 sensor to our nodeMCU .
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2                // Connect D4 Pin on NodeMCU

OneWire onewire(ONE_WIRE_BUS);

DallasTemperature sensors(&onewire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Demo...!!!!");
  sensors.begin();    // Begin the sensor to accept digital readings.
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Requesting Temperature....");
  sensors.requestTemperatures();        // Request Temperature from a sensor.
  Serial.println("DONE");
  Serial.print("Temperature is:  ");
  float TempC = sensors.getTempCByIndex(0);
  float TempF = sensors.getTempFByIndex(0);
  Serial.print(TempC);       // Getting temperaure in the celsius Form.
  Serial.print("\t");
  Serial.println(TempF);
   delay(1000); 
}


