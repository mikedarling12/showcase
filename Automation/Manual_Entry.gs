function AddManualForm() {
  //var form = HtmlService.createHtmlOutputFromFile('EntryForm').setTitle('Manual Entry');
  var form = HtmlService.createTemplateFromFile("EntryForm")
    .evaluate()
    .setTitle("Manual Entry");
  SpreadsheetApp.getUi().showSidebar(form);
}

function AddQueryForm() {
  var ui = SpreadsheetApp.getUi();
  //var targetRow = ui.prompt("Select the row to be modified:");
  //if (targetRow.getSelectedButton() == ui.Button.CLOSE) {
  //  return;
  //}
  //var data = GetSheetValues(targetRow.getResponseText());
  //var form = HtmlService.createHtmlOutputFromFile('QueryEdit').setTitle('Query Edit');
  var form = HtmlService.createTemplateFromFile("QueryEdit")
    .evaluate()
    .setTitle("Query Edit");
  ui.showSidebar(form);
}

function AddRecord(
  facility_name,
  location_name,
  date,
  treatment_start_date,
  old_client_new_insurance,
  form_filler,
  form_filler_email,
  form_filler_phone,
  client_first_name,
  client_last_name,
  patient_dob,
  second_insurance,
  patient_phone,
  client_ssn,
  client_street,
  client_street_2,
  client_city,
  client_state,
  client_zip,
  insurance_provider,
  insurance_provider_phone,
  client_insurance_id,
  policy_holder_first_name,
  policy_holder_last_name,
  policy_holder_dob,
  policy_holder_client_relation,
  policy_holder_street,
  policy_holder_street_2,
  policy_holder_city,
  policy_holder_state,
  policy_holder_zip,
  policy_benefits,
  policy_benefit_type
) {
  var ss = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  ss.appendRow([
    "",
    "",
    "",
    "",
    "",
    facility_name,
    location_name,
    date,
    treatment_start_date,
    old_client_new_insurance,
    form_filler,
    form_filler_email,
    form_filler_phone,
    client_first_name,
    client_last_name,
    patient_dob,
    second_insurance,
    patient_phone,
    client_ssn,
    client_street,
    client_street_2,
    client_city,
    client_state,
    client_zip,
    insurance_provider,
    insurance_provider_phone,
    client_insurance_id,
    policy_holder_first_name,
    policy_holder_last_name,
    policy_holder_dob,
    policy_holder_client_relation,
    policy_holder_street,
    policy_holder_street_2,
    policy_holder_city,
    policy_holder_state,
    policy_holder_zip,
    policy_benefits,
    policy_benefit_type,
  ]);
  var newRow = ss.getLastRow();
  //SpreadsheetApp.getUi().alert(ss.getRange)
  ss.getRange(newRow, 3).insertCheckboxes();
}

function EditRecord(row, dataArr) {
  var ss = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var topRange = ss.getRange(1, 2, 1, 41).getValues().flat();
  //var currentRange = ss.getRange(row, 1, 1, 33);
  stampValue(row, topRange[0], dataArr[0]);
  for (var i = 1; i < 35; i++) {
    if (dataArr[i] != "/") stampValue(row, topRange[i + 2], dataArr[i]);
  }
}

function GetSheetValues(row) {
  var ss =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VOB Current Month");
  var values = ss
    .getRange(row, 2, 1, 38)
    .setNumberFormat("@STRING@")
    .getValues()
    .flat();
  return values;
}

function GetInsuranceCompanies() {
  return (companies = SpreadsheetApp.getActiveSpreadsheet()
    .getSheetByName("Facilities and Locations")
    .getRange(4, 1, 28, 1)
    .getValues()
    .flat());
}

function GetFacilities() {
  //var ui = SpreadsheetApp.getUi();

  // Get the whole data set.
  const facilities = SpreadsheetApp.getActiveSpreadsheet()
    .getSheetByName("Facilities and Locations")
    .getRange(4, 1, 28, 22)
    .getValues();

  //console.log("Facilities:");
  //ui.alert(facilities);

  // Make a map to store our companies with each of their locations.
  var facilityMap = new Map();

  // Go through each row, but all columns but the first, as that is where the company name is.
  for (var row = 0; row < 24; row++) {
    for (var col = 2; col < 22; col++) {
      // As long as the space is not blank, add it to the set.
      var company = facilities[row][0];
      var location = facilities[row][col];
      if (location != "") {
        facilityMap.set(location, company);
      }
    }
  }

  console.log("Facilities Set:");
  for (let key of facilityMap.keys()) {
    console.log(key);
  }
  //ui.alert(facilityMap.size);

  return facilityMap;
}

function GetLocations(row) {
  // Get the whole data set.
  const facilities = SpreadsheetApp.getActiveSpreadsheet()
    .getSheetByName("Facilities and Locations")
    .getRange(4, 1, 28, 22)
    .getValues();

  // Make a map to store our companies with each of their locations.
  var facilityMap = new Map();

  // Go through each row, but all columns but the first, as that is where the company name is.
  for (var col = 2; col < 22; col++) {
    // As long as the space is not blank, add it to the set.
    var company = facilities[row][0];
    var location = facilities[row][col];
    if (location != "") {
      facilityMap.set(location, company);
    }
  }

  console.log("Facilities Set:");
  for (let key of facilityMap.keys()) {
    console.log(key);
  }
  //ui.alert(facilityMap.size);

  return facilityMap;
}

function createDropDown() {
  var companies = GetInsuranceCompanies();
  var htmlOptions = "";
  companies.forEach(function (value) {
    htmlOptions = htmlOptions + "<option>" + value + "</option>";
  });
  return htmlOptions;
}

function test_GetInsuranceCompanies() {
  var ui = SpreadsheetApp.getUi();
  GetFacilities();
}

function checkpointOne() {
  SpreadsheetApp.getUi().alert("Checkpoint 1.");
}

function checkpointTwo() {
  SpreadsheetApp.getUi().alert("Checkpoint 2.");
}

function getAllStates() {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var statesSheet = ss.getSheetByName("States");
  var [headers, ...data] = statesSheet.getDataRange().getValues();
  return data;
}
