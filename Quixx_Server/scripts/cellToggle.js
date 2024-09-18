let cellsPicked = 0; // current max is 1, but once the generic die result is working, this will be two.

function toggleCell(id) {
    var cell = document.getElementById(id);
    if (cellCanBeSelected(id)) {
        cell.classList.remove('notSelected');
        cell.classList.add('selected');
        cell.querySelector('.mark-button').classList.add('marked');
        let color = cell.querySelector('.mark-button').classList[0];
        if (cell.textContent == 12 && (color == "red" || color == "yellow")) {
            let lockCell = document.getElementById(color + 13);
            lockCell.classList.remove('notSelected');
            lockCell.classList.add('selected');
            lockCell.querySelector('.mark-button').classList.add('marked');
        }
        if (cell.textContent == 2 && (color == "blue" || color == "green")) {
            let lockCell = document.getElementById(color + 13);
            lockCell.classList.remove('notSelected');
            lockCell.classList.add('selected');
            lockCell.querySelector('.mark-button').classList.add('marked');
        }
        updateTotal(color);
        cellsPicked++;
        // removeAvailabilityFromCells();
    }
    else if (cell.classList.contains('selected') && cell.classList.contains("clickable")) {
        cell.classList.remove('selected');
        cell.classList.add('notSelected');
        cell.querySelector('.mark-button').classList.remove('marked');
        let color = cell.querySelector('.mark-button').classList[0];
        updateTotal(color);
        cellsPicked--;
    }
}

function cellCanBeSelected(id) {
    let cell = document.getElementById(id);
    if (cell.classList.contains('notSelected') && cell.classList.contains("clickable") && isValidCell(id)) {
        return true;
    }
    return false;
}

function countSelectedCellsInRow(color) {
    var total = 0;
    for (var i = 2; i <= 13; i++) {
        var cell = document.getElementById(color + i);
        if (!cell.classList.contains('notSelected')) {
            total += 1;
        }
    }
    return total;
}

function updateTotal(color) {
    var total = 0;
    let numSelected = 0;
    for (var i = 2; i < 14; i++) {
        var cell = document.getElementById(color + i);
        if (!cell.classList.contains('notSelected')) {
            total += ++numSelected;
        }
    }
    document.getElementById(color + 'Total').textContent = total;
    updateOverallTotal();
}

function calculatePenalties() {
    let totalPenalty = 0;
    for (let penalty_i = 1; penalty_i < 5; penalty_i++) {
        if (document.getElementById("penalty" + penalty_i).checked) {
            totalPenalty += 5;
        }
    }
    return totalPenalty;
}

function updateOverallTotal() {
    let redTotal = parseInt(document.getElementById('redTotal').textContent);
    let yellowTotal = parseInt(document.getElementById('yellowTotal').textContent);
    let greenTotal = parseInt(document.getElementById('greenTotal').textContent);
    let blueTotal = parseInt(document.getElementById('blueTotal').textContent);
    let penaltyTotal = calculatePenalties();
    let overallTotal = redTotal + yellowTotal + greenTotal + blueTotal - penaltyTotal;
    document.getElementById('overallTotal').textContent = overallTotal;
}

function markCell(id, color) {
    if (cellStillPossible(id, color)) {
        document.getElementById(id).classList.add("clickable");
    }
}

function cellStillPossible(id, color) {
    if (document.getElementById(id).classList.contains("clickable") || document.getElementById(id).classList.contains("selected")) {
        return false;
    }
    var prospectiveCellValue = parseInt(document.getElementById(id).textContent);
    //console.log(color);
    //console.log(prospectiveCellValue);

    // Based on which color the prospective cell is, check for any cell that would block the cell from being selected.
    if (color == "red" || color == "yellow") {
        for (let valueToCheck = prospectiveCellValue + 1; valueToCheck < 12; valueToCheck++) {
            //console.log(document.getElementById(color + valueToCheck));
            if (document.getElementById(color + valueToCheck).classList.contains("selected")) {
                return false;
            }
        }
        if (prospectiveCellValue == 12 && countSelectedCellsInRow(color) < 5) {
            return false;
        }
    } else if (color == "blue" || color == "green") {
        for (let valueToCheck = prospectiveCellValue - 1; valueToCheck > 3; valueToCheck--) {
            //console.log(document.getElementById(color + valueToCheck));
            if (document.getElementById(color + valueToCheck).classList.contains("selected")) {
                return false;
            }
        }
        if (prospectiveCellValue == 2 && countSelectedCellsInRow(color) < 5) {
            return false;
        }
    } else { console.log("There was an exception here.")}
    return true;
}

function removeAvailabilityFromCells() {
    var markedElements = document.querySelectorAll(".clickable");
    var totalElements = markedElements.length;
    for (let i = 0; i < totalElements; i++) {
        markedElements[i].classList.remove('clickable');   
    }
}

function lockIn() {
    if (cellsPicked == 0) {
        markPenalty();
    }
    removeAvailabilityFromCells();
    cellsPicked = 0;
}

function markPenalty() {
    for (let i = 0; i < 6; i++) {
        let penaltyCheckbox = document.querySelector("#penalty" + (i + 1));
        if (!penaltyCheckbox.checked) {
            penaltyCheckbox.checked = true;
            console.log("Penalty Marked");
            return;
        }
    }
    return;
}

function isValidCell(id) {
    console.log(cellsPicked);
    if (cellsPicked >= 1) {
        return false;
    }
    return true;
}