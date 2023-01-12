//
// Created by bytte on 12.01.2023.
//

#ifndef PASSWORDMANAGER_DATABASECONNECTOR_H
#define PASSWORDMANAGER_DATABASECONNECTOR_H

#include <vector>
#include "entry.h"


class DatabaseConnector {
public:


public:
    bool open(std::string databasePassword);
    entry read(std::string name);
    std::vector<entry> readAll();
    void add(entry entry);
    void remove(std::string);
    void close();
private:
    std::vector<int> stringToVector(std::string str);
    int find(std::string name);

    std::vector<entry> database;
    std::string databasePassword;

};


#endif //PASSWORDMANAGER_DATABASECONNECTOR_H