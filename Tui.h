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
    void add();
    void readDatabase();

private:
    DatabaseConnector databaseConnector;
};


#endif //PASSWORDMANAGER_TUI_H
