//
// Created by bytte on 12.01.2023.
//

#ifndef PASSWORDMANAGER_ENDECRYPTOR_H
#define PASSWORDMANAGER_ENDECRYPTOR_H


#include <string>
#include <vector>

class Endecryptor {

private:
    unsigned int calcSeed(const std::string& pass, tm* date);
public:
    std::vector<int> encrypt(std::string toEncrypt, const std::string& pass, tm* date);

    std::string decrypt(const std::vector<int>& toDecrypt, const std::string& pass, tm* date);

};


#endif //PASSWORDMANAGER_ENDECRYPTOR_H
