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
        std::cout << "Database password > ";
        std::cin >> databasePassword;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!databaseConnector.open(databasePassword)) {
            std::cout << "ERR: Wrong password." << std::endl;
            std::cout << "Database password > ";
            std::cin >> databasePassword;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    else {
        std::cout << "INFO: Database not found, creating new." << std::endl;
        std::cout << "Enter password for new database > ";
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
        std::cin >> option;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << std::endl;

        switch (option) {
            case 1:
                this->listQuery();
                break;
            case 2:
                this->listAll();
                break;
            case 3:
                this->add();
                break;
            case 4:
                this->edit();
                break;
            case 5:
                this->remove();
                break;
            case 9:
                stop = true;
                std::cout << "INFO: Closing." << std::endl;
                databaseConnector.close();
                break;
            default:
                std::cout << "ERR: Wrong option." << std::endl;
        }

    }
}

void Tui::add() {
    std::string name;
    std::string generate;
    std::string pass;

    std::cout << "Name > ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Generate password? [Y/n] > ";
    std::cin >> generate;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (generate == "n" || generate == "N") {
        std::cout << "Password > ";
        std::cin >> pass;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        int length;
        int strength;
        std::cout << "How strong do you want your password?" << std::endl;
        std::cout << "1. Only small letters" << std::endl;
        std::cout << "2. Small and big letters" << std::endl;
        std::cout << "3. Small and big letters + numbers + special characters" << std::endl;
        std::cout << "> ";
        std::cin >> strength;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "How long do you want your password? > ";
        std::cin >> length;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (strength) {
            case 1:
                pass = generatePassword(length, false, false);
                break;
            case 2:
                pass = generatePassword(length, true, false);
                break;
            case 3:
            default:
                pass = generatePassword(length, true, true);
                break;

        }
    }

    entry newEntry = {name, pass};
    databaseConnector.add(newEntry);
    std::cout << "Element added." << std::endl;
    this->hold();

}

void Tui::listAll() {
    std::vector<entry>* data = this->databaseConnector.readAll();
    for (const entry& e : *data) {
        std::cout << "======================" << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }
    this->hold();

}

void Tui::listQuery() {
    std::string query;
    std::cout << "Query: ";
    std::cin >> query;
    std::vector<entry> results = databaseConnector.readQuery(query);
    if (results.empty()) {
        std::cout << "INFO: No results." << std::endl;
    }
    for (entry e : results) {
        std::cout << "======================" << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }
    this->hold();
}

void Tui::remove() {
    this->listAllShort();
    std::vector<entry>* data = this->databaseConnector.readAll();
    int index;
    std::cout << "Select element to delete > ";
    std::cin >> index;
    databaseConnector.remove(index - 1);
    std::cout << "INFO: Element " << index << " removed." << std::endl;
    this->hold();
}

void Tui::edit() {
    this->listAllShort();
    std::vector<entry>* data = this->databaseConnector.readAll();

    int index;
    std::string newName;
    std::string newPass;
    std::cout << "Select element to edit > ";
    std::cin >> index;
    entry* entry = &data->at(index - 1);
    std::cout << "New name (Press Enter to keep "  << entry->name << ".) > ";
    std::cin >> newName;
    if ( !newName.empty() )
        entry->name = newName;
    std::cout << "New password (Press Enter to keep current) > ";
    std::cin >> newPass;
    if ( !newPass.empty() )
        entry->pass = newPass;

    std::cout << "INFO: Changes has been made." << std::endl;
}

std::string Tui::generatePassword(int length, bool bigLetters, bool specialChars) {
    std::string result;
    time_t time = std::time(nullptr);
    tm* now = std::localtime(&time);
    srand(now->tm_hour * now->tm_sec + now->tm_year);
    for (int i = 0; i < length; ++i) {
        char c;
        if (!bigLetters)
            c = rand() % 26 + 97;
        else if (!specialChars)
            c = rand() % 26 + 65 + (rand() % 2 * 32);
        else
            c = rand() % 94 + 33;

        result.push_back(c);
    }
    return result;
}

void Tui::listAllShort() {
    std::vector<entry>* data = this->databaseConnector.readAll();
    for (int i = 0; i < data->size(); ++i) {
        std::cout << i + 1 << ". " << data->at(i).name << std::endl;
    }
}

void Tui::hold() {
    std::cout << "INFO: Press Enter to continue. ";
    std::cin.get();
}


