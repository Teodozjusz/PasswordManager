//
// Created by bytte on 12.01.2023.
//

#include <string>
#include <cstdlib>
#include <vector>

#include "Endecryptor.h"
#include "DateTime.h"


unsigned int Endecryptor::calcSeed(std::string pass, tm* date) {
    unsigned int seed = date->tm_mday + date->tm_mon + date->tm_year + 1900;
    for (int i = 0; i < pass.size(); i++) {
        seed += pass[i];
    }
    seed *= date->tm_sec % 10;
    return seed;
}

std::vector<int> Endecryptor::encrypt(
        std::string toEncrypt, std::string pass, tm* date) {

    std::vector<int> result(toEncrypt.size(), 0);

    srand(calcSeed(pass, date));
    for (int i = 0; i < toEncrypt.size(); i++) {
        int offset = rand() % 200 - 100;
        result.at(i) = toEncrypt[i] + offset;
    }

    return result;
}

std::string Endecryptor::decrypt(
        std::vector <int> toDecrypt, std::string pass, tm* date) {

    std::string result = "";
    srand(calcSeed(pass, date));

    for (int i = 0; i < toDecrypt.size(); i++) {
        int offset = rand() % 200 - 100;
        result.push_back(toDecrypt.at(i) - offset);
    }

    return result;
}
