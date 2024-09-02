function newFile() {
  //
  // INITIAL INFORMATION
  //

  // Get the name of the user for records.
  // var username = getName();

  // Get the row of the client whose info will be templated.
  var ui = SpreadsheetApp.getUi();
  var targetRow = ui.prompt("Select the row to be templated:");
  if (targetRow.getSelectedButton() == ui.Button.CLOSE) {
    return;
  }
  var clientRow = targetRow.getResponseText();
  startStamp(clientRow);
  var validAgent = true;
  //var validAgent = startStamp(clientRow);
  if (validAgent) {
    // Get the active spreadsheet.
    var ss = SpreadsheetApp.getActiveSpreadsheet();
    var ssSheet = ss.getSheetByName("VOB Current Month");

    // Get the time that the report was run.
    //var startTimeCol = getCol(ssSheet.getName(), "Start Time");
    var startTimePreFormat = new Date(getNowButFormatted());
    //var startTimePreFormat = new Date(ssSheet.getRange(clientRow, startTimeCol).getValue());
    var startDate = Utilities.formatDate(startTimePreFormat, "MST", "M.d.yyyy");
    //var startDate = startTimePreFormat;

    // Get the column of the client name.
    var clientFirstNameColumn = getCol(ssSheet.getName(), "Client First Name");
    var clientLastNameColumn = getCol(ssSheet.getName(), "Client Last Name");

    // Finally, get the client name.
    var clientFirstName = ssSheet
      .getRange(clientRow, clientFirstNameColumn)
      .getValue();
    var clientLastName = ssSheet
      .getRange(clientRow, clientLastNameColumn)
      .getValue();
    var clientName = clientLastName + ", " + clientFirstName;

    // Ensure the user chose the correct client.
    var proceed = ui.alert(
      "The selected client is " + clientName + ". Is this correct?",
      ui.ButtonSet.YES_NO
    );

    // Display message based on input.
    if (proceed == ui.Button.YES) {
      // Get insurance provider name.
      var insuranceCol = getCol(ssSheet.getName(), "Insurance Provider");
      var insuranceName = ssSheet.getRange(clientRow, insuranceCol).getValue();

      //
      // CHECK FOR EXISTING DOCUMENTS
      //

      var fileIDColumn = getCol(ssSheet.getName(), "File URL");
      var fileID = ssSheet.getRange(clientRow, fileIDColumn).getValue();

      // Get the drive app up and running.
      var dApp = DriveApp;

      // If a form already exists for this transaction...
      if (fileID != "") {
        // Split up all the ids and put them in an array.
        var fileIDArray = parseToArray(fileID);

        // Take the IDs and make a string of their urls to display to the agent.
        var existingFileMessage =
          clientName + " already has a document at this address: \n\n";
        for (var i = 0; i < fileIDArray.length; i++) {
          existingFileMessage =
            existingFileMessage +
            dApp.getFileById(fileIDArray[i]).getUrl() +
            ".\n";
        }
        existingFileMessage =
          existingFileMessage + "\nWould you like to still create a new form?";

        var proceedWithNewFile = ui.alert(
          "Existing Form",
          existingFileMessage,
          ui.ButtonSet.YES_NO
        );

        //var proceedWithNewFile = ui.prompt("Existing Form", clientName + " already has a document at this address: \n" + fileURL + ".\n Would you like to still create a new form?", ui.ButtonSet.YES_NO);

        // End the proccess if they did not intend to run the program.
        if (
          proceedWithNewFile == ui.Button.CLOSE ||
          proceedWithNewFile == ui.Button.NO
        ) {
          ui.alert("Operation Cancelled.");
          return;
        }
        markAsRerun(clientRow);
      }

      // Otherwise, proceed and make a new form.
      //ui.alert("No URL yet.");

      //
      // ACTUALLY MAKING THE FILE
      //

      // Identify the two folders we are working with.
      var mainDir = dApp.getFoldersByName("Senior Project Test");
      var mainIter = mainDir.next();
      var mainFiles = mainIter.getFiles();

      //ui.alert("Main files found");

      // Where the templates will be coming from.
      var templateID = getClientFacility(clientRow);
      var template = dApp.getFileById(templateID);
      //var templatesFolder = dApp.getFoldersByName("Template Docs").next();
      //var templates = templatesFolder.getFiles();
      //var templateFile = "Template Master VOB";

      //ui.alert("Template files found");

      // Where the new documents will go.
      var newDocFolder = dApp
        .getFoldersByName("2023 VOB Response Folder")
        .next();
      //ui.alert("newDocFolder found");
      //var newDocFolder = dApp.getFoldersByName("Created Docs").next();

      // Create variable names to help us determine whether the file was found or not.
      //var found = true;
      //var copiedFileName = "";

      //ui.alert("Before template iteration");

      // Make a copy of the template and put it in the new directory.
      //copiedFileName = "Copy of " + template.getName();
      var newFile = template.makeCopy(newDocFolder);
      var newFileID = newFile.getId();

      // Loop through each file in the main directory, then copy a file if it is found.
      //while(templates.hasNext())
      //{
      //  var file = templates.next();
      //  var filename = file.getName();
      //ui.alert(filename + " was checked!");

      //  if(filename == templateFile)
      //  {
      //    found = true;
      //    file.makeCopy(newDocFolder);
      //    copiedFileName = "Copy of " + filename;
      //  }
      //}

      //ui.alert("After template iteration");

      //var newFileId = "";

      //if(found == false)
      //{
      //  ui.alert(templateFile + " was not found!");
      //}else{

      var newFileName = "VOB " + clientName + " - " + startDate;
      newFile.setName(newFileName);
      //var fileRenamed = false;
      //var copyFiles = newDocFolder.getFiles();

      //ui.alert("Before copy found");

      // Go until the new file is found.
      //while(copyFiles.hasNext()) {
      //  var file = copyFiles.next();
      //  var filename = file.getName();

      //  if(filename == copiedFileName)
      //  {
      //    file.setName(newFileName);
      //    fileRenamed == true;
      //    newFileId = file.getId();
      stampCumulative(clientRow, "File URL", newFileID);
      //  }
      //}
      //ui.alert("After copy found");

      fillFile(newFileID, clientRow, startDate);
      //}
    }
  }
}

