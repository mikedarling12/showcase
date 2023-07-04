function fillTester() {
  var fileID = "1-5Chlt4dddUgEE0iMC_thZ-Bf0i9jPZWI-3MahWM3jY";
  var tab = "RTC";
  var tag = "<<PatientName>>";
  var value = "Karen";
  
  insertInForm(fileID, tag, value);
}

function insertInForm(fileID, tag, newValue) {
  var ui = SpreadsheetApp.getUi();
  var file = SpreadsheetApp.openById(fileID);
  //ui.alert(file.getName());

  var insertFile = SpreadsheetApp.openById(fileID);
  insertFile
    .createTextFinder(tag)
    .matchEntireCell(true)
    .matchCase(true)
    .matchFormulaText(false)
    .ignoreDiacritics(false)
    .replaceAllWith(newValue);
}

function testStartStamp() {
  var clientRow = 9;
  startStamp(clientRow);
}

function startStamp(clientRow) {
  var ui = SpreadsheetApp.getUi();

  // Pick out the tabs we will be using.
  // var currentSheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var usernameSheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Agent List");

  // Get the name of the user.
  var username = Session.getActiveUser();
  
  // Decode the username using the VOB Agent Sheet.
  var usernameCol = getCol(usernameSheet.getName(), "Username");
  var nameCol = getCol(usernameSheet.getName(), "Name");

  var nameLastRow = usernameSheet.getLastRow();

  var usernames = usernameSheet.getRange(1, usernameCol, nameLastRow, 1).getValues();
  var names = usernameSheet.getRange(1, nameCol, nameLastRow, 1).getValues();

  var vobAgentName = "";

  for (var i = 1; i < nameLastRow; i++) {
    var currentUsername = usernames[i];
    //ui.alert(currentUsername + " vs " + username);
    if (currentUsername.toString() == username.toString()) {
      vobAgentName = names[i];
      //ui.alert(vobAgentName);
    }
  }

  if (vobAgentName == "")
  {
    ui.alert("You are not on the list of verified agents.");
    return false;
  } else {
    stampUser(clientRow, vobAgentName);

    // Move status to partial.
    stampValue(clientRow, "Status", "Partial");

    // Paste the end time.
    var now = new Date();
    var currentTime = Utilities.formatDate(now, Session.getScriptTimeZone(), 'M/d/yyyy h:mm aaa');
    stampValue(clientRow, "Start Time", currentTime);

    return true;
  }
}

function endStamp(clientRow) {

  var ui = SpreadsheetApp.getUi();
  //var targetRow = ui.prompt("Select the row to end-stamp:");
  //var clientRow = targetRow.getResponseText();

  // Paste the end time.
  var now = new Date();
  var currentTime = Utilities.formatDate(now, 'CST', 'M/d/yyyy h:mm aaa');
  stampValue(clientRow, "End Time", currentTime);

  // Move status to completed.
  stampValue(clientRow, "Status", "Completed");
}

function stampUser(clientRow, vobAgentName) {
  // Put the user's name into the VOB slot.
  var ui = SpreadsheetApp.getUi();
  var ssSheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var agentTag = "VOB Agent";
  var agentCol = getCol(ssSheet.getName(), agentTag);
  var agentsInvolvedLocation = ssSheet.getRange(clientRow, agentCol)
  var agentsInvolved = agentsInvolvedLocation.getValue();

  // If there is already a name there, verify whether it is a new name, and include it if so.
  if (agentsInvolved != "") {
    var agentArray = agentsInvolved.split(",");
    var agentAlreadyPresent = false;
    // ADD A LOOP
    if (agentArray[0] == vobAgentName) {
      agentAlreadyPresent = true;
    }

    if (agentAlreadyPresent == false) {
      agentsInvolved = agentsInvolved + "," + vobAgentName;
      stampValue(clientRow, agentTag, agentsInvolved);
    }
  }
  // Otherwise, enter the new name into the space. 
  else {
    stampValue(clientRow, agentTag, vobAgentName);
  }
}

function stampValue(row, colTag, value) {
  // Get the spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getActiveSheet();

  // Get the location of pasting.
  var col = getCol(ssSheet.getName(), colTag);
  //SpreadsheetApp.getUi().alert("Row: " + row + " Col: " + col);
  var clientRange = ssSheet.getRange(row, col);

  // Fill the location.
  clientRange.setValue(value);
}
