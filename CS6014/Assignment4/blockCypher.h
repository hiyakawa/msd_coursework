//
// Crypto Homework 1: Blocks and Streams
// Programming Part 1: A (bad) block cypher
// Muyuan Zhang
//

#pragma once

#include <cstdint>
#include <string>

void generateKey(const std::string& password, uint8_t(& key)[8]);
void generateSubstTables(uint8_t(& substTables)[8][256]);
void encrypt(const uint8_t* key, uint8_t(& substTables)[8][256],
             uint8_t(& plaintext)[11], uint8_t n);
void decrypt(const uint8_t* key, uint8_t(& substTables)[8][256],
             uint8_t(& plaintext)[11], uint8_t n);
void XOR(const uint8_t* key, uint8_t(& plaintext)[11], uint8_t n);
