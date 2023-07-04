function archiveMonth() {
  var ui = SpreadsheetApp.getUi();

  // Get the current sheet.
  var activeSpreadsheet = SpreadsheetApp.getActiveSpreadsheet();
  var primarySheet = activeSpreadsheet.getActiveSheet();

  // Copy the sheet.
  var archiveSheet = primarySheet.copyTo(activeSpreadsheet);

  // Rename the new sheet and move it into position.
  archiveSheet.activate();
  activeSpreadsheet.moveActiveSheet(2); // Second position.

  // Get the new names for the sheets and set them.
  var archiveSheetName = primarySheet.getName();
  var newMonthDate = new Date();
  var newMonthDateFormatted = Utilities.formatDate(newMonthDate, Session.getScriptTimeZone(), 'MMMM yyyy');
  var newMonthName = "VOB " + newMonthDateFormatted;
  primarySheet.setName(newMonthName);
  archiveSheet.setName(archiveSheetName);

  // Clean the old file to make room for new 
  primarySheet.activate();
  var lastCol = activeSpreadsheet.getLastColumn();
  var lastRow = activeSpreadsheet.getLastRow();
  var range = primarySheet.getRange(2,1,lastRow - 1,lastCol);
  range.clearContent();
}
