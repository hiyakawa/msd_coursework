"use strict";

function selectionSort(arr, param) {
    for (let i = 0; i < arr.length; i++) {
        let minLocation = findMinLocation(arr, i, param);
        // if a smaller element is found
        if (minLocation != i) {
            // swap the elements
            let tmp = arr[i]; 
            arr[i] = arr[minLocation];
            arr[minLocation] = tmp;      
        }
    }
    return arr;
}

function findMinLocation(arr, minLocation, param) {
    // find the smallest number in the subarray
    for (let j = minLocation + 1; j < arr.length; j++) {
        if (param(arr[j], arr[minLocation]) == -1) {
            minLocation = j; 
        }
    }
    return minLocation;
}

function compareTo(a, b) {
    if (a > b) {
        return 1;
    }
    else if (a == b) {
        return 0;
    }
    return -1;
}

// // int arrry
let intArr = [5, 4, 3, 2, 1];
// selectionSort(intArr);
// console.log(intArr);
// // [1, 2, 3, 4, 5]

// // float arrry
let floatArr = [5.1, 4.2, 3.0, 2.9, 1.7];
// selectionSort(floatArr);
// console.log(floatArr);
// // [1.7, 2.9, 3, 4.2, 5.1]

// // string arrry
let stringArr = ["C", "a", "3", "b", "1"];
// selectionSort(stringArr);
// console.log(stringArr);
// // ['1', '3', 'C', 'a', 'b']
// // sorted based on ASCII value

// // mixed arrry
// let mixedArr = [5, "6.2", 3.0, "2", 1.1];
// selectionSort(mixedArr);
// console.log(mixedArr);
// // [1.1, '2', 3, 5, '6.2']
// // strings are converted to floats (or ints)

console.log(selectionSort(intArr, compareTo));
// [1, 2, 3, 4, 5]
console.log(selectionSort(floatArr, compareTo));
// [1.7, 2.9, 3, 4.2, 5.1]
console.log(selectionSort(stringArr, compareTo));
// ['1', '3', 'C', 'a', 'b']

/* Q: Try changing the comparison in compareTo() from "<" to ">".
 *    What happens when you sort now?
 * A: selectionSort() will sort the arrays in descending order.
 *    [5, 4, 3, 2, 1]
 *    [5.1, 4.2, 3, 2.9, 1.7]
 *    ['b', 'a', 'C', '3', '1']
 */

let laylaSmith = {};
laylaSmith.first = "Layla";
laylaSmith.last = "Smith";

let avaSmith = {};
avaSmith.first = "Ava";
avaSmith.last = "Smith";

let elijahMiles = {};
elijahMiles.first = "Elijah";
elijahMiles.last = "Miles";

let avaMiles = {};
avaMiles.first = "Ava";
avaMiles.last = "Miles";

let people = [laylaSmith, avaSmith, elijahMiles, avaMiles];

function sortPeopleByLast(arr) {
    for (let i = 0; i < arr.length; i++) {
        let minLocation = i;

        for (let j = i + 1; j < arr.length; j++) {
            if ((arr[j].last < arr[minLocation].last) ||
                ((arr[j].last == arr[minLocation].last) && (arr[j].first < arr[minLocation].first))) {
                minLocation = j; 
            }
        }
        if (minLocation != i) {
            let tmp = arr[i]; 
            arr[i] = arr[minLocation];
            arr[minLocation] = tmp;      
        }
    }
    return arr;
}

let sortedPeopleByLast = sortPeopleByLast(people);

for (let person of sortedPeopleByLast) {
    console.log(person.first, person.last);
}
// ava Miles, elijah Miles, ava Smith, layla Smith

function sortPeopleByFirst(arr) {
    for (let i = 0; i < arr.length; i++) {
        let minLocation = i;

        for (let j = i + 1; j < arr.length; j++) {
            if ((arr[j].first < arr[minLocation].first) ||
                ((arr[j].first == arr[minLocation].first) && (arr[j].last < arr[minLocation].last))) {
                minLocation = j; 
            }
        }
        if (minLocation != i) {
            let tmp = arr[i]; 
            arr[i] = arr[minLocation];
            arr[minLocation] = tmp;      
        }
    }
    return arr;
}

let sortedPeopleByFirst = sortPeopleByFirst(people);

for (let person of sortedPeopleByFirst) {
    console.log(person.first, person.last);
}
// ava Miles, ava Smith, elijah Miles, layla Smith