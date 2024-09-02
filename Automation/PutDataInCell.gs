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

function test_logHours() {
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "record-claim",
    "Mike",
    2,
    "Now"
  );
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "record-claim",
    "Mike",
    3,
    "Now"
  );
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "record-claim",
    "Mike",
    2,
    "Now"
  );
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "modify-start",
    "Mike",
    3,
    "Then"
  );
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "modify-end",
    "Mike",
    2,
    "Then"
  );
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "end-time",
    "Mike",
    2,
    "Then"
  );
}

function logHours(fileID, logType, vobAgent, clientRow, timestamp) {
  var ui = SpreadsheetApp.getUi();
  var file = SpreadsheetApp.openById(fileID);
  //var file = SpreadsheetApp.openById(fileID);
  //VOB Time Metric from Tracker
  console.log(file.getName());

  var insertFile = SpreadsheetApp.openById(fileID);
  var timeLog = insertFile.getSheetByName("Sheet1");

  vobAgent = vobAgent.toString();

  // If the logType is record-claim, add a new row to the data for it.
  if (logType == "record-claim") {
    //ui.alert(vobAgent);
    //ui.alert(clientRow);
    //ui.alert(timestamp);
    timeLog.appendRow([vobAgent, clientRow, timestamp]);
  }

  // If the logType isn't for a record claim, find the row to modify.
  else {
    var valueRange = timeLog.getDataRange().getValues();
    var rowToModify = 2;
    var currentRow = 0;
    valueRange.forEach(function (row) {
      if (row[0] == vobAgent && row[1] == clientRow) {
        rowToModify = currentRow;
        console.log(rowToModify);
      }
      currentRow++;
    });

    // Put the time stamp in the correct row.
    if (logType == "start-time") {
      timeLog.getRange(rowToModify + 1, 3).setValue(timestamp);
    } else if (logType == "end-time") {
      timeLog.getRange(rowToModify + 1, 4).setValue(timestamp);
    } else if (logType == "modify-start") {
      timeLog.getRange(rowToModify + 1, 5).setValue(timestamp);
    } else if (logType == "modify-end") {
      timeLog.getRange(rowToModify + 1, 6).setValue(timestamp);
    } else {
      ui.alert("A typo was present in this feature. Please contact support.");
    }
  }
}

function claimRecord() {
  // Get the desired row from the agent.
  var ui = SpreadsheetApp.getUi();
  var clientRow = ui.prompt("Select the row to claim:").getResponseText();

  // Get the time and name of the agent.
  var currentTime = getNowButFormatted();
  var vobAgentName = decodeUsername(parseUsername());

  // Record the claiming and when it happened.
  stampCumulative(clientRow, "VOB Agent", vobAgentName);
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "record-claim",
    vobAgentName,
    clientRow,
    currentTime
  );
  stampValue(clientRow, "Status", "Claimed");
}

function testStartStamp() {
  var clientRow = 9;
  startStamp(clientRow);
  //stampValue(clientRow, "Status", "Claimed");
}

function startStamp(clientRow) {
  var ui = SpreadsheetApp.getUi();

  // Pick out the tabs we will be using.
  // var currentSheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();

  // Get the email domain of the user.
  //var username = parseUsername();

  // If the name came back blank, it was from an invalid domain, so reject it.
  //if (username == "") {
  //  ui.alert("Error: User email not on company domain.");
  //  return false;
  //}

  // Decode the user's username using the sheet.
  var vobAgentName = "Shelley M";
  //var vobAgentName = decodeUsername(username);

  // If you cannot find the agent, deny them access.
  if (vobAgentName == "") {
    ui.alert(
      "Your email has not yet been registered in the system. Please contact the Spreadsheet Admin."
    );
    return false;
  } else {
    stampCumulative(clientRow, "VOB Agent", vobAgentName);

    // Move status to needs more info.
    stampValue(clientRow, "Status", "Claimed");

    // Get what times have been logged so far.
    var ssSheet =
      SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Current Month");
    //var timeCol = getCol(ssSheet.getName(), "Start Time");
    //var timeLocation = ssSheet.getRange(clientRow, timeCol);
    //var timesSoFar = timeLocation.getValue();

    // Get the current time.
    var currentTime = getNowButFormatted();

    logHours(
      "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
      "start-time",
      vobAgentName,
      clientRow,
      currentTime
    );

    return true;
  }
}

