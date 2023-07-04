function onOpen() {
  let ui = SpreadsheetApp.getUi();
  ui.createMenu('Create Template')
      .addItem('Make a new file', 'newFile')
      .addItem('Stamp start time', 'testStartStamp')
      .addItem('Send file (partial)', 'endStamp')
      .addItem('Send file (completed)', 'sendFileComplete')
      .addItem('Test Time', 'testTime')
      .addItem('Archive Sheet', 'archiveMonth')
      .addToUi();
 addMenu(); 
}
