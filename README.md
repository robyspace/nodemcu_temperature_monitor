# nodemcu_temperature_monitor

Collection of Arduino sketches written for the NodeMCU. The links of the libraries are used in those sketches are given below. These all sketches are depending on Dallas Temperature Sensor (DS18B20).

## Temperature test: 
Sketch that enables the NodeMCU to monitor the current room temperature using Dallas room temperature sensor and display it on a Serial Monitor. Below is the schematic diagram for connecting Dallas room temperature to NodeMCU. 
<p align="center"><img align="center" alt="schematic ds18b20" src="https://i.imgur.com/XydiQpZ.png"></p>
<p align="center"><img align="center" alt="serial monitor result " src="https://i.imgur.com/x2OePJ4.png"></p>

This results the room temperature in the form of Celsius and Fahrenheit is displayed in the serial Monitor.  
## Temperature Test Server:
Sketch that enables the NodeMCU and to monitor the current room temperature using Dallas room temperature sensor which can be displayed in a NodeMCU web Server. Scroll up to see the schematic diagram for connecting Dallas Room temperature sensor to NodeMCU.
<p align="center"><img align="center" alt="temperature server webpage " src="https://i.imgur.com/bW3GVNf.png"></p>
 
Above screen-shot is the result of the temperature test server.
## Temperature Led Control Test Server: 
Sketch that enables the NodeMCU to be monitoring the current room temperature and control the using Dallas room temperature sensor in a NodeMCU web Server. Below is the schematic diagram for connecting Dallas Room temperature sensor and LEd to NodeMCU.
<p align="center"><img align="center" alt="schematic ds18b20 led" src="https://i.imgur.com/f0I2HYw.png"></p>

As like previous sketch it displays a current room temperature in a server, with that the Led will automating the brightness based on temperature.
## Data Logging: 
This sketch interfaces Dallas Room temperature (DS18B20) to NodeMCU. By using this sensor, we can get the temperature readings for every Minute and log that temperature data into SPI Flash File System. Finally, the stored temperature data is display on the Serial Monitor.
<p align="center"><img align="center" alt="data loggin serial monitor" src="https://i.imgur.com/qVumJ2h.png?1"></p>

## Temperature Docs Log:
This Sketch interfaces the DS18B20 room temperature to NodeMCU. As a previous sketch, it also stores the temperature for every minute but in this time, we can store the temperature data into a Google Spreadsheets. We have an additional feature with this sketch i.e. we can get an email like alert mail from NodeMCU if the temperature readings beyond in our range like I put in code like (If temperature falls below 20C and rises above 45C).
<p align="center"><img align="center" alt="docs logging serial monitor" src="https://i.imgur.com/JLltn3z.png?1"></p>

## Library Links:
> [Dallas Temperature Libray](https://github.com/milesburton/Arduino-Temperature-Control-Library)

> [Temperature Data SpreadSheet Log](https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit#gid=0)

> [Schematic Diagram of The All Sketches](https://www.dropbox.com/s/3bn9ozwphsut71x/Schematic_ESP8266_20180314170549.pdf?dl=0)
 









