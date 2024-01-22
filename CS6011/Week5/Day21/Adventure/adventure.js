
let roomNameBQ;
let loginDiv;
let gameDiv;
let commandTA;
let outputDiv;
let ws;

let wsIsOpen = false;

let roomNameText
let roomNameElement = "room-name"
let description
let descriptionElement = "description"
let exits = []
let exitsElement = "exits__content"
let roomItems = []
let roomItemsElement = "room-items__content"
let inventory = []
let inventoryElement = "inventory__content"
let actions = []
let actionsElement = "actions__content"
let playersHere = []
let playersHereElement = "players__content"

// let listArray = []
// listArray.push(exits)
// listArray.push(roomItems)
// listArray.push(inventory)
// listArray.push(actions)
// listArray.push(playersHere)

function updateList(items, elementID){
    let itemsList = document.getElementById(elementID)
    itemsList.innerHTML = ""
    for (let item of items) {
        if (item != "") {
            let itemStr = "<li>" + item + "</li>"
            itemsList.innerHTML += itemStr
        }
    }
}

function updateRoom(){
    // roomName = document.getElementById("room-name")
    // roomName.innerText = roomNameText
    //
    // description = document.getElementById("description")
    // description.innerText = description

    updateList(exits, exitsElement)

    updateList(roomItems, roomItemsElement)

    updateList(inventory, inventoryElement)

    updateList(actions, actionsElement)

    updateList(playersHere, playersHereElement)

}

function printList(content, elementID, items){
    items = content.split(',')
    updateList(items, elementID)
}

///////////////////////////////////////////////////////////////////
// Web Socket Handlers:

function handleWebSocketOpen( event ) {
    console.log( "handle WS Open" );
    commandTA.select();
    ws.send( "playerName: " + playerNameTA.value );
    ws.send("l");
    wsIsOpen = true;
}

/*  TONG SHEN
 *  - Hide the gameDiv when the server is down.
 *  - Print information to notify the players.
 */
function handleWebSocketClose( event ) {
    console.log( "handleWebSocketClose: '" + event.reason + "', " + event.code );
    serverDownDiv.style.display = "block";
    gameDiv.style.display = "none";
    loginDiv.style.display = "none";
    wsIsOpen = false;
    let display = document.getElementById("outputDiv");
    display.innerHTML = "";
    let exists = document.getElementById("exits__content");
    exists.innerHTML = "";
    let roomItems = document.getElementById("room-items__content");
    roomItems.innerHTML = "";
    let inventory = document.getElementById("inventory__content");
    inventory.innerHTML = "";
    let actions = document.getElementById("actions__content");
    actions.innerHTML = "";
    let players = document.getElementById("players__content");
    players.innerHTML = "";
    commandTA.value = '';
    commandTA.select();
}

function handleWebSocketMessage( event ) {

    /*  TONG SHEN
     *  - check the message, if it is "InvalidName", alert the player and ask her to use another one
     *  - go back to the login page
     */
    if (event.data === "InvalidName"){
        gameDiv.style.display = "none";
        loginDiv.style.display = "block";
        alert("Player name is already taken. Please try another one.");
    }
    else if (event.data == "ValidName"){
        gameDiv.style.display = "block";
        loginDiv.style.display = "none";
        commandTA.select();
    }
    else
    {
        console.log("msg is " + event.data );

        let p  = document.createElement('p');
        let hr = document.createElement('hr');

        p.innerHTML = event.data;

        outputDiv.appendChild(p);
        outputDiv.appendChild(hr);
        hr.scrollIntoView();
    
    }
}

///////////////////////////////////////////////////////////////////////////

function handleWebSocketError( error ) {
    console.log( "handleWebSocketError: " + error.message );
}

///////////////////////////////////////////////////////////////////

function handlePlayerName( e ) {
    if (e.keyCode == 13) {
        e.preventDefault(); // Prevent the <CR> from being added to the textarea.

        if(validateName(e)){
            playerNameTitle.textContent = "Player: " + playerNameTA.value;
            playerNameTitle.style.display = "inline-block";
        // following line for offline testing purposes -- remove before production (Jon)
        // gameDiv.style.display = "block";
        // loginDiv.style.display = "none";
        //     serverName = serverSelect.textContent;
        //     ws = new WebSocket( serverName );
            // ws = new WebSocket( "ws://localhost:12345" );
            ws = new WebSocket( "ws://10.17.222.247:12345" );
            ws.onopen    = handleWebSocketOpen;
            ws.onclose   = handleWebSocketClose;
            ws.onmessage = handleWebSocketMessage;
            ws.onerror   = handleWebSocketError;
        }
    }
}

