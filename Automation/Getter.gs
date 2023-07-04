function getName() {
  var name = SpreadsheetApp.getUi().prompt("What is your name: ").getResponseText();
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

  //SpreadsheetApp.getUi().alert("Loop Before");

  // Check each column along the top row for the client column.
  while(columnFound == false)
  {
    //SpreadsheetApp.getUi().alert(ssSheet.getRange(1, column).getValue());
    if(ssSheet.getRange(1, column).getValue() == keyword)
    {
      columnFound = true;
    } else {
      column++;
    }

    if(column > lastCol)
    {
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
  while(rowFound == false)
  {
    //SpreadsheetApp.getUi().alert(ssSheet.getRange(row, column).getValue());
    if(ssSheet.getRange(row, column).getValue() == keyword)
    {
      //SpreadsheetApp.getUi().alert("Client column found.");
      rowFound = true;
    } else {
      row++;
    }

    // If it has gone to 10, it has already passed it and should not loop into infinity.
    if(row == 100)
    {
      //SpreadsheetApp.getUi().alert("Client column not found.");
      columnFound = true;
    }
  }
  return row;
}
