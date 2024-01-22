//
// Crypto Homework 1: Blocks and Streams
// Programming Part 2: RC4 Cypher
// Muyuan Zhang
//

#include "blockCypher.h"
#include "RC4Cypher.h"

RC4::RC4(std::string& password) {
    generateKey(password, key_);
    initTable(key_);
}

void RC4::initTable(const uint8_t* key) {
    for (int i = 0; i < 256; ++i) {
        arr_[i] = i;
    }

    int offset = 0;

    for (int i = 0; i < 256; ++i) {
        offset = (offset + arr_[i] + key[i % 8]) % 256;
        std::swap(arr_[i], arr_[offset]);
    }
}

std::string RC4::encrypt(std::string& message) {
    ciphertext_ = "";
    int i = 0;
    int j = 0;

    for (char k : message) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;

        std::swap(arr_[i], arr_[j]);
        ciphertext_.push_back(arr_[(arr_[i] + arr_[j]) % 256] ^ k);
    }

    return ciphertext_;
}

std::string RC4::decrypt(uint8_t key[8]) {
    initTable(key);
    std::string decrypted;
    int i = 0;
    int j = 0;

    for (char k : ciphertext_) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;

        std::swap(arr_[i], arr_[j]);
        decrypted.push_back(arr_[(arr_[i] + arr_[j]) % 256] ^ k);
    }

    return decrypted;
}

std::string RC4::decrypt(const std::string& encryptedText) {
    initTable(key_);
    std::string decrypted;
    ciphertext_ = "";
    int i = 0;
    int j = 0;

    for (char k : encryptedText) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;
        std::swap(arr_[i], arr_[j]);
        decrypted.push_back(arr_[(arr_[i] + arr_[j]) % 256] ^ k);
    }

    return decrypted;
}

uint8_t* RC4::getKey() {
    return key_;
}