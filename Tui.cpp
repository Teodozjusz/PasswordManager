//
// Created by bytte on 12.01.2023.
//

#include "Tui.h"
#include <iostream>
#include <ctime>
#include <limits>

#include "Endecryptor.h"
#include "DatabaseConnector.h"

void Tui::run() {
    std::string databasePassword;
    std::cout << "Database password: ";
    std::cin >> databasePassword;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    databaseConnector.open(databasePassword);

    bool stop = false;
    while (!stop) {
        int option;

        std::cout << "=====================================" << std::endl;
        std::cout << "Nameless Password Manager by Adam Bem" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "1. Create new entry" << std::endl;
        std::cout << "2. List database" << std::endl;
        std::cout << "0. exit" << std::endl;

        std::cout << "> ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option) {
            case 1:
                this->add();
                break;
            case 2:
                this->readDatabase();
                break;
            case 0:
                stop = true;
                databaseConnector.close();
                break;
            default:
                std::cout << "Wrong option." << std::endl;
        }

    }
}

void Tui::add() {
    std::string name;
    std::string pass;

    std::cout << "Name: ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Password: ";
    std::cin >> pass;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Endecryptor endecryptor;
    std::time_t time = std::time(nullptr);
    tm* timestamp = std::localtime(&time);

    std::cout << "Time: " << time << std::endl;

    std::vector<int> encryptedName =
            endecryptor.encrypt(name, "qwerty", timestamp);
    std::cout << "Name: ";
    for (int e : encryptedName) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::vector<int> encryptedPass = endecryptor.encrypt(pass, "qwerty", timestamp);
    std::cout << "Pass: ";
    for (int e : encryptedPass) {
        std::cout << e << " ";
    }
    std::cout << std::endl;



}

void Tui::readDatabase() {
    std::vector<entry> data = this->databaseConnector.readAll();
    for (const entry& e : data) {
        std::cout << "======================" << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }


}
