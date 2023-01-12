//
// Created by bytte on 12.01.2023.
//

#include "Tui.h"
#include <iostream>

void Tui::run() {
    bool stop = false;
    while (!stop) {
        std::string option;
        std::cout << "=====================================" << std::endl;
        std::cout << "Nameless Password Manager by Adam Bem" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "1. Create new entry" << std::endl;
        std::cout << "2. Search database" << std::endl;
        std::cout << "q - exit" << std::endl;

        std::cout << "> ";
        std::cin >> option;
        std::cout << std::endl;

        if (option == "q") {
            stop = true;
        }

    }
}
