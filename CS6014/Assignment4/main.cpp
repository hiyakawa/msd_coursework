//
// Crypto Homework 1: Blocks and Streams
// Muyuan Zhang
//

#include "blockCypher.h"
#include "RC4Cypher.h"
#include <algorithm>

int main() {
    // test block cypher
    uint8_t key1[8];
    std::string password = "helloworld";
    generateKey(password, key1);
    
    uint8_t substTables[8][256];
    std::string message = "hello world";
    generateSubstTables(substTables);

    uint8_t n = 11;
    uint8_t plaintext_arr[11];

    for (uint8_t i = 0; i < 11; ++i) {
        plaintext_arr[i] = message[i];
    }

    encrypt(key1, substTables, plaintext_arr, n);
    std::cout << std::endl;
    decrypt(key1, substTables, plaintext_arr, n);

    for (int i = 0; i < 11; ++i) {
        if (plaintext_arr[i] != message[i]) {
            throw std::runtime_error("Block cypher failed!");
        }
    }

    // test RC4 cypher
    uint8_t key2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    RC4* rc4 = new RC4(password);
    std::string cipher1 = rc4->encrypt(message);

    generateKey(password, key2);
    std::string decrypted = rc4->decrypt(rc4->getKey());

    // Verify that decrypting a message with a different key1 than the encryption
    // key1 does not reveal the plaintext
    for (int i = 0; i < message.length(); ++i) {
        if (message[i] != decrypted[i]) {
            throw std::runtime_error("RC4 cypher Q1 failed!");
        }
    }

    bool check = false;
    decrypted = rc4->decrypt(key2);

    for (int i = 0; i < message.length(); ++i) {
        if (message[i] != decrypted[i]) {
            check = true;
        }
    }
    if (! check) {
        throw std::runtime_error("RC4 cypher failed!");
    }

    // Verify that encrypting 2 messages using the same keystream is insecure
    std::string cipher2 = rc4->encrypt(message);

    if (cipher1.length() > cipher2.length()) {
        n = cipher2.length();
    }
    else {
        n = cipher1.length();
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (cipher1[i] ^ cipher2[i]);
    }
    std::cout << std::endl;

    // Modify part of a message using a bit-flipping attack.
    RC4 salary = RC4((std::string &) "Salary");
    std::string two = "Your salary is $1000";
    std::string salaryEncrypted = salary.encrypt(two);
    std::string result;

    for (int i = 0; i < salaryEncrypted.length(); i++){
        if (i > 16 && i < 20){
            result += std::to_string(salaryEncrypted.at(i) ^ 0x09);
        }
        else if (i == 16) {
            result += std::to_string(salaryEncrypted.at(i) ^ 0x08);
        }
        else {
            result += salaryEncrypted[i];
        }
    }

    std::string decryptedSalary = salary.decrypt(result);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
