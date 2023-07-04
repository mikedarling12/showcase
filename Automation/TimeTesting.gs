function testTime() {
  var ui = SpreadsheetApp.getUi();
  var clientRow = 12;
  var timeZone = Session.getScriptTimeZone();

  // Get the spreadsheets with the necessary information.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var infoSheet = ss.getActiveSheet();
  
  // Get the time that the report was run.
  var startTimeCol = getCol(infoSheet.getName(), "Start Time");
  var startTimePreFormat = new Date(infoSheet.getRange(clientRow, startTimeCol).getValue());
  var startTimeZone = startTimePreFormat.getTimezoneOffset();
  //ui.alert(startTimeZone);
  var startTime = Utilities.formatDate(startTimePreFormat, timeZone-7, 'h:mm aaa');

  ui.alert(startTime);

  var startTimeCol = getCol(infoSheet.getName(), "Start Time");
  var startTimePreFormat = new Date(infoSheet.getRange(clientRow, startTimeCol).getValue());
  var startTime = Utilities.formatDate(startTimePreFormat, timeZone-7, 'h:mm aaa');

  ui.alert(startTime);

  // Fix the date the report was received.
  //var dateCol = getCol(infoSheet.getName(), "Date");
  //var datePreFormat = new Date(infoSheet.getRange(clientRow, dateCol).getValue());
  //var dateTimeZone = datePreFormat.getTimezoneOffset();
  //ui.alert(dateTimeZone);
  //var date = Utilities.formatDate(datePreFormat, timeZone+1, 'M/d/yyyy');
  //var secondDate = new Date(date.getTime() + 24 * 60 * 60 * 1000);
  //ui.alert(date);
  //ui.alert(Session.getScriptTimeZone());
  //ui.alert(SpreadsheetApp.getActiveSpreadsheet().getSpreadsheetTimeZone());
}
