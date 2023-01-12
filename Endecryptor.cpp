//
// Created by bytte on 12.01.2023.
//

#include <string>
#include <cstdlib>
#include <vector>

#include "Endecryptor.h"
#include "DateTime.h"

unsigned int Endecryptor::calcSeed(std::string pass, Date* date) {
    unsigned int seed = date->day + date->month + date->year;
    for (int i = 0; i < pass.size(); i++) {
        seed += pass[i];
    }
    seed *= date->second % 10;
    return seed;
}

std::vector<int> Endecryptor::encrypt(
        std::string toEncrypt, std::string pass, Date* date) {

    std::vector<int> result(toEncrypt.size(), 0);

    srand(calcSeed(pass, date));
    for (int i = 0; i < toEncrypt.size(); i++) {
        int offset = rand() % 200 - 100;
        result.at(i) = toEncrypt[i] + offset;
    }

    return result;
}

std::string Endecryptor::decrypt(
        std::vector <int> toDecrypt, std::string pass, Date* date) {

    std::string result = "";
    srand(calcSeed(pass, date));

    for (int i = 0; i < toDecrypt.size(); i++) {
        int offset = rand() % 200 - 100;
        result.push_back(toDecrypt.at(i) - offset);
    }

    return result;
}
