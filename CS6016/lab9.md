# CS6016 Lab 9: Indexes

## Part 1 - Selecting Indexes

### A database contains the following table for former-employee records

+ Find all employees that started after a certain date
+ Find all employees that started on a certain date, and worked until at least another certain date

A: ("Start Date", "End Date"). This secondary index can optimize the query on employees that started after a certain date, and also on employees that started on a certain date and worked until at least another certain date

### A database contains the following table for tracking student grades in classes

+ Get all students with a grade better than 'B' - ("Grade")
+ Get all classes where any student earned a grade worse than 'D' - ("Grade")
+ Get all classes ordered by class name - ("className")
+ Get all students who earned an 'A' in a certain class - ("className", "Grade")

A: ("Grade"), ("className", "Grade").

### Queries on the chess database

+ select Name from Players where Elo >=2050;

A: ("Elo")

+ select Name, gID from Players join Games where pID=WhitePlayer;

A: ("WhitePlayer"), for `pID` is already the primary index of `Games`.

### Queries on the public Library database

+ select * from Inventory natural join CheckedOut;

A: Do not need to add any other indexes, for the primary index of both tables is `Serial`.

### More library queries

+ select * from Inventory natural join CheckedOut where CardNum=2;

A: ("CheckedOut.CardNum"). The primary index of both tables is `Serial`, so only CheckedOut.CardNum needs to create index.

+ select * from Patrons natural join CheckedOut;

A: ("CheckedOut.CardNum"). The join of the two tables is on `CardNum` which is the shared field, and `Patrons.CardNum` is already the primary index.

### Still more library queries

A: ("Inventory.ISBN"). `Inventory.Serial` is the primary index, so `Inventory.ISBN` needs to create an index.

## Part 2 - B+ Tree Index Structures

### Students table

+ How many rows of the table can be placed into the first leaf node of the primary index before it will split?

A: `sID`, 4 bytes; `className`, 10 bytes; `Grade`, 1 byte. 4096 / (4 + 10 + 1) = 273.

+ What is the maximum number of keys stored in an internal node of the primary index? (Remember to ignore pointer space. Remember that internal nodes have a different structure than leaf nodes.)

A: `sID`, 4 bytes; `className`, 10 bytes. 4096 / (4 + 10) = 292.

+ What is the maximum number of rows in the table if the primary index has a height of 1? (A tree of height 1 has 2 levels and requires exactly one internal node)

A: (292 + 1) * 273 = 79989 rows.

+ What is the minimum number of rows in the table if the primary index has a height of 1? (A tree of height 1 has 2 levels). The minimum capacity of a node in a B+ tree is 50%, unless it is the only internal/leaf node. The minimum number of children of a root node is 2.

A: 273 + 1 = 274 rows.

+ If there is a secondary index on Grade, what is the maximum number of entries a leaf node can hold in the secondary index?

A: 4096 / (4 + 1) = 819.

### Another table

+ What is the maximum number of leaf nodes in the primary index if the table contains 48 rows?

A: Max rows on each leaf node is 4096 / 128 = 32. Min rows on each leaf node is 32 / 2 = 16. Max leaf nodes is 48 / 16 = 3.

+ What is the minimum number of leaf nodes in the primary index if the table contains 48 rows?

A: 48 / 32 = 2
