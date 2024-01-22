# CS6016 Lab 4: SQL

## Part 2 - Creating the Dealership

```
CREATE TABLE Cars (
	VIN int unsigned PRIMARY KEY,
	Make varchar(255),
	Model varchar(255),
	Year int unsigned,
	Color varchar(255)
);

CREATE TABLE SalesPeople (
	SSN int unsigned PRIMARY KEY,
	Name varchar(255)
);

CREATE TABLE Responsible (
	uID int unsigned PRIMARY KEY,
	VIN int unsigned,
	SSN int unsigned,
	FOREIGN KEY (VIN) REFERENCES Cars(VIN),
	FOREIGN KEY (SSN) REFERENCES SalesPeople(SSN)
);

INSERT INTO Cars
VALUES
	(1, "Toyota", "Tacoma", 2008, "Red"),
	(2, "Toyota", "Tacoma", 1999, "Green"),
	(3, "Tesla", "Model 3", 2018, "White"),
	(4, "Subaru", "WRX", 2016, "Blue"),
	(5, "Ford", "F150", 2004, "Red");

INSERT INTO SalesPeople
VALUES
	(1111111111, "Arnold"),
	(2222222222, "Hannah"),
	(3333333333, "Steve");

INSERT INTO Responsible
VALUES
	(1, 1, 1111111111),
	(2, 1, 2222222222),
	(3, 2, 1111111111),
	(4, 3, 3333333333),
	(5, 4, NULL),
	(6, 5, 2222222222);
```

## Part 3 - Simple Retrieval Queries

* Get the Titles of all books by `<Author>`

```
SELECT Title
FROM Titles
WHERE Author = "<Author>"
```

* Get Serial numbers of all books by `<Author>`

```
SELECT Serial
FROM Titles
INNER JOIN Inventory ON Titles.ISBN = Inventory.ISBN
WHERE Author = "<Author>"
```

* Get the Titles of all books checked out by `<Patron's name>`

```
SELECT Title
FROM CheckedOut
INNER JOIN Patrons ON CheckedOut.CardNum = Patrons.CardNum
INNER JOIN Inventory ON CheckedOut.Serial = Inventory.Serial
INNER JOIN Titles ON Titles.ISBN = Inventory.ISBN
WHERE Patrons.Name = "<Patron's name>"
```

* Get phone number(s) of anyone with `<Title>` checked out

```
SELECT DISTINCT Phone
FROM CheckedOut
INNER JOIN Phones ON Phones.CardNum = CheckedOut.CardNum
INNER JOIN Inventory ON CheckedOut.Serial = Inventory.Serial
INNER JOIN Titles ON Titles.ISBN = Inventory.ISBN
WHERE Title = "<Title>"
```

## Part 4 - Intermediate Retrieval Queries

* Find the Titles of the library's oldest `<N>` books. Assume the lowest serial number is the oldest book.

```
SELECT Title
FROM Titles
INNER JOIN Inventory
ON Titles.ISBN = Inventory.ISBN
ORDER BY Serial
LIMIT <N>
```

* Find the name of the person who has checked out the most recent book. Assume the highest serial number is the newest book.

```
SELECT Name
FROM Patrons
INNER JOIN CheckedOut
ON Patrons.CardNum = CheckedOut.CardNum
ORDER BY Serial DESC
LIMIT 1
```

* Find the phone number(s) of anyone who has not checked out any books.

```
SELECT Phone
FROM Phones
WHERE CardNum NOT IN (
	SELECT DISTINCT CardNum
	FROM CheckedOut)
```

* The library wants to expand the number of unique selections in its inventory, thus, it must know the ISBN and Title of all books that it owns at least one copy of. Create a query that will return the ISBN and Title of every book in the library, but will not return the same book twice.

```
SELECT DISTINCT Titles.ISBN, Titles.Title
FROM Inventory
INNER JOIN Titles
ON Inventory.ISBN = Titles.ISBN
```

## Part 5 - Chess Queries

* Find the names of any player with an Elo rating of 2850 or higher.

```
SELECT DISTINCT Name
FROM Players
WHERE Elo >= 2850
```

* Find the names of any player who has ever played a game as white.

```
SELECT DISTINCT Name
FROM Players
INNER JOIN Games
ON Players.pID = Games.WhitePlayer
```

* Find the names of any player who has ever won a game as white.

```
SELECT DISTINCT Name
FROM Players
INNER JOIN Games
ON Players.pID = Games.WhitePlayer AND Games.Result = "W"
```

* Find the names of any player who played any games in 2018.

```
SELECT DISTINCT Name
FROM Players
INNER JOIN (
	SELECT WhitePlayer, BlackPlayer
	FROM Events
	INNER JOIN Games
	ON Events.eID = Games.eID AND year(Date) = 2018) AS Games2018
WHERE pID = BlackPlayer OR pID = WhitePlayer
```

* Find the names and dates of any event in which Magnus Carlsen lost a game.

```
SELECT DISTINCT Name, Date
FROM Events
INNER JOIN (
	SELECT eID
	FROM Players
	INNER JOIN Games
	ON (pID = Games.WhitePlayer AND Result = 'B')
	OR (pID = Games.BlackPlayer AND Result = 'W')
	WHERE Name = "Carlsen, Magnus") AS T
WHERE T.eID = Events.eID
```

* Find the names of all opponents of Magnus Carlsen.

```
SELECT DISTINCT Name
FROM Players
INNER JOIN (
	SELECT BlackPlayer, WhitePlayer
	FROM Players
	INNER JOIN Games
	ON pID = Games.WhitePlayer
	OR pID = Games.BlackPlayer
        WHERE Name = "Carlsen, Magnus") AS T
WHERE Name != "Carlsen, Magnus" AND (WhitePlayer = Players.pID or BlackPlayer = Players.pID)
```
