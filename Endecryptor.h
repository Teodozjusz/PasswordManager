//
// Created by bytte on 12.01.2023.
//

#ifndef PASSWORDMANAGER_ENDECRYPTOR_H
#define PASSWORDMANAGER_ENDECRYPTOR_H


#include <string>
#include <vector>

class Endecryptor {

private:
    unsigned int calcSeed(std::string pass, tm* date);
public:
    std::vector<int> encrypt(std::string toEncrypt, std::string pass, tm* date);

    std::string decrypt(std::vector<int> toDecrypt, std::string pass, tm* date);

};


#endif //PASSWORDMANAGER_ENDECRYPTOR_H
