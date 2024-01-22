"use strict";

document.writeln("Hello world from document.writeln()!")
// will show in the web page
console.log("Hello world from console.log()!")
// will show in the console

let myArray = ["String", true, 3, 2.0,
    {"city": "salt lake city", "country": "U.S."}];

console.log(myArray);

for (let val of myArray) {
    console.log(val);
}

function addTwoNum(a, b) {
    return a + b;
}

let myFunction = function(a, b) {
    return a + b;
}
// for the "let" version, the function do not have a name

console.log(addTwoNum(1.1, 2));
// float + int -> float
console.log(myFunction(1.01, "2"));
// returns "1.012"
// int + string -> string


