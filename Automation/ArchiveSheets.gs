function archiveSheets() {
  // Check if it is the beginning of the year yet.
  var date = new Date();

  // If it is, archive the whole sheet. Otherwise, archive just the month.
  if (date.getMonth() === 0) {
    archiveYear();
  } else {
    archiveMonth();
  }
}

function archiveMonth() {
  var ui = SpreadsheetApp.getUi();

  // Get the current sheet.
  var activeSpreadsheet = SpreadsheetApp.getActiveSpreadsheet();
  //var activeSheet = activeSpreadsheet.getActiveSheet();
  var activeSheet = ss.getSheetByName("VOB Current Month"); // MAYBE CHANGE

  // Copy the sheet.
  var archiveSheet = activeSheet.copyTo(activeSpreadsheet);

  // Rename the new sheet and move it into position.
  archiveSheet.activate();
  activeSpreadsheet.moveActiveSheet(2); // Second position.

  // Get the new names for the sheets and set them.
  var lastMonthDate = new Date();
  lastMonthDate.setMonth(lastMonthDate.getMonth() - 1);
  var lastMonthDateFormatted = Utilities.formatDate(
    lastMonthDate,
    "MST",
    "MMMM"
  );
  var lastMonthName = "VOB " + lastMonthDateFormatted; // REVISIT
  archiveSheet.setName(lastMonthName);

  // Clean the old file to make room for new.
  activeSheet.activate();
  clearContent();
}

function archiveYear() {
  // Get the drive app up and running.
  var dApp = DriveApp;
  var ui = SpreadsheetApp.getUi();

  // Identify the two folders we are working with.
  var mainDir = dApp.getFoldersByName("Senior Project Test").next();
  var archiveDir = dApp.getFoldersByName("Archived Sheets").next();

  // Make a copy of the sheet and put it in the archive folder.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var currentFileId = ss.getId();
  var currentFileName = ss.getName();
  var currentFile = dApp.getFileById(currentFileId);
  currentFile.makeCopy(currentFileName, archiveDir);
  currentFile.setName("VOB FormDR - " + 2024);
  cleanCurrentFile();
}

function cleanCurrentFile() {
  // Get the file.
  var ui = SpreadsheetApp.getUi();
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheets = ss.getSheets();

  // Iterate through each sheet in the file.
  //sheets[0].setName("VOB January");
  var sheetName = "";
  for (var i = 0; i < sheets.length; i++) {
    var sheetName = sheets[i].getSheetName();

    // Remove all sheets except for the one that takes input and the two information files.
    if (
      sheetName != "VOB Current Month" &&
      sheetName != "VOB Agent List" &&
      sheetName != "Facility Contact Info"
    ) {
      ss.deleteSheet(sheets[i]);
    }
  }
  clearContent();
}

function clearContent() {
  // Remove all data from the current spreadsheet.
  var activeSpreadsheet =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Current Month");
  var lastCol = activeSpreadsheet.getLastColumn();
  var lastRow = activeSpreadsheet.getLastRow();
  var range = activeSpreadsheet.getRange(2, 1, lastRow - 1, lastCol);
  range.clearContent();
}
