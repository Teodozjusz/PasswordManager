#include <iostream>
#include <ctime>
#include "Endecryptor.h"

int main() {

//    std::time_t timestamp=std::time(nullptr);
//    std::cout << timestamp << std::endl;
//    tm* local=std::localtime(&timestamp);
    //std::cout<<std::asctime(local)<<std::endl;

    std::time_t time = 1673519010;
    tm* time1 = std::localtime(&time);
    std::cout << time1->tm_hour << std::endl;

//    Endecryptor endecryptor;
//
//    std::string pass = "qwertyuiop";
//    std::time_t timestamp=std::time(nullptr);
//    tm* local=std::localtime(&timestamp);
//
//    std::string text = "dupa123";
//    std::cout << "Before: " << text << std::endl;
//
//    std::vector<int> encryptedPass =
//            endecryptor.encrypt(text, pass, local);
//
//    std::cout << "Encrypted: ";
//    for (int i = 0; i < encryptedPass.size(); i++) {
//        std::cout << encryptedPass.at(i) << " ";
//    }
//    std::cout << std::endl;
//
//    std::string decrypted =
//            endecryptor.decrypt(encryptedPass, pass, local);
//
//    std::cout << "After: " << decrypted << std::endl;


}
