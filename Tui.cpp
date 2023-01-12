//
// Created by bytte on 12.01.2023.
//

#include "Tui.h"
#include <iostream>
#include <limits>
#include <filesystem>
#include "Endecryptor.h"
#include "DatabaseConnector.h"

namespace fs=std::filesystem;
void Tui::run() {
    fs::path path("database.txt");
    std::string databasePassword;
    if (exists(path)) {
        do {
            std::cout << "Database password: ";
            std::cin >> databasePassword;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        } while (!databaseConnector.open(databasePassword));
    }
    else {
        std::cout << "INFO: Database not found, creating new." << std::endl;
        std::cout << "Enter password for new database: ";
        std::cin >> databasePassword;
        databaseConnector.init(databasePassword);
    }


    bool stop = false;
    while (!stop) {
        int option = -1;

        std::cout << "=====================================" << std::endl;
        std::cout << "Nameless Password Manager by Adam Bem" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "1. Search database" << std::endl;
        std::cout << "2. List sorted database" << std::endl;
        std::cout << "3. Add password" << std::endl;
        std::cout << "4. Edit password" << std::endl;
        std::cout << "5. Delete password" << std::endl;
        std::cout << "6. Add category" << std::endl;
        std::cout << "7. Delete category" << std::endl;
        std::cout << "9. Exit" << std::endl;

        std::cout << "> ";
        if(!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << std::endl;

        switch (option) {
            case 1:
            case 2:
                this->readDatabase();
                break;
            case 3:
                this->add();
                break;
            case 9:
                stop = true;
                std::cout << "Closing." << std::endl;
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

    entry newEntry = {name, pass};
    databaseConnector.add(newEntry);

}

void Tui::readDatabase() {
    std::vector<entry> data = this->databaseConnector.readAll();
    for (const entry& e : data) {
        std::cout << "======================" << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }


}
