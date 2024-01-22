# CS6016 Lab 5: SQL Continued

* Find the name of the patron who has checked out the most books.

```
SELECT Name
FROM Patrons
INNER JOIN (
	SELECT CardNum
	FROM CheckedOut
	GROUP BY CardNum
	HAVING COUNT(CardNum) = (
		SELECT COUNT(Serial) AS BookCount
		FROM CheckedOut
		GROUP BY CardNum
		ORDER BY BookCount DESC
		LIMIT 1)) AS A 
ON Patrons.CardNum = A.CardNum
```

* Find the Titles of all books that were written by an author whose name starts with 'K'.

```
SELECT Title
FROM Titles
WHERE Author LIKE "K%"
```

* Find the Authors who have written more than one book.

```
SELECT Author
FROM Titles
GROUP BY Author
HAVING COUNT(DISTINCT ISBN) > 1
```

* Find the Authors for which the library has more than one book in inventory (this includes multiple copies of the same book).

```
SELECT Author
FROM Titles
INNER JOIN Inventory
ON Titles.ISBN = Inventory.ISBN
GROUP BY Author
HAVING COUNT(DISTINCT Serial) > 1
```

* The library wants to implement a customer loyalty program based on how many books each patron has checked out. Provide an SQL query that returns the names, number of books they have checked out, and loyalty level of each Patron. 

```
SELECT Name, COUNT(Serial) AS BookCount,
	CASE WHEN COUNT(Serial) > 2 THEN 'Platinum'
	WHEN COUNT(Serial) = 2 THEN 'Gold'
	WHEN COUNT(Serial) = 1 THEN 'Silver'
	ELSE 'Bronze' END as LoyaltyLevel
FROM Patrons
LEFT JOIN CheckedOut
ON Patrons.CardNum = CheckedOut.CardNum
GROUP BY Patrons.Name
ORDER BY BookCount DESC
```
