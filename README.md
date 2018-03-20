# nodemcu_temperature_monitor

Collection of Arduino sketches written for the NodeMCU. The links of the libraries are used in those sketches are given below. These all sketches are depending on Dallas Temperature Sensor (DS18B20).

## Temperature test: 
Sketch that enables the NodeMCU to monitor the current room temperature using Dallas room temperature sensor and display it on a Serial Monitor. Below is the schematic diagram for connecting Dallas room temperature to NodeMCU. 
<img align="center" src="https://i.imgur.com/XydiQpZ.png">
<img align="center" src="https://i.imgur.com/x2OePJ4.png">

This results the room temperature in the form of Celsius and Fahrenheit is displayed in the serial Monitor.  
## Temperature Test Server:
Sketch that enables the NodeMCU and to monitor the current room temperature using Dallas room temperature sensor which can be displayed in a NodeMCU web Server. Scroll up to see the schematic diagram for connecting Dallas Room temperature sensor to NodeMCU.

 

Above screen-shot is the result of the temperature test server.
Temperature Led Control Test Server: 
 Sketch that enables the NodeMCU to be monitoring the current room temperature and control the using Dallas room temperature sensor in a NodeMCU web Server. Scroll up to see the schematic diagram for connecting Dallas Room temperature sensor to NodeMCU.
As like previous sketch it displays a current room temperature in a server, with that the Led will automating the brightness based on temperature.
Data Logging: 
This sketch interfaces Dallas Room temperature (DS18B20) to NodeMCU. By using this sensor, we can get the temperature readings for every Minute and log that temperature data into SPI Flash File System. Finally, we can display the temperature data which stored in a flash file.
Temperature Docs Log:
This Sketch interfaces the DS18B20 room temperature to NodeMCU. As a previous sketch, it also stores the temperature for every minute but in this time, we can store the temperature data into a Google Spreadsheets. We have an additional feature with this sketch i.e. we can get an email like alert mail from NodeMCU if the temperature readings beyond in our range like I put in code like (If temperature falls below 20C and rises above 45C).
 









