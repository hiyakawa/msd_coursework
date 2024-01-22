//
//  PoliStructs.h
//  PoliStructs
//
//  Created by Laura Zhang on 8/30/22.
//

#ifndef PoliStructs_h
#define PoliStructs_h

#include <string>
#include <vector>
#include <list>

struct Politician {
    std::string name;               // name of the politician
    std::string party;              // party affiliation (Cplusers or Javacans)
    std::string state_or_federal;   // whether they're a state or federal politicia
};

std::vector<Politician> Javacans(std::vector<Politician> all_politicians);

std::list<std::string> federalCplusers(std::vector<Politician> all_politicians);

void politicianVectorPrinter(std::vector<Politician> all_politicians);

void stringListPrinter(std::list<std::string> all_politicians);

void errorExit(std::string message);

#endif /* PoliStructs_h */
