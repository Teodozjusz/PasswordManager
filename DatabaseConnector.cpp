//
// Created by bytte on 12.01.2023.
//

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include "DatabaseConnector.h"
#include "Endecryptor.h"

void DatabaseConnector::init(std::string databasePassword) {
    std::ofstream databaseWriter("database.txt");
    std::time_t timestamp = std::time(nullptr);
    databaseWriter << timestamp << std::endl;

    tm* now = std::localtime(&timestamp);
    Endecryptor endecryptor;
    std::vector<int> controlSum = endecryptor.encrypt("69", databasePassword, now);
    for (int i = 0; i < controlSum.size(); i++) {
        databaseWriter << controlSum.at(i);
        if (i < controlSum.size() - 1) {
            databaseWriter << " ";
        }
    }
    databaseWriter << std::endl;
    this->open(databasePassword);

}

bool DatabaseConnector::open(std::string databasePassword) {
    this->databasePassword = databasePassword;
    database = std::vector<entry>();
    std::ifstream databaseReader("database.txt");

    std::string unixTimeStr;
    std::getline(databaseReader, unixTimeStr);
    time_t unixTime = stoll(unixTimeStr);
    tm* timestamp = std::localtime(&unixTime);

    Endecryptor endecryptor;
    std::string controlString;
    getline(databaseReader, controlString);
    std::vector controlVector = this->stringToVector(controlString);
    std::string controlSum = endecryptor.decrypt(controlVector, databasePassword, timestamp);
    if (controlSum != "69")
        return false;

    std::string s;
    while (!databaseReader.eof()) {
        std::string name;
        std::string pass;
        std::string category;
        for (int i = 0; i < 3; i++) {
            std::getline(databaseReader, s);
            if (s.empty()) return true;
            std::vector<int> line = this->stringToVector(s);
            switch (i) {
                case 0:
                    name = endecryptor.decrypt(line, databasePassword, timestamp);
                    break;
                case 1:
                    pass = endecryptor.decrypt(line, databasePassword, timestamp);
                    break;
                case 2:
                    category = endecryptor.decrypt(line, databasePassword, timestamp);
                    break;
            }

        }
        entry entry = {name, pass, category};
        database.push_back(entry);

    }
    return true;
}

std::vector<entry>* DatabaseConnector::readAll() {
    return &this->database;
}

std::vector<entry> DatabaseConnector::readQuery(std::string query) {
    std::vector<entry> result;
    std::transform(query.begin(), query.end(),query.begin(), ::tolower);
    for (entry e : database) {
        std::transform(e.name.begin(), e.name.end(), e.name.begin(), ::tolower);
        std::transform(e.category.begin(), e.category.end(),e.category.begin(), ::tolower);
        if (e.name == query || e.category == query)
            result.push_back(e);

    }
    return result;
}

void DatabaseConnector::add(entry entry) {
    database.push_back(entry);
}

void DatabaseConnector::remove(int index) {
    database.erase(database.begin() + index);
}

int DatabaseConnector::findIndex(std::string query) {
    for (int i = 0; i < database.size(); ++i) {
        if (database.at(i).name == query || database.at(i).category == query)
            return i;
    }
    return -1;
}

std::vector<int> DatabaseConnector::stringToVector(std::string str) {
    std::vector<int> result;
    std::string delimiter = " ";
    size_t start = 0;
    size_t end;

    while ((end = str.find(delimiter, start)) != std::string::npos) {
        int number = stoi(str.substr(start, end - start));
        result.push_back(number);
        start = end + delimiter.length();
    }
    result.push_back(stoi(str.substr(start)));

    return result;
}

void DatabaseConnector::close() {
    std::ofstream databaseWriter("database.txt");
    std::time_t timestamp = std::time(nullptr);
    databaseWriter << timestamp << std::endl;
    tm* now = std::localtime(&timestamp);
    Endecryptor endecryptor;

    std::vector<int> controlSum = endecryptor.encrypt("69", databasePassword, now);
    for (int i = 0; i < controlSum.size(); i++) {
        databaseWriter << controlSum.at(i);
        if (i < controlSum.size() - 1) {
            databaseWriter << " ";
        }
    }
    databaseWriter << std::endl;

    for (entry e : database) {
        std::vector<int> toEncrypt = endecryptor.encrypt(e.name, this->databasePassword, now);
        for (int i = 0; i < toEncrypt.size(); i++) {
            databaseWriter << toEncrypt.at(i);
            if (i < toEncrypt.size() - 1) {
                databaseWriter << " ";
            }
        }
        databaseWriter << std::endl;

        toEncrypt = endecryptor.encrypt(e.pass, this->databasePassword, now);
        for (int i = 0; i < toEncrypt.size(); i++) {
            databaseWriter << toEncrypt.at(i);
            if (i < toEncrypt.size() - 1) {
                databaseWriter << " ";
            }
        }
        databaseWriter << std::endl;

        toEncrypt = endecryptor.encrypt(e.category, this->databasePassword, now);
        for (int i = 0; i < toEncrypt.size(); i++) {
            databaseWriter << toEncrypt.at(i);
            if (i < toEncrypt.size() - 1) {
                databaseWriter << " ";
            }
        }
        databaseWriter << std::endl;

    }
}

std::vector<std::string> DatabaseConnector::readCategories() {
    std::vector<std::string> result;
    for (entry e : database) {
        if (!result.empty()) {
            bool isFound = false;
            for (std::string category : result) {
                if (category == e.category) {
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                result.push_back(e.category);

        }
        else
            result.push_back(e.category);

    }

    return result;
}

