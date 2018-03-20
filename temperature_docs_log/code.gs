var toEmail = "your_email@gmail.com";

function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var value=0;
  var email = Session.getActiveUser().getEmail();
  var subject = "Re: Alert from NodeMCU" ;
  var lowalert = "<html><body><p>Dear User,<br>&nbsp;&nbsp;&nbsp;&nbsp;Greetings of the day. We are informing you about that your room temperature is Critically LOW. Please check your room once. You can also check the previous room temperature reading by clicking the below link.<br><a href = \"https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing\" >https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing</a><br><br><p>Thank you.</p><br><br><br><p>\n\n\nSincerely,</p><p>\n<b>NodeMCU</b>\n</p><p>Arduino Platform,</p><p>\nChennai, Tamilnadu.</p></p>\n</body></html>";
  var highalert = "<html><body><p>Dear User,<br>&nbsp;&nbsp;&nbsp;&nbsp;Greetings of the day. We are informing you about that your room temperature is Critically HIGH. Please check your room once. You can also check the previous room temperature reading by clicking the below link.<br><a href = \"https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing\">https://docs.google.com/spreadsheets/d/1Dl0MbdmU-8bJiwInfa-9JfYPznRQXIQipkoTqbeHMNU/edit?usp=sharing</a><br><br><p>Thank you.</p><br><br><br><p>\n\n\nSincerely,</p><p>\n<b>NodeMCU</b>\n</p><p>Arduino Platform,</p><p>\nChennai, Tamilnadu.</p></p>\n</body></html>";
  
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = 'Spread_Sheet_ID'; 		// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();		// get Active sheet
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    rowData[0] = new Date(); 											// Timestamp in column A
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'temperature': //Parameter
          rowData[1] = value; //Value in column B
          result = 'Written on column B';
          break;
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  
  // Return result of operation
  
  if(value<20)
  {
    sendEmail(email,lowalert,subject);
    result += "\nlow alert sent";
  }
  else if (value>45)
  {
    sendEmail(email,highalert,subject);
       result += "\nhigh alert sent";
  }
  return ContentService.createTextOutput(result);
}
/**
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}

function sendEmail(address,message,sub)
{
   MailApp.sendEmail({
          "to": address,
     "subject": sub,
    "htmlBody": message      
   });
 
  Logger.log("send_textMessage: " + "Email sent to: " + address);
}
