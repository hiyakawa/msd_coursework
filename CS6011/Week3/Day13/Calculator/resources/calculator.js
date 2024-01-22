"use strict";

let xTA = document.getElementById("xTA");
let yTA = document.getElementById("yTA");
let resultTA = document.getElementById("resultTA");
let wsResultTA = document.getElementById("wsResultTA");
let button = document.getElementById("addBtn");
let ws = new WebSocket("ws://localhost:8080");
let wsOpen = false;

xTA.addEventListener("keypress", handleKeyPressCB);
yTA.addEventListener("keypress", handleKeyPressCB);
button.addEventListener("click", handleKeyPressCB);

ws.onopen = handleConnectCB;
ws.onmessage = handleMessageFromWsCB;

function handleAjaxErrorCB() {
    console.log("An ajax error occurred");
    wsResultTA.value = "Server has a problem...";
}

function handleAjaxSuccessCB() {
    console.log("Got a response from the server");
    resultTA.value = this.responseText;
}

function handleConnectCB() {
    console.log("The web socket is open.");
    wsOpen = true;
}

function handleMessageFromWsCB(event) {
    console.log("Receiving message...");
    wsResultTA.value = event.data;
}

function handleKeyPressCB(event) {
    if (event.type == "click" || event.keyCode == 13) {
        let x = parseFloat(xTA.value);
        let y = parseFloat(yTA.value);

        if (isNaN(x)) {
            alert("x has to be a number");
            xTA.value = "<Enter a number>";
            xTA.select();
            return;
        }

        if (isNaN(y)) {
            alert("y has to be a number");
            yTA.value = "<Enter a number>";
            yTA.select();
            return;
        }

        let request = new XMLHttpRequest();
        request.open("GET", "http://localhost:8080/calculate?x=" + x + "&y=" + y);
        request.addEventListener("error", handleAjaxErrorCB);
        request.addEventListener("load", handleAjaxSuccessCB);
        request.send();

        if (wsOpen) {
            ws.send(x + " " + y);
        }
        else {
            wsResultTA.value = "WS is not open...";
        }
    }
}