function handleLoginClick( e ) {

    if(validateName(e)){
        playerNameTitle.textContent = "Player: " + playerNameTA.value;
        playerNameTitle.style.display = "inline-block";
        //////////////////////////////
        // Setup the WebSocket:
        // serverName = serverSelect.textContent;
        // ws = new WebSocket( serverName );
        // ws = new WebSocket( "ws://localhost:12345" );
        ws = new WebSocket( "ws://10.17.222.247:12345" );
        ws.onopen    = handleWebSocketOpen;
        ws.onclose   = handleWebSocketClose;
        ws.onmessage = handleWebSocketMessage;
        ws.onerror   = handleWebSocketError;
    }
}

function handleServerNameClick(e) {
    console.log("we made it");
    serverTextDropdown.hidden = true;
    serverSelect.hidden = false;
    serverSelect.select();
}

function handleCommand( e ) {
    if( e.keyCode == 13 ) {
        e.preventDefault(); // Prevent the <CR> from being added to the textarea.
        ws.send( commandTA.value );
        commandTA.value = "";
    }
}

let justGotFocus = false;
serverDownDiv.style.display = "none";

// function handleMouseUp( e ) {
//     console.log("mouseup");
//     e.preventDefault();
//     e.stopImmediatePropagation();
//     e.stopPropagation();
// }

// Prevent the mouse down event from doing anything immediately after a window
// focus event.  This allows us to "select" the command textarea and leave it
// ready for the user to type a command into.
function handleMouseDown( e ) {
    // console.log("mousedown");
    if( justGotFocus ) {
        e.preventDefault();
        justGotFocus = false;
    }
}

function handleWindowFocus( e ) {
    // console.log( "handle window focus");
    justGotFocus = true;
    commandTA.focus();
    commandTA.select();
}

/*  TONG SHEN
 *  - Set a button to let the player go back to the login page if the server is down.
 */
function handleBack(e) {
    console.log( "User go back to the login page.");
    loginDiv.style.display = "block";
    serverDownDiv.style.display = "none";
    gameDiv.style.display = "none";
}

window.onload = () => {

    loginDiv = document.getElementById("loginDiv")

    gameDiv = document.getElementById( "gameDiv" );
    gameDiv.style.display = "none";

    playerNameTitle = document.getElementById("playerNameVal")

    playerNameTA = document.getElementById( "playerNameText" );
    playerNameTA.onkeypress = (e) => { handlePlayerName( e ); };

    serverSelect = document.getElementById("serverNameText");

    serverTextDropdown = document.getElementById("serverTextDropdown");
    serverTextDropdown.onclick = (e) => { handleServerNameClick( e ); };

    loginButton = document.getElementById("loginButton");
    loginButton.onclick = (e) => { handleLoginClick( e ); };

    commandTA = document.getElementById( "commandText" );
    commandTA.onkeypress = (e) => { handleCommand( e ); };

    outputDiv = document.getElementById( "outputDiv" );

    serverDownDiv = document.getElementById("serverDownDiv");
    backhomeBtn = document.getElementById("backHomeBtn");
    backhomeBtn.onclick = (e) => { handleBack(e); };

    playerNameTA.select();
    // window.onmouseup = handleMouseUp;
    window.onfocus = handleWindowFocus;
    window.onmousedown = handleMouseDown;
}





/// From stack overflow...

function sanitize( string ) {
  const map = {
      '&': '&amp;',
      '<': '&lt;',
      '>': '&gt;',
      '"': '&quot;',
      "'": '&#x27;',
      "/": '&#x2F;',
  };
  const reg = /[&<>"'/]/ig;
  return string.replace(reg, (match)=>(map[match]));
}

//Diego
/*
validates that the player name is a letter A-Z a-z
returns a boolean
 */
function validateName(name) {
    //https://www.w3resource.com/javascript/form/all-letters-field.php
    //^ == start of line ......... $ == end of line
    var letters = /^[A-Za-z]+$/; //regex magic
    if(playerNameTA.value.match(letters) && playerNameTA.value != ""){
        return true;
    }
    else {
        alert("Please input your name as letters only");
        return false;
    }
}
