#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Created by bytte on 12.01.2023.
//

#include <string>
#include <cstdlib>
#include <vector>

#include "Endecryptor.h"

/**
 * Calculades seed using password and given timestamp
 * @param pass password
 * @param date given timestamp
 * @return seed
 */
unsigned int Endecryptor::calcSeed(const std::string& pass, tm* date) {
    unsigned int seed = date->tm_mday + date->tm_mon + date->tm_year + 1900;
    for (char c : pass) {
        seed += c;
    }
    seed *= date->tm_sec % 10;
    return seed;
}

/**
 * Encrypts string to vector of numbers from -200 to 200
 * @param toEncrypt string to encrypt
 * @param pass password used for encryption
 * @param date moment of ecryption
 * @return vector containing encrypted string
 */
std::vector<int> Endecryptor::encrypt(
        std::string toEncrypt, const std::string& pass, tm* date) {

    std::vector<int> result(toEncrypt.size(), 0);

    srand(calcSeed(pass, date));
    for (int i = 0; i < toEncrypt.size(); i++) {
        int offset = rand() % 200 - 100;
        result.at(i) = toEncrypt[i] + offset;
    }

    return result;
}

/**
 * Decrypts vector of ints back to string
 * @param toDecrypt encrypted data
 * @param pass password used to decryption
 * @param date moment of encryption
 * @return decrypted string
 */
std::string Endecryptor::decrypt(
        const std::vector <int>& toDecrypt, const std::string& pass, tm* date) {

    std::string result;
    srand(calcSeed(pass, date));

    for (int i : toDecrypt) {
        int offset = rand() % 200 - 100;
        result.push_back(i - offset);
    }

    return result;
}

#pragma clang diagnostic pop