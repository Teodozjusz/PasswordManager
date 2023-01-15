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
    void init(std::string databasePassword);
    bool open(std::string databasePassword);
    std::vector<entry> readQuery(std::string query);
    std::vector<entry>* readAll();
    std::vector<std::string> readCategories();
    void add(entry entry);
    void remove(int index);
    void removeCategory(std::string category);
    void close();
private:
    std::vector<int> stringToVector(std::string str);
    int findIndex(std::string query);

    std::vector<entry> database;
    std::string databasePassword;

};


#endif //PASSWORDMANAGER_DATABASECONNECTOR_H
