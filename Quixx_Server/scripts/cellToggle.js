function toggleCell(id) {
    var cell = document.getElementById(id);
    if (cell.classList.contains('notSelected')) {
        cell.classList.remove('notSelected');
        cell.classList.add('selected');
        cell.querySelector('.mark-button').classList.add('marked');
        let color = cell.querySelector('.mark-button').classList[0];
        updateTotal(color);
    }
    else if (cell.classList.contains('selected')) {
        cell.classList.remove('selected');
        cell.classList.add('notSelected');
        cell.querySelector('.mark-button').classList.remove('marked');
        let color = cell.querySelector('.mark-button').classList[0];
        updateTotal(color);
    }
}

function updateTotal(color) {
    var total = 0;
    let numSelected = 0;
    for (var i = 2; i <= 13; i++) {
        var cell = document.getElementById(color + i);
        if (!cell.classList.contains('notSelected')) {
            total += ++numSelected;
        }
    }
    document.getElementById(color + 'Total').textContent = total;
    updateOverallTotal();
}

function updateOverallTotal() {
    let redTotal = parseInt(document.getElementById('redTotal').textContent);
    let yellowTotal = parseInt(document.getElementById('yellowTotal').textContent);
    let greenTotal = parseInt(document.getElementById('greenTotal').textContent);
    let blueTotal = parseInt(document.getElementById('blueTotal').textContent);
    let overallTotal = redTotal + yellowTotal + greenTotal + blueTotal;
    document.getElementById('overallTotal').textContent = overallTotal;
}