#include <iostream>
#include "Endecryptor.h"
#include "DateTime.h"

int main() {

    Endecryptor endecryptor;


    std::string pass = "qwertyuiop";
    Date date(05, 01, 2000, 8, 10, 26);

    std::string text = "dupa123";
    std::cout << "Before: " << text << std::endl;

    std::vector<int> encryptedPass =
            endecryptor.encrypt(text, pass, &date);

    std::cout << "Encrypted: ";
    for (int i = 0; i < encryptedPass.size(); i++) {
        std::cout << encryptedPass.at(i) << " ";
    }
    std::cout << std::endl;

    std::string decrypted =
            endecryptor.decrypt(encryptedPass, pass, &date);

    std::cout << "After: " << decrypted << std::endl;


}
