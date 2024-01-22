# CS6016 Lab 1: Relational Model and Keys

## Part 1

+ Inventory [__SKU__ (integer), name (string), quantity (integer), price (real)]

+ Aisle [__SKU__ (integer), name (string), aisle (integer)]

+ Cars [__VIN__ (string), make (string), model (string), year (integer), color (string)]

+ Salespeople [__SSN__ (string), name (string)]

+ Responsible [__uID__ (string), VIN (string), SSN (string)]

## Part 2

```
CREATE TABLE Patrons (
    Name string,
    CardNum integer,
    PRIMARY KEY (CardNum)
)

CREATE TABLE Phones (
    CardNum string,
    Phone char(8),
    PRIMARY KEY (CardNum, Phone),
    FOREIGN KEY (CardNum) REFERENCES Patrons(CardNum)
)

CREATE TABLE CheckedOut (
    CardNum integer,
    Serial integer,
    PRIMARY KEY (Serial),
    FOREIGN KEY (Serial) REFERENCES Inventory(Serial),
    FOREIGN KEY (CardNum) REFERENCES Patrons(CardNum)
)

CREATE TABLE Inventory (
    Serial integer,
    ISBN char(14),
    PRIMARY KEY (Serial),
    FOREIGN KEY (ISBN) REFERENCES Titles(ISBN)
)

CREATE TABLE Titles (
    ISBN char(14),
    Title string,
    Author string,
    PRIMARY KEY (ISBN)
)
```

## Part 3

### Cars table

| VIN | make | model | year | color|
| --- | --- | --- | --- | --- |
| 1 | Toyota | Tacoma | 2008 | Red |
| 2 | Toyota | Tacoma | 1999 | Green |
| 3 | Tesla | Model 3 | 2018 | White |
| 4 | Subaru | WRX | 2016 | Blue |
| 5 | Ford | F150 | 2004 | Red |

### Salespeople table

| SSN | name |
| --- | --- |
| 1111111111 | Arnold |
| 2222222222 | Hannah |
| 3333333333 | Steve |

### Responsible table

| uID | VIN | SSN |
| --- | --- | --- |
| 1 | 1 | 1111111111 |
| 2 | 1 | 2222222222 |
| 3 | 2 | 1111111111 |
| 4 | 3 | 3333333333 |
| 5 | 4 | NULL |
| 6 | 5 | 2222222222 |

## Part 4

|Attribute Sets|Superkey?|Proper Subsets|Key?|
|---           |---      |---           |--- |
|{A1}          |No       |{}            |No  |
|{A2}          |No       |{}            |No  |
|{A3}          |No       |{}            |No  |		
|{A1, A2}      |Yes      |{A1}, {A2}    |Yes |
|{A1, A3}      |No       |{A1}, {A3}    |No  |
|{A2, A3}      |No       |{A2}, {A3}    |No  |
|{A1, A2, A3}  |Yes      |{A1}, {A2}, {A3}|No|

## Part 5

+ False. Other sets might have duplicate {x}.

+ False. Other sets might have duplicate {x}.

+ True. All keys are superkey.

+ False. {x, y, z} can be a superkey even if {x}, {y}, or {z} are all not superkey.

+ True. {x, y, z} is the minimal subsets of unique values.