function lockIn() {
    if (!canRoll) {
        if (cellsPicked == 0) {
            markPenalty();
        } else {
            console.log("Locking in");
            var cellSelectedColor = document.querySelectorAll("." + selectedColor);
            var cellSelectedGeneric = document.querySelectorAll("." + selectedGeneric);
            console.log(cellSelectedColor);
            console.log(cellSelectedGeneric);
            if (cellSelectedColor.length == 1) {
                cellSelectedColor[0].classList.add("selected");
            }
            if (cellSelectedGeneric.length == 1) {
                cellSelectedGeneric[0].classList.add("selected");
            }
        }
        removeAvailabilityFromCells();
        cellsPicked = 0;
        canRoll = true;
    }
}

function markPenalty() {
    for (let i = 0; i < 6; i++) {
        let penaltyCheckbox = document.querySelector("#penalty" + (i + 1));
        if (!penaltyCheckbox.checked) {
            penaltyCheckbox.checked = true;
            console.log("Penalty Marked");
            updateOverallTotal();
            return;
        }
    }
    return;
}

function removeAvailabilityFromCells() {
    removeClassFromClassList(clickableGeneric);
    removeClassFromClassList(clickableColor);
    removeClassFromClassList(selectedGeneric);
    removeClassFromClassList(selectedColor);
}

function removeClassFromClassList(className) {
    var markedElements = document.querySelectorAll("." + className);
    var totalElements = markedElements.length;
    for (let i = 0; i < totalElements; i++) {
        markedElements[i].classList.remove(className);   
    }
}