// INCOMPLETE CODE, WAS NEVER FULLY IMPLEMENTED.

function importEmail() {
  // https://www.youtube.com/watch?v=NTA0WMNTfEo

  var ui = SpreadsheetApp.getUi();

  // Get specific email threads.
  var threads = GmailApp.search("from:example@gmail.com ");

  // Loop through the email list till the desired email is found.
  //var i = 0;
  //while (validEmail() && i != threads.length())
  for (var i = 0; i < threads.length; i++) {
    var emails = threads[i].getMessages();
    for (var j = 0; j < emails.length; j++) {
      //var whoFrom = emails[j].getFrom();
      //var date = emails[j].getDate();
      var body = emails[j].getPlainBody();
      //ui.alert("From: " + whoFrom + " Date: " + date);
      //ui.alert(body); // is already a string.
      var bodySplit = body.split("\n*");
      for (var k = 0; k < bodySplit.length; k++) {
        var bodySplitSplit = bodySplit[k].replace("*", ":").split(":\n");
        ui.alert(bodySplitSplit[0]);
        if (bodySplitSplit[0] == "Full Name") {
          ui.alert(bodySplitSplit[1]);
        }
        //ui.alert(bodySplit[k].replace('*',':'));
      }
    }
    //parseEmail(email);
  }

  // Get the domain of the email.
  var usernameParts = username.toString().split("@");
  var emailDomain = usernameParts[1];
}

function parseEmail(email) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssSheet = ss.getSheetByName("VOB Current Month");
  ssSheet.appendRow("Email data here");
}
