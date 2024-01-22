"use strict";

function main() {
    createTable();
    document.onclick = handleClick;
}

window.onload = main;

function createTable() {
    let html = '<table border="1">';

    for (let i = 0; i < 11; i++) {
        const label = i === 0 ? "#" : i;
        html += `<tr><td>${label}</td>`;
        const multiplier = i === 0 ? 1 : i;

        for (let j = 1; j < 11; j++) {
            html += `<td>${multiplier * j}</td>`;
        }

        html += "</tr>";
    }

    document.getElementById("table").innerHTML = html + '</table>';
}

function handleClick() {
    let table = document.getElementById('table');
    let cells = table.getElementsByTagName('td');

    for (let i = 0; i < cells.length; i++) {
        let cell = cells[i];

        cell.onclick = function () {
            let rowId = this.parentNode.rowIndex;
            let colId = this.cellIndex;

            if (rowId && colId) {
                let rowsNotSelected = table.getElementsByTagName('tr');
                let colsNotSelected = table.getElementsByTagName('td');

                for (let row = 0; row < rowsNotSelected.length; row++) {
                    rowsNotSelected[row].style.backgroundColor = "";
                    rowsNotSelected[row].classList.remove('selected');
                }

                for (let col = 0; col < colsNotSelected.length; col++) {
                    colsNotSelected[col].style.backgroundColor = "";
                    colsNotSelected[col].classList.remove('selected');
                }

                let rowSelected = table.getElementsByTagName('tr')[rowId];
                let colSelected = table.getElementsByTagName('td')[colId];

                rowSelected.querySelector('td').style.backgroundColor = "yellow";
                colSelected.style.backgroundColor = "yellow";
                this.style.backgroundColor = "yellow";
                rowSelected.className += " selected";
                colSelected.className += " selected";
            }
        }
    }
}

document.getElementById('togglebtn').addEventListener('click', function () {
    let x = document.body;
    x.style.backgroundColor = x.style.backgroundColor === "red" ? "blue" : "red";
});