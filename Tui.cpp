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

/**
 * Method that starts the interface.
 */
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
        std::cout << "2. List database" << std::endl;
        std::cout << "3. Add password" << std::endl;
        std::cout << "4. Edit password" << std::endl;
        std::cout << "5. Delete password" << std::endl;
        std::cout << "6. Delete category" << std::endl;
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
            case 6:
                this->removeCategory();
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

/**
 * Method used to handle "Add new password" option.
 */
void Tui::add() {
    std::string category;
    std::string name;
    std::string generate;
    std::string pass;

    this->listCategories();
    std::cout << "You can also something else to create new category." << std::endl;
    std::cout << "Category > ";
    std::cin >> category;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name > ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Generate password? [Y/n] > ";
    generate = std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (generate == "n" || generate == "N") {
        std::cout << "Password > ";
        std::cin >> pass;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        pass = generatePassword();
    }

    entry newEntry = {name, pass, category};
    databaseConnector.add(newEntry);
    std::cout << "Element added." << std::endl;
    this->hold();

}
/**
 * Method used to handle "List database" option.
 */
void Tui::listAll() {
    std::vector<entry>* data = this->databaseConnector.readAll();
    for (const entry& e : *data) {
        std::cout << "======================" << std::endl;
        std::cout << "Category: " << e.category << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }
    this->hold();

}

/**
 * Method used to handle "Search database" option.
 */
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
        std::cout << "Category: " << e.category << std::endl;
        std::cout << "Name: " << e.name << std::endl;
        std::cout << "Password: " << e.pass << std::endl << std::endl;
    }
    this->hold();
}

/**
 * Method used to handle "Remove password" option.
 */
void Tui::remove() {
    this->listAllShort();
    int index;
    std::cout << "Select element to delete (0 to cancel) > ";
    std::cin >> index;
    if (index == 0) return;
    databaseConnector.remove(index - 1);
    std::cout << "INFO: Element " << index << " removed." << std::endl;
    this->hold();
}

/**
 * Method used to handle "Remove category" option.
 */
void Tui::removeCategory() {
    this->listCategories();
    std::string category;
    std::cout << "Category to remove > ";
    std::cin >> category;
    databaseConnector.removeCategory(category);
}

/**
 * Method used to handle "Edit password" option.
 */
void Tui::edit() {
    this->listAllShort();
    std::vector<entry>* data = this->databaseConnector.readAll();

    int index;
    std::string newCategory;
    std::string newName;
    std::string newPass;
    char generate;
    std::cout << "Select element to edit (0 to cancel) > ";
    std::cin >> index;
    if (index == 0) return;
    entry* entry = &data->at(index - 1);

    this->listCategories();
    std::cout << "You can also something else to create new category." << std::endl;
    std::cout << "New category [" << entry->category << "] > ";
    std::cin >> entry->category;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "New name [" << entry->name << "] > ";
    std::cin >> entry->name;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Do you want new password? [y/N] > ";
    std::cin >> generate;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (generate == 'y' || generate == 'Y') {
        std::cout << "Generate new password? [Y/n] > ";
        std::cin >> generate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (generate == 'n' || generate == 'N') {
            std::cout << "New password > ";
            std::cin >> entry->pass;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            entry->pass = generatePassword();
        }
    }

    std::cout << "INFO: Changes has been made." << std::endl;
    this->hold();
}

/**
 * Method used to determine how strong password user wants
 * and execute method to generate it
 * @return generated password
 */
std::string Tui::generatePassword() {
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
            return generatePasswordString(length, false, false);
        case 2:
            return generatePasswordString(length, true, false);
        case 3:
        default:
            return generatePasswordString(length, true, true);

    }
}

/**
 * Method that generates password using provided parameters
 * @param length of wanted password
 * @param bigLetters if password has to contain big letters
 * @param specialChars if password has to contain special characters.
 *                     Needs bigLetters set to true to work.
 * @return generated password.
 */
std::string Tui::generatePasswordString(int length, bool bigLetters, bool specialChars) {
    std::string result;
    time_t time = std::time(nullptr);
    tm* now = std::localtime(&time);
    srand(now->tm_min * now->tm_sec + now->tm_mday);
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

/**
 * Method that prints names of all entries in database in compact list
 */
void Tui::listAllShort() {
    std::vector<entry>* data = this->databaseConnector.readAll();
    for (int i = 0; i < data->size(); ++i) {
        std::cout << i + 1 << ". " << data->at(i).name << std::endl;
    }
}

/**
 * Method that holds program until pressing Enter key.
 */
void Tui::hold() {
    std::cout << "INFO: Press Enter to continue. ";
    std::cin.get();
}

/**
 * Method that lists categories (5 per row).
 */
void Tui::listCategories() {
    std::vector<std::string> categories = databaseConnector.readCategories();
    std::cout << "Categories: ";
    for (int i = 0; i < categories.size(); ++i) {
        std::cout << categories.at(i);
        if (i % 5 == 0 && i > 0 && i != categories.size() - 1)
            std::cout << ", " << std::endl;
        else if ( i != categories.size() - 1 )
            std::cout << ", ";
    }
    std::cout << std::endl;

}







