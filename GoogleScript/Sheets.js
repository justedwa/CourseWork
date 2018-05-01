//JS for handling HTTP GET requests
function doGet(e){
  Logger.log("--- doGet ---");
 
 var gear = "",
     speed = "",
     accel = "",
     hr = " ",
     time = "",
     lean = "",
     coord = "",
     temp = "",
     ip = "",
     crash = "",
     humidity = "";
 
  try {
    ip = e.parameters.ip
    gear = e.parameters.gear;
    speed = e.parameters.speed;
    accel = e.parameters.accel;
    hr = e.parameters.hr;
    lean = e.parameters.lean;
    coord = e.parameters.coord;
    temp = e.parameters.temp;
    humidity = e.parameters.humidity;
    crash = e.parameters.crash;
 
    // save the data to spreadsheet
    save_data(crash,ip,gear,speed,accel,hr,lean,coord,temp,humidity);
 
 
    return ContentService.createTextOutput("Wrote: " + coord + "\n");
 
  } catch(error) { 
    Logger.log(error);    
    return ContentService.createTextOutput("oops...." + error.message);
  }  
}
 
// function to save given data to a sheet
function save_data(crash,ip,gear,speed,accel,hr,lean,coord,temp,humidity){
  Logger.log("--- save_data ---");
  try {
    
    var dateTime = new Date(); //converts dateTime into HH:MM:SS
    var h = dateTime.getHours();
    var m = dateTime.getMinutes();
    var s = dateTime.getSeconds();
    var Time = h + ":" + m + ":" + s; 
    var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/133kQ1j7DzuQqwB1qQaJ6_CxGGWuO7n-13wlPG-eaNg4/edit");
    var summarySheet = ss.getSheetByName("Summary");
    var dataLoggerSheet = ss.getSheetByName("DataLogger");
    var prevCrash = dataLoggerSheet.getRange("J" + 3).getValue();
    if(crash == 1 && prevCrash != 1){
      MailApp.sendEmail("2197418303@vtext.com","CRASH","Crash at:" + coord);
    }
    // Get last edited row from DataLogger sheet
    var row = dataLoggerSheet.getLastRow() + 1;
 
 
    // Start Populating the data
    dataLoggerSheet.getRange("G" + row).setValue(gear); // ID
    dataLoggerSheet.getRange("B" + row).setValue(speed); // dateTime
    dataLoggerSheet.getRange("C" + row).setValue(accel); // tag
    dataLoggerSheet.getRange("D" + row).setValue(hr); // value
    dataLoggerSheet.getRange("E" + row).setValue(Time); // value
    dataLoggerSheet.getRange("F" + row).setValue(lean);
    dataLoggerSheet.getRange("A" + row).setValue(coord);
    dataLoggerSheet.getRange("H" + row).setValue(temp);
    dataLoggerSheet.getRange("I" + row).setValue(humidity);
    dataLoggerSheet.getRange("J" + 2).setValue(ip);
    dataLoggerSheet.getRange("J" + 3).setValue(crash);
 
    // Update summary sheet
    summarySheet.getRange("B1").setValue(dateTime); // Last modified date
  }
 
  catch(error) {
    Logger.log(JSON.stringify(error));
  }
 
  Logger.log("--- save_data end---"); 
}