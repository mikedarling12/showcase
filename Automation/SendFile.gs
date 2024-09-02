function sendFilePartial() {
  var ui = SpreadsheetApp.getUi();
  // Get the row of the client whose form will be sent.
  var targetRow = ui.prompt("Select the row to send an email from:");
  if (targetRow.getSelectedButton() == ui.Button.CLOSE) {
    return;
  }
  var clientRow = targetRow.getResponseText();

  // Send file, then stamp it partially-finished.
  sendFile(clientRow, true);
  endStamp(clientRow, "Partial");
}

function sendFileComplete() {
  var ui = SpreadsheetApp.getUi();
  // Get the row of the client whose form will be sent.
  var targetRow = ui.prompt("Select the row to send an email from:");
  if (targetRow.getSelectedButton() == ui.Button.CLOSE) {
    return;
  }
  var clientRow = targetRow.getResponseText();

  // Send file, then stamp it finished.
  sendFile(clientRow);
  endStamp(clientRow, "Completed");
}

function sendFile(clientRow, partial) {
  var ui = SpreadsheetApp.getUi();

  // Get the active spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var infoSheet = ss.getSheetByName("VOB Current Month");

  // Get the fileId of the selected client and move it to the new folder.
  var fileIdCol = getCol(infoSheet.getName(), "File URL");
  var fileId = infoSheet.getRange(clientRow, fileIdCol).getValue();
  var file = SpreadsheetApp.openById(fileId);
  //var file = DriveApp.getFileById(fileId);
  var fileLink = file.getUrl();

  // Get the facility.
  var sheets = file.getSheets();
  //ui.alert(file.getName());
  //ui.alert(sheets[0].getName());
  var facilityRow = 1;
  //var facilityFolder = "";
  //switch(sheets[0].getName())
  //{
  //  case 'UMR':
  //    facilityRow = 2;
  //    facilityFolder = "Home Folder";
  //    break;
  //  case 'BCBS':
  //    facilityRow = 3;
  //    facilityFolder = "Shelley Folder";
  //    break;
  //  default:
  //    ui.alert("Correct form not found");
  //    return;
  //}
  //moveToClientFolder(fileId, facilityFolder);

  // Get the client name.
  var clientFirstNameColumn = getCol(infoSheet.getName(), "Client First Name");
  var clientLastNameColumn = getCol(infoSheet.getName(), "Client Last Name");
  var clientFirstName = infoSheet
    .getRange(clientRow, clientFirstNameColumn)
    .getValue();
  var clientLastName = infoSheet
    .getRange(clientRow, clientLastNameColumn)
    .getValue();
  var clientName = formatClientName(clientFirstName, clientLastName);

  // Get the notes on the client.
  var clientNotesColumn = getCol(infoSheet.getName(), "Email Notes");
  var clientNotes = infoSheet.getRange(clientRow, clientNotesColumn).getValue();

  // Get the recipient's email and name.
  //var facilitySheet = ss.getSheetByName("Facilities and Locations");
  var facilityColumn = getCol(infoSheet.getName(), "Facility Name");
  var facilityName = infoSheet.getRange(clientRow, facilityColumn).getValue();
  //var facilityRow = clientRow; // Change this to depend on the facility.
  //var facilityContactNameCol = getCol(facilitySheet.getName(), "Name");
  //var facilityContactName = facilitySheet.getRange(facilityRow, facilityContactNameCol).getValue();
  //var facilityContactEmailCol = getCol(facilitySheet.getName(), "Email");
  //var facilityContactEmail = facilitySheet.getRange(facilityRow, facilityContactEmailCol).getValue();

  // Send the actual email.
  //var emailTo = facilityContactEmail;
  var emailTo = "shelley@illuminatebilling.com";
  //var emailTo = "mikedarling12@gmail.com";
  var subject = "VOB " + clientName;
  var emailBody = "Hey " + facilityName + ",";
  var emailGreeting = "<p>Hey " + facilityName + ",</p>";
  var emailBody =
    "<p>Here is the VOB for " + clientName + ": " + fileLink + "</p>";
  var emailPartialMsg = "<p>***PARTIAL VOB.***<p>";
  var emailCompletedMsg = "<p>***COMPLETED VOB.***<p>";
  var emailNotesSection = "<p>" + clientNotes + "</p>";
  var emailEnd = "<p>Thank you!</p>";
  if (partial) {
    var emailContent =
      emailGreeting +
      emailBody +
      emailPartialMsg +
      emailNotesSection +
      emailEnd;
  } else {
    var emailContent =
      emailGreeting +
      emailBody +
      emailCompletedMsg +
      emailNotesSection +
      emailEnd;
  }
  //ui.alert(emailContent);
  MailApp.sendEmail({
    to: emailTo,
    subject: subject,
    htmlBody: emailContent,
  });
}

function moveToClientFolder(fileId, clientFileName) {
  // Move a file into a client folder.
  var file = DriveApp.getFileById(fileId);
  var clientFolder = DriveApp.getFoldersByName(clientFileName).next();
  file.moveTo(clientFolder);
}
