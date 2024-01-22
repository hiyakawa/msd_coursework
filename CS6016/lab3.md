# CS6016 Lab 3: Relational Algebra

## Part 1 - Joins

### 1

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|20|a|5|20|b|6|
|20|a|5|20|b|5|

### 2

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|25|b|8|20|b|6|
|25|b|8|20|b|5|

### 3

|A|Q|R|B|C
|---|---|---|---|---|
|20|a|5|b|6|
|20|a|5|b|5|

### 4

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|20|a|5|20|b|5|

## Part 2 - Chess Queries

### 1

$ \Pi_{Name}(\sigma_{Elo \geq 2850}(Players)) $

### 2

$ \Pi_{Name}(Players \bowtie_ {Players.pID = Games.wpID}Games)$

### 3

$ \Pi_{Name}(Players \bowtie_ {Players.pID = Games.wpID \wedge Games.Result = 1-0}Games)$

### 4

$ \Pi_{Players.Name}(Players \bowtie_{Players.pID = Games.wpID \vee Players.pID = Games.bpID}(Events \bowtie_{Events.eID = Games.eID \wedge Events.Year = 2018}Games))$

### 5

$ \Pi_{Events.Name, Year}(Events \bowtie_{Events.eID = Games.eID}(\sigma_{Name = Magnus \ Carlson}(Players \bowtie_{(pID = wpID\ \wedge \ Result = 0-1)\ \vee \ (pID = bpID \ \wedge \ Result = 1-0)}Games)))$

### 6

$ \Pi_{Name}(\sigma_{Name \neq Magnus \ Carlson}(Players \bowtie_ {Players.pID = Games.wpID \vee Players.pID = Games.bpID}(\Pi_{wpID, bpID}(\sigma_{Name = Magnus \ Carlson}(Players \bowtie_ {pID = wpID \vee pID = bpID}Games))))$


## Part 3 - LMS Queries

### Part 3.1

#### a)

$ \rho(C, \pi_{sid}(\sigma_{Grd=C}(Enrolled)))$

|C.sID|
|---|
|3|
|4|

$\pi_{Name}((\pi_{sid}(Enrolled) - C)\bowtie Students)$

|Students.Name|
|---|
|Hermione|
|Harry|

#### b)

+ The query is searching for students who got a C from the Enrolled schema, projects sID column and renames the relation as C.

+ The query removes sID 3 and 4 from the Enrolled schema, isolates the sID 1 and 2 using natural join and projects the Name attribute.

### Part 3.2

#### a)

$ \rho(S1, Students) $

|S1.sID|S1.Name|S1.DOB|
|---|---|---|
|1|Hermione|1980|
|2|Harry|1979|
|3|Ron|1980|
|4|Malfoy|1982|

$ \rho(S2, Students) $

|S2.sID|S2.Name|S2.DOB|
|---|---|---|
|1|Hermione|1980|
|2|Harry|1979|
|3|Ron|1980|
|4|Malfoy|1982|

$ \pi_{S2.Name}(\sigma_{S1.Name == Ron \wedge S1.DOB == S2.DOB \wedge S2.name != Ron}(S1 \times S2))$

|S2.Name|
|---|
|Hermione|

#### b)

The query is searching for students with the same DOB as Ron apart from himself.

### Part 3.3

#### a)

$\pi_{Name}((\pi_{cid, sid}(Enrolled)/\pi_{sid}(Students))\bowtie Courses)$

|Courses.Name|
|---|

#### b)

The query is searching for the course names taken by every single student.

## Part 4

$ \Pi_{Name}((\Pi_{sID, cID}(Enrolled) / \Pi_{cID}(\sigma_{cID \geq 3000 \wedge cID \geq 4000}(Enrolled))) \bowtie Students) $