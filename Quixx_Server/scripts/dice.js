// This function will cause all available dice to reroll themselves, then update their visual values.
function rollDice() {
    removeAvailabilityFromCells();
    var whiteDice1 = document.getElementById("whiteDice1");
    var whiteDice2 = document.getElementById("whiteDice2");
    var redDice = document.getElementById("redDice");
    var yellowDice = document.getElementById("yellowDice");
    var greenDice = document.getElementById("greenDice");
    var blueDice = document.getElementById("blueDice");
    whiteDice1.textContent = randomizeDice();
    whiteDice2.textContent = randomizeDice();
    redDice.textContent = randomizeDice();
    yellowDice.textContent = randomizeDice();
    greenDice.textContent = randomizeDice();
    blueDice.textContent = randomizeDice();

    markAllAvailableCells([parseInt(whiteDice1.textContent), parseInt(whiteDice2.textContent), 
                        parseInt(redDice.textContent), parseInt(yellowDice.textContent), 
                        parseInt(greenDice.textContent), parseInt(blueDice.textContent)]);
    cellsPicked = 0;
}

function markAllAvailableCells(diceResults) {
    for (let generic_dice_i = 0; generic_dice_i < 2; generic_dice_i++) {
        markCell(getAvailableCellID("red", diceResults[generic_dice_i], diceResults[2]), "red");
        markCell(getAvailableCellID("yellow", diceResults[generic_dice_i], diceResults[3]), "yellow");
        markCell(getAvailableCellID("green", diceResults[generic_dice_i], diceResults[4]), "green");
        markCell(getAvailableCellID("blue", diceResults[generic_dice_i], diceResults[5]), "blue");
    }
}

function getAvailableCellID(color, die1, die2) {
    var value = die1 + die2;
    var id = color + value;
    return id;
}

// This function will roll a single die to determine its new value.
function randomizeDice() {
    return Math.floor(Math.random() * 6) + 1;
}

// This function will cause all available dice to reroll themselves, then update their visual values.
function setDiceEnd() {
    var whiteDice1 = document.getElementById("whiteDice1");
    var whiteDice2 = document.getElementById("whiteDice2");
    var redDice = document.getElementById("redDice");
    var yellowDice = document.getElementById("yellowDice");
    var greenDice = document.getElementById("greenDice");
    var blueDice = document.getElementById("blueDice");
    whiteDice1.textContent = 6;
    whiteDice2.textContent = 1;
    redDice.textContent = 6;
    yellowDice.textContent = 6;
    greenDice.textContent = 1;
    blueDice.textContent = 1;
    
    markAllAvailableCells([parseInt(whiteDice1.textContent), parseInt(whiteDice2.textContent), 
        parseInt(redDice.textContent), parseInt(yellowDice.textContent), 
        parseInt(greenDice.textContent), parseInt(blueDice.textContent)]);
    cellsPicked = 0;
}