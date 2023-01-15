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
    void init(const std::string& password);
    bool open(const std::string& password);
    std::vector<entry> readQuery(std::string query);
    std::vector<entry>* readAll();
    std::vector<std::string> readCategories();
    void add(const entry& entry);
    void remove(int index);
    void removeCategory(std::string category);
    void close();
private:
    std::vector<int> stringToVector(const std::string& str);

    std::vector<entry> database;
    std::string databasePassword;

};


#endif //PASSWORDMANAGER_DATABASECONNECTOR_H
