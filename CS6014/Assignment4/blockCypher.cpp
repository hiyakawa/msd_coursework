//
// Crypto Homework 1: Blocks and Streams
// Programming Part 1: A (bad) block cypher
// Muyuan Zhang
//

#include "blockCypher.h"
#include <random>

void XOR(const uint8_t* key, uint8_t(& plaintext)[11], uint8_t n) {
    for (int i = 0; i < n; ++i) {
        plaintext[i] = plaintext[i] ^ key[i % 8];
    }
}

void generateKey(const std::string& password, uint8_t(& key)[8]) {
    // use a very insecure "hash" of an arbitrary length password
    for (int i = 0; i < password.length(); ++i) {
        key[i % 8] = key[i % 8] ^ password[i];
    }
}

void generateSubstTables(uint8_t(& substTables)[8][256]) {
    // 8 substitution tables (each acting on 1 byte)
    for (int i = 0; i < 8; ++i) {
        // represent the substitution as a 256 element array
        for (int j = 0; j < 256; ++j) {
            substTables[i][j] = j;
        }

        // shuffle the substitution table
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(substTables[i]),
                     std::end(substTables[i]), g);
    }
}

void encrypt(const uint8_t* key, uint8_t(& substTables)[8][256],
             uint8_t(& plaintext)[11], uint8_t n) {
    for (int j = 0; j < 16; ++j) {
        XOR(key, plaintext, n);

        for (int i = 0; i < n; ++i) { // substitute
            plaintext[i] = substTables[i % 8][plaintext[i]];
        }

        uint8_t msbFirstByte = plaintext[0] >> 7;
        for (int i = 0; i < n - 1; ++i) {
            // rotate the entire state 1 bit to the left
            plaintext[i] = plaintext[i] << 1 | plaintext[i + 1] >> 7;
        }

        plaintext[n - 1] = (plaintext[n - 1] << 1) | msbFirstByte;
    }
}

void decrypt(const uint8_t* key, uint8_t(& substTables)[8][256],
             uint8_t(& plaintext)[11], uint8_t n) {
    for (int j = 0; j < 16; ++j) {
        uint8_t lsbCurrentByte = plaintext[n - 1] << 7;
        
        for (int i = 0; i < n; ++i) {
            uint8_t lsbNextByte = plaintext[i] << 7;
            plaintext[i] = (plaintext[i] >> 1) | lsbCurrentByte;
            lsbCurrentByte = lsbNextByte;
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int k = 0; k < 256; ++k) {
                if (plaintext[i] == substTables[i % 8][k]) {
                    plaintext[i] = k;
                    break;
                }
            }
        }

        XOR(key, plaintext, n);
    }
}
