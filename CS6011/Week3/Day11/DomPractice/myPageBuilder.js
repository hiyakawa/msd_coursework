"use strict";

function main() {
    let newHeading1 = document.createElement("h1");
    let h1Text = document.createTextNode("Hello CS 6011!");
    newHeading1.appendChild(h1Text);
    document.body.append(newHeading1);

    let newHeading3 = document.createElement("h3");
    let h3Text = document.createTextNode("Muyuan Zhang @ U of U");
    newHeading3.appendChild(h3Text);
    document.body.append(newHeading3);

    let newPara1 = document.createElement("p");
    let paraText1 = document.createTextNode("In this lab, you'll write an HTML web page that uses at least 15 different HTML tags.");
    newPara1.appendChild(paraText1);
    document.body.append(newPara1);

    let newDiv1 = document.createElement("div");

    let newImg = document.createElement("img");
    newImg.src = "https://avatars.githubusercontent.com/u/71244459?v=4";
    newDiv1.appendChild(newImg);

    let newPara2 = document.createElement("p");

    let newLink = document.createElement("a");
    let linkText = document.createTextNode("My Github Repo for the course");
    newLink.appendChild(linkText);
    newLink.href = "https://github.com/hiyakawa/msd_coursework_u_of_u/tree/main/CS6011";
    newLink.title = "My Github Repo for the course";
    newPara2.appendChild(newLink);

    newDiv1.appendChild(newPara2);
    document.body.append(newDiv1);

    let newDiv2 = document.createElement("div");

    let newHeading4 = document.createElement("h4");
    let h4Text = document.createTextNode("Using GitHub Pages");
    newHeading4.appendChild(h4Text);
    newDiv2.append(newHeading4);

    let newPara3 = document.createElement("p");
    let paraText3 = document.createTextNode("Make the repo on GitHub:");
    newPara3.appendChild(paraText3);
    newDiv2.append(newPara3);

    let newUl1 = document.createElement("ul");
    let ulText1 = document.createTextNode("Make the repo under your own account, not under MSD.");
    newUl1.appendChild(ulText1);
    newDiv2.append(newUl1);

    let newUl2 = document.createElement("ul");
    let ulText2 = document.createTextNode("Name it yourgithubusername.github.io");
    newUl2.appendChild(ulText2);
    newDiv2.append(newUl2);

    let newUl3 = document.createElement("ul");
    let ulText3 = document.createTextNode("Select \"Add a README file\"");
    newUl3.appendChild(ulText3);
    newDiv2.append(newUl3);

    let newUl4 = document.createElement("ul");
    let ulText4 = document.createTextNode("Select Public.");
    newUl4.appendChild(ulText4);
    newDiv2.append(newUl4);

    document.body.append(newDiv2);
}

window.onload = main;