function testFileFill() {
  var newFileName = "[AutoCrat Preview] Test Document for Karen Hill";
  var clientRow = 9;
  var clientColumn = 5;
  fillFile(newFileName, clientRow, clientColumn);
}

function fillFile(newFileId, clientRow, startDate) {
  var ui = SpreadsheetApp.getUi();

  // Get the spreadsheets with the necessary information.
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var infoSheet = ss.getSheetByName("VOB Current Month");

  //************************************************************************************************************
  // GET ALL IMPORTANT INFORMATION
  //************************************************************************************************************

  var timeZone = Session.getScriptTimeZone();

  // Get the date the report was received.
  //var dateReceivedCol = getCol(infoSheet.getName(), "Date");
  //var dateReceivedPreFormat = new Date(infoSheet.getRange(clientRow, dateReceivedCol).getValue());
  //var dateReceived = Utilities.formatDate(dateReceivedPreFormat, timeZone+1, 'M/d/yyyy');

  // Get the VOB Agent name.
  var vobAgentCol = getCol(infoSheet.getName(), "VOB Agent");
  var vobAgent = infoSheet.getRange(clientRow, vobAgentCol).getValue();

  // Get the time that the report was run.
  //var startTimeCol = getCol(infoSheet.getName(), "Start Time");
  //var startTimePreFormat = new Date(infoSheet.getRange(clientRow, startTimeCol).getValue());
  //var startTime = Utilities.formatDate(startTimePreFormat, timeZone-7, 'M/d/yyyy h:mm aaa');
  var startTime = getNowButFormatted();

  // Get the client name.
  var clientFirstNameColumn = getCol(infoSheet.getName(), "Client First Name");
  var clientLastNameColumn = getCol(infoSheet.getName(), "Client Last Name");
  var clientFirstName = infoSheet
    .getRange(clientRow, clientFirstNameColumn)
    .getValue();
  var clientLastName = infoSheet
    .getRange(clientRow, clientLastNameColumn)
    .getValue();
  var clientName = clientFirstName + " " + clientLastName;

  // Get client date of birth.
  var clientDOBCol = getCol(infoSheet.getName(), "Patient date of birth");
  var clientDOBPreFormat = new Date(
    infoSheet.getRange(clientRow, clientDOBCol).getValue()
  );
  var clientDOB = Utilities.formatDate(
    clientDOBPreFormat,
    timeZone + 1,
    "M/d/yyyy"
  );

  // Get last four digits of client social.
  var clientSSNCol = getCol(infoSheet.getName(), "Client last 4 digits of SSN");
  var clientSSN = infoSheet.getRange(clientRow, clientSSNCol).getValue();

  // Get client phone number.
  var clientExistingCol = getCol(
    infoSheet.getName(),
    "Is this an EXISTING client with NEW insurance?"
  );
  var clientExisting = infoSheet
    .getRange(clientRow, clientExistingCol)
    .getValue();

  // Get the client address.
  var clientStreetAddressCol = getCol(
    infoSheet.getName(),
    "Client Street Address"
  );
  var clientStreetAddress = infoSheet
    .getRange(clientRow, clientStreetAddressCol)
    .getValue();
  var clientCityCol = getCol(infoSheet.getName(), "Client City");
  var clientCity = infoSheet.getRange(clientRow, clientCityCol).getValue();
  var clientStateCol = getCol(infoSheet.getName(), "Client State/Province");
  var clientState = infoSheet.getRange(clientRow, clientStateCol).getValue();
  var clientZipCol = getCol(infoSheet.getName(), "Client ZIP");
  var clientZip = infoSheet.getRange(clientRow, clientZipCol).getValue();
  var clientFullAddress =
    clientStreetAddress +
    " " +
    clientCity +
    " " +
    clientState +
    " " +
    clientZip;

  // Get client phone number.
  var clientPhoneNumCol = getCol(infoSheet.getName(), "Patient phone number");
  var clientPhoneNum = infoSheet
    .getRange(clientRow, clientPhoneNumCol)
    .getValue();

  // Get the policy holder name.
  var policyHolderFirstNameColumn = getCol(
    infoSheet.getName(),
    "First Name of Policy Holder"
  );
  var policyHolderLastNameColumn = getCol(
    infoSheet.getName(),
    "Last Name of Policy Holder"
  );
  var policyHolderFirstName = infoSheet
    .getRange(clientRow, policyHolderFirstNameColumn)
    .getValue();
  var policyHolderLastName = infoSheet
    .getRange(clientRow, policyHolderLastNameColumn)
    .getValue();
  var policyHolderName = policyHolderFirstName + " " + policyHolderLastName;

  // Get the policy holder date of birth.
  var policyHolderDOBCol = getCol(
    infoSheet.getName(),
    "Policy Holder's Date of Birth"
  );
  var policyHolderDOBPreFormat = new Date(
    infoSheet.getRange(clientRow, policyHolderDOBCol).getValue()
  );
  var policyHolderDOB = Utilities.formatDate(
    policyHolderDOBPreFormat,
    timeZone + 1,
    "M/d/yyyy"
  );

  // Get the client's relationship to the policy holder.
  var policyHolderRelationCol = getCol(
    infoSheet.getName(),
    "Client's relationship to policy holder"
  );
  var policyHolderRelation = infoSheet
    .getRange(clientRow, policyHolderRelationCol)
    .getValue();

  // Get the insurance name.
  var insuranceNameCol = getCol(infoSheet.getName(), "Insurance Provider");
  var insuranceName = infoSheet
    .getRange(clientRow, insuranceNameCol)
    .getValue();

  // DO A LOOP TO GET THE INSURANCE NAME
  //var insuranceRow = 1;

  // Get the insurance number.
  var insurancePhoneNumCol = getCol(
    infoSheet.getName(),
    "Insurance Provider Phone"
  );
  var insurancePhone = infoSheet
    .getRange(clientRow, insurancePhoneNumCol)
    .getValue();
  //var insurancePhone = "";
  //if (providedNumberPresent) {
  //  insurancePhone = "Primary Number: " + infoSheet.getRange(clientRow, insurancePhoneNumCol).getValue() + " Provided Number: " + providedNumber;
  //} else {
  //  insurancePhone = "Primary Number: " + infoSheet.getRange(clientRow, insurancePhoneNumCol).getValue();
  //}

  // Get the MedID
  var insuranceMedIDCol = getCol(infoSheet.getName(), "Client Insurance ID");
  var insuranceMedID = infoSheet
    .getRange(clientRow, insuranceMedIDCol)
    .getValue();

  //************************************************************************************************************
  // FILL THE SHEET
  //************************************************************************************************************
  //ui.alert(newFileId);
  insertInForm(newFileId, "<<Datetime>>", startTime);
  insertInForm(newFileId, "<<VOBAgent>>", vobAgent);
  //insertInForm(newFileId, "<<Now>>", startTime);
  insertInForm(newFileId, "<<PatientName>>", clientName);
  insertInForm(newFileId, "<<PatientDOB>>", clientDOB);
  insertInForm(newFileId, "<<PatientSSN>>", clientSSN);
  insertInForm(newFileId, "<<Existing>>", clientExisting);
  insertInForm(newFileId, "<<PatientAddress>>", clientFullAddress);
  insertInForm(newFileId, "<<PatientPhoneNum>>", clientPhoneNum);
  insertInForm(newFileId, "<<PolicyHolderName>>", policyHolderName);
  insertInForm(newFileId, "<<PolicyHolderDOB>>", policyHolderDOB);
  insertInForm(newFileId, "<<PolicyHolderRelation>>", policyHolderRelation);
  insertInForm(newFileId, "<<InsuranceName>>", insuranceName);
  insertInForm(newFileId, "<<InsuranceNumber>>", insurancePhone);
  insertInForm(newFileId, "<<MedId>", insuranceMedID);

  //getFilePostRun(clientRow);
  //ui.alert("Here is your new file: \n" + DriveApp.getFileById(fileIDArray[i]).getUrl());
}
