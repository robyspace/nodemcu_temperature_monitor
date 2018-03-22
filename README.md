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
This Sketch interfaces the DS18B20 room temperature to NodeMCU. As a previous sketch, it also stores the temperature for every minute but in this time, we can store the temperature data into a Google Spreadsheets. We have an additional feature with this sketch i.e. we can get an email like `Alert Mail` from NodeMCU if the temperature readings beyond in our range like I put in code like (If temperature falls below 20C and rises above 45C).
<p align="center"><img align="center" alt="docs logging serial monitor" src="https://i.imgur.com/JLltn3z.png?1"></p>

In order to recieve sensor data and post it to Google spreadsheets use google script editor. See the description for how I have done.
* ## Steps to Follow for Sending Data to Spread Sheets
    - Go through with this link [Spreadsheets link](https://docs.google.com/spreadsheets/) and sign in with your gmail account.
    - Create a new spreadsheet. Default name should be Untitled Spreadsheet, change it if you want.
   	- Here I want two columns one is for date and another one is for temperature data, you can add if you want more.
   	- Now the spread sheet is ready, in order to send the data you just write a code to send data to spreadsheets.
   	- Goto Tools -> Script Editor (It redirected another page).
   	- In that page we can find 'code.gs', this is the name of your script file. 
   	- Copy that code in this link [Google script code]().
   	- Read the code and make some changes if you want.
   	- Make sure the parameters (In switch case you can find 'temperature' that should be match with spreadsheets column name) and             row numbers must be same .
    - This changes should be fine for sending data.
    
* Here we add a additional feature called `Alert Mail`. In the same code you can a send a mail. Here you go, how to send a notification mail from spread sheets.
    - Enter your mail Id in toEmail field.
    ```sh
    var toEmail = "saikrishnakoniki@gmail.com";
    ```
    - Enter Subject and Messages like (I used low alert message and high alert message based on the temperature values).
    ```sh
    var subject = "Re: Alert from NodeMCU" ;
  // Low alert message Body
  var lowalert = "<html><body><p>Dear User,<br>&nbsp;&nbsp;&nbsp;&nbsp;Greetings of the day. We are informing you about that your room temperature is Critically LOW. Please check your room once. You can also check the previous room temperature reading by clicking the below link.<br><a href = \"https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing\" >https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing</a><br><br><p>Thank you.</p><br><br><br><p>\n\n\nSincerely,</p><p>\n<b>Vistronics Design Solutions</b>\n</p><p>10B Chowdary nagar,</p><p>\nValasaravakkam,</p><p>\nChennai, Tamilnadu.</p></p>\n</body></html>";
  // High Alert message body.
  var highalert = "<html><body><p>Dear User,<br>&nbsp;&nbsp;&nbsp;&nbsp;Greetings of the day. We are informing you about that your room temperature is Critically HIGH. Please check your room once. You can also check the previous room temperature reading by clicking the below link.<br><a href = \"https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing\">https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing</a><br><br><p>Thank you.</p><br><br><br><p>\n\n\nSincerely,</p><p>\n<b>Vistronics Design Solutions</b>\n</p><p>10B Chowdary nagar,</p><p>\nValasaravakkam,</p><p>\nChennai, Tamilnadu.</p></p>\n</body></html>";
  
    - Edit the range whaterver you want like (I'm using less than 20 Degrees and greater than 45 Degrees temperature).
    - With sendEmail function, you can get the mail when the temperature falls into 20Degrees and rises beyond 45 Degrees.
   ```  
## Important Links:
> [Dallas Temperature Libray](https://github.com/milesburton/Arduino-Temperature-Control-Library)

> [Temperature Data SpreadSheet Log](https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit#gid=0)

> [Schematic Diagram of The All Sketches](https://www.dropbox.com/s/3bn9ozwphsut71x/Schematic_ESP8266_20180314170549.pdf?dl=0)
 