function endStamp(clientRow, status) {
  var ui = SpreadsheetApp.getUi();
  var usernameSheet =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Agent List");

  // Paste the end time.
  var currentTime = getNowButFormatted();
  logHours(
    "1TIOPrvYiU-eoiyd5jzkirr639YG0Fse_Ybf1RzsXyko",
    "end-time",
    vobAgentName,
    clientRow,
    currentTime
  );

  // Record the person who touched it.
  var username = parseUsername();

  // If the name came back blank, it was from an invalid domain, so reject it.
  if (username == "") {
    ui.alert("Error: User email not on company domain.");
    return false;
  }

  // Decode the user's username using the sheet.
  var vobAgentName = decodeUsername(username);

  // If you cannot find the agent, deny them access.
  if (vobAgentName == "") {
    ui.alert(
      "Your email has not yet been registered in the system. Please contact the Spreadsheet Admin."
    );
    return false;
  } else {
    // Move status to completed.
    stampValue(clientRow, "Status", status);

    return true;
  }
}

function parseUsername() {
  // Get the username of the current operator.
  var username = Session.getActiveUser();

  // Get the domain of the email.
  var usernameParts = username.toString().split("@");
  var emailDomain = usernameParts[1];

  // If the email is valid, it passes the test.
  if (emailDomain == "illuminatebilling.com") {
    //if (emailDomain == "gmail.com") {
    return usernameParts[0];
  } else {
    return "";
  }
}

function decodeUsername(username) {
  var ui = SpreadsheetApp.getUi();

  var usernameSheet =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Agent List");

  // Decode the username using the VOB Agent Sheet.
  var usernameCol = getCol(usernameSheet.getName(), "Username");
  var nameCol = getCol(usernameSheet.getName(), "Name");

  // Set the range we will search in for the VOB Agent.
  var nameLastRow = usernameSheet.getLastRow();
  var usernames = usernameSheet
    .getRange(1, usernameCol, nameLastRow, 1)
    .getValues();
  var names = usernameSheet.getRange(1, nameCol, nameLastRow, 1).getValues();

  // Loop through the agents till you find them.
  var vobAgentName = "";
  for (var i = 1; i < nameLastRow; i++) {
    var currentUsername = usernames[i];
    if (currentUsername.toString() == username.toString()) {
      vobAgentName = names[i];
    }
  }
  return vobAgentName;
}

function stampCumulative(clientRow, columnTag, value) {
  // Put record into the VOB slot, adding to the list if there is already data there.
  var ui = SpreadsheetApp.getUi();
  var ssSheet =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Current Month");
  var column = columnTag;
  var targetCol = getCol(ssSheet.getName(), column);
  var dataLocation = ssSheet.getRange(clientRow, targetCol);
  var dataSet = dataLocation.getValue();

  // See if the value is already there.
  if (!parseContentForDuplicates(clientRow, columnTag, value)) {
    // If there is already a value there, add it to the list.
    if (dataSet != "") {
      dataSet = dataSet + " | " + value;
    }

    // Otherwise, start a new list.
    else {
      dataSet = value;
    }

    // Put the list back in the cell.
    stampValue(clientRow, column, dataSet);
  }
}

function stampValue(row, colTag, value, category) {
  // Get the spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName("VOB Current Month");

  // Get the location of pasting.
  // Categories help prevent similarly-named columns from being mistaken as each other.
  if (category == "FacilityInfo") {
  } else if (category == "Patient Info") {
  } else if (category == "Insurance Info") {
  } else {
    var col = getCol(ssSheet.getName(), colTag);
    //SpreadsheetApp.getUi().alert("Row: " + row + " Col: " + col);
    var clientRange = ssSheet.getRange(row, col);

    // Fill the location.
    clientRange.setValue(value);
  }
}

function markAsRerun(clientRow) {
  // Get the spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName("VOB Current Month");

  // Get the Checkbox Cell.
  var rerunCol = getCol(ssSheet.getName(), "Rerun");
  var rerunCheckbox = ssSheet.getRange(clientRow, rerunCol);

  if (!rerunCheckbox.isChecked()) {
    rerunCheckbox.check();
  }
}
