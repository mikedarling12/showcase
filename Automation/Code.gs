function onOpen() {
  let ui = SpreadsheetApp.getUi();
  ui.createMenu("Create Template")
    //.addItem('Import email', 'importEmail')
    //.addItem('Claim Record', 'claimRecord') // in PutDataInCell.gs
    .addItem("Create New VOB", "newFile") // in NewTemplate.gs
    .addItem("Get VOB by row", "getFile") // in Getters.gs
    .addItem("Stamp start time", "testStartStamp") // in PutDataInCell.gs
    .addItem("Send facility email (partial)", "sendFilePartial") // in sendFile.gs
    .addItem("Send facility email (completed)", "sendFileComplete") // in sendFile.gs
    //.addItem('Archive Sheet', 'archiveMonth') // in ArchiveSheets.gs
    //.addItem('Archive Spreadsheet', 'archiveYear') // in ArchiveSheets.gs
    //.addItem('Test Parse Function', 'test_parseContent') // in ArchiveSheets.gs
    .addItem("Enter information manually", "AddManualForm") // in Manual_Entry.gs
    .addItem("Query Edit", "AddQueryForm") // in Manual_Entry.gs
    //.addItem('Test insurance company getter', 'test_GetInsuranceCompanies') // in Manual_Entry.gs
    .addToUi();
  addMenu();
}

//AddManualForm()

function createTimeDrivenTriggers() {
  // Archive sheets will trigger either monthly
  // or yearly archive, based on the month.
  ScriptApp.newTrigger("archiveSheets")
    .timeBased()
    .onMonthDay(1) // First of the month.
    .atHour(1) // As soon as it changes days.
    .create();
}
