function sendFileComplete() {
  // Get the row of the client whose form will be sent.
  var ui = SpreadsheetApp.getUi();
  var targetRow = ui.prompt("Select the row to be templated:");
  var clientRow = targetRow.getResponseText();

  // Get the active spreadsheet.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var infoSheet = ss.getActiveSheet();

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
  var facilityFolder = "";
  switch(sheets[0].getName())
  {
    case 'RTC':
      facilityRow = 2;
      facilityFolder = "Home Folder";
      break;
    case 'Detox VOB':
      facilityRow = 3;
      facilityFolder = "Shelley Folder";
      break;
  }
  moveToClientFolder(fileId, facilityFolder);
  
  // Get the client name.
  var clientFirstNameColumn = getCol(infoSheet.getName(), "First Name");
  var clientLastNameColumn = getCol(infoSheet.getName(), "Last Name");
  var clientFirstName = infoSheet.getRange(clientRow, clientFirstNameColumn).getValue();
  var clientLastName = infoSheet.getRange(clientRow, clientLastNameColumn).getValue();
  var clientName = clientLastName + ", " + clientFirstName;

  // Get the notes on the client.
  var clientNotesColumn = getCol(infoSheet.getName(), "Notes");
  var clientNotes = infoSheet.getRange(clientRow, clientNotesColumn).getValue();

  // Get the recipient's email and name.
  var facilitySheet = ss.getSheetByName("Facility Contact Info");
  //var facilityRow = 2; // Change this to depend on the facility.
  var facilityContactNameCol = getCol(facilitySheet.getName(), "Name");
  var facilityContactName = facilitySheet.getRange(facilityRow, facilityContactNameCol).getValue();
  var facilityContactEmailCol = getCol(facilitySheet.getName(), "Email");
  var facilityContactEmail = facilitySheet.getRange(facilityRow, facilityContactEmailCol).getValue();

  // Send the actual email.
  var emailTo = facilityContactEmail;
  var subject = 'VOB ' + clientName;
  //var emailBody = 'Hey ' + facilityContactName + ",";
  var emailGreeting = '<p>Hey ' + facilityContactName + ',</p>';
  var emailBody = '<p>Here is the VOB for ' + clientName + ': ' + fileLink + '</p>';
  var emailNotesSection = '<p>' + clientNotes + '</p>';
  var emailEnd = '<p>Thank you!</p>';
  var emailContent = emailGreeting + emailBody + emailNotesSection + emailEnd;
  MailApp.sendEmail({
    to:emailTo,
    subject:subject,
    htmlBody:emailContent
  })

  endStamp(clientRow);
}

function moveToClientFolder(fileId, clientFileName) {
  // Move a file into a client folder.
  var file = DriveApp.getFileById(fileId);
  var clientFolder = DriveApp.getFoldersByName(clientFileName).next();
  file.moveTo(clientFolder);
}
