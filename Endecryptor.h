//
// Created by bytte on 12.01.2023.
//

#ifndef PASSWORDMANAGER_ENDECRYPTOR_H
#define PASSWORDMANAGER_ENDECRYPTOR_H


#include <string>
#include <vector>

#include "DateTime.h"

class Endecryptor {

private:
    unsigned int calcSeed(std::string pass, Date* date);
public:
    std::vector<int> encrypt(std::string toEncrypt, std::string pass, Date* date);

    std::string decrypt(std::vector<int> toDecrypt, std::string pass, Date* date);

};


#endif //PASSWORDMANAGER_ENDECRYPTOR_H
