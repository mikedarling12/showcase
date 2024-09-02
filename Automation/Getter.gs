function getName() {
  var name = SpreadsheetApp.getUi()
    .prompt("What is your name: ")
    .getResponseText();
  SpreadsheetApp.getUi().alert(name);
  return name;
}

function getCol(sheetname, keyword) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName(sheetname);
  var lastCol = ssSheet.getLastColumn();

  // Set up variables to help find the row with the client information.
  var columnFound = false;
  var column = 1;

  // Check each column along the top row for the client column.
  while (columnFound == false) {
    //SpreadsheetApp.getUi().alert(ssSheet.getRange(1, column).getValue());
    if (ssSheet.getRange(1, column).getValue() == keyword) {
      columnFound = true;
    } else {
      column++;
    }

    if (column > lastCol) {
      SpreadsheetApp.getUi().alert(keyword + " column not found.");
      columnFound = true;
    }
  }
  return column;
}

function getRow(sheetname, column, keyword) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName(sheetname);

  // Set up variables to help find the row with the client information.
  var rowFound = false;
  var row = 1;

  //SpreadsheetApp.getUi().alert("Loop Before");

  // Check each column along the top row for the client column.
  while (rowFound == false) {
    //SpreadsheetApp.getUi().alert(ssSheet.getRange(row, column).getValue());
    if (ssSheet.getRange(row, column).getValue() == keyword) {
      //SpreadsheetApp.getUi().alert("Client column found.");
      rowFound = true;
    } else {
      row++;
    }

    // If it has gone to 10, it has already passed it and should not loop into infinity.
    if (row == 100) {
      //SpreadsheetApp.getUi().alert("Client column not found.");
      columnFound = true;
    }
  }
  return row;
}

function getNowButFormatted() {
  var now = new Date();
  var currentTime = Utilities.formatDate(now, "MST", "M/d/yyyy HH:mm");
  return currentTime;
}

function test_parseContent() {
  var duplicate = parseContentForDuplicates(17, "VOB Agent", "Mike Darling");
  SpreadsheetApp.getUi().alert(duplicate);
}

function parseContentForDuplicates(clientRow, columnTag, value) {
  var ui = SpreadsheetApp.getUi();
  var ssSheet =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Current Month");
  var column = columnTag;
  var targetCol = getCol(ssSheet.getName(), column);
  var dataLocation = ssSheet.getRange(clientRow, targetCol);
  var dataSet = dataLocation.getValue();

  // Turn the data set into an array to scan through.
  var dataArray = parseToArray(dataSet);

  // Loop through the array to determine if there are duplicates.
  for (dataValue in dataArray) {
    if (dataValue == value) {
      return true;
    }
  }
  return false;
}

function parseToArray(data) {
  var dataSetString = data.toString();
  var dataArray = dataSetString.split(" | ");
  return dataArray;
}

function testClientFacility() {
  var facility = getClientFacility(2);
  console.log(facility);
}

function getClientFacility(clientRow) {
  // Get the spreadsheets with the necessary information.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var infoSheet = ss.getSheetByName("VOB Current Month");
  var facilitySheet = ss.getSheetByName("Facilities and Locations");

  var facilityColumn = getCol(infoSheet.getName(), "Facility Name");
  var facilityName = infoSheet.getRange(clientRow, facilityColumn).getValue();

  var facilityIDList = facilitySheet.getRange(4, 1, 20, 2).getValues();
  for (var row = 0; row < 20; row++) {
    if (facilityIDList[row][0] == facilityName) {
      console.log("Ding!");
      SpreadsheetApp.getUi().alert(facilityIDList[row][1]);
      return facilityIDList[row][1];
    }
  }
  return "";
  //var facilityID = facilitySheet.getRange(clientRow, facilityIDColumn).getValue();
}

function testFormatClientName() {
  console.log(formatClientName("John", "Doe"));
}

function formatClientName(clientFirstName, clientLastName) {
  var clientFirstInitial = clientFirstName.substring(0, 1);
  return clientLastName + ", " + clientFirstInitial;
}

function getFile() {
  var ui = SpreadsheetApp.getUi();
  var dApp = DriveApp;

  var targetRow = ui.prompt("Select the row to get the file from:");
  if (targetRow.getSelectedButton() == ui.Button.CLOSE) {
    return;
  }
  var clientRow = targetRow.getResponseText();

  // Get the active spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName("VOB Current Month");

  var fileIDColumn = getCol(ssSheet.getName(), "File URL");
  var fileID = ssSheet.getRange(clientRow, fileIDColumn).getValue();

  if (fileID != "") {
    var fileIDArray = parseToArray(fileID);
    fileIDArray.forEach((id) => {
      //ui.alert(id);
      ui.alert(dApp.getFileById(id).getUrl() + ".\n");
    });
  } else {
    ui.alert("This client does not have a file yet.");
  }
}

function getFilePostRun(clientRow) {
  var ui = SpreadsheetApp.getUi();
  var dApp = DriveApp;

  // Get the active spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName("VOB Current Month");

  var fileIDColumn = getCol(ssSheet.getName(), "File URL");
  var fileID = ssSheet.getRange(clientRow, fileIDColumn).getValue();

  if (fileID != "") {
    var fileIDArray = parseToArray(fileID);
    ui.alert(dApp.getFileById(fileID).getUrl() + ".\n");
  } else {
    ui.alert("This client does not have a file yet.");
  }
}
