//
// Crypto Homework 1: Blocks and Streams
// Programming Part 2: RC4 Cypher
// Muyuan Zhang
//

#pragma once

#include <cstdint>
#include <string>
#include <iostream>

class RC4 {
    uint8_t arr_ [256];
    uint8_t key_ [8];
    std::string plaintext_;
    std::string ciphertext_;

public:
    RC4(std::string& password);
    void initTable(const uint8_t* key);
    std::string encrypt(std::string& message);
    std::string decrypt(uint8_t key[8]);
    std::string decrypt(const std::string& encryptedText);
    uint8_t* getKey();
};
