# Book Analyzer

#### Muyuan Zhang

## Commands

```
$ clang++ -std=c++17 -c *.cpp
$ clang++ -o BookAnalyzer *.o
```

## Input & Output Example

```
$ ./BookAnalyzer

Usage message:

No input file is given!
```

```
$ ./BookAnalyzer mobydick.txt

Usage message:

No key word is given!
```

```
$ ./BookAnalyzer mobydick.txt weltering

Statistics for Moby-Dick; or The Whale by unknown:

  Number of words: 215864
  
  Number of characters: 1033936
  
  The shortest word is "a", and the longest word is "matches?—tinder?—gunpowder?—what"
  
  

The word "weltering" appears 3 times:

  at 4%: "ship weltering there"
  
  at 40%: "up weltering astern."
  
  at 97%: "the weltering sea."
```

```
$ ./BookAnalyzer test.txt fox
 
Statistics for unknown by unknown:

  Number of words: 9
  
  Number of characters: 37
  
  The shortest word is "fox", and the longest word is "jumped"
  
  

The word "fox" appears 1 times:

  at 35%: "brown fox jumped"
```

```
$ ./BookAnalyzer nosuchfile.txt weltering

Usage message: nosuchfile.txt

This file does not exist!
```

```
$ ./BookAnalyzer test.txt fox and something else

Usage message:

Too many arguments entered!
```
