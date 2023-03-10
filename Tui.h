//
// Created by bytte on 12.01.2023.
//

#ifndef PASSWORDMANAGER_TUI_H
#define PASSWORDMANAGER_TUI_H

#include <string>
#include "DatabaseConnector.h"

class Tui {
public:
    void run();

private:
    DatabaseConnector databaseConnector;

    void add();
    void listAll();
    void listQuery();
    void edit();
    void remove();
    void removeCategory();

    void listCategories();
    void listAllShort();
    static std::string generatePassword();
    static std::string generatePasswordString(int length, bool bigLetters, bool specialChars);
    void hold();
};


#endif //PASSWORDMANAGER_TUI_H
