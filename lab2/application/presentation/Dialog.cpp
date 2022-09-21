#include "Dialog.h"
#include <iostream>
#include "string"

Dialog::Dialog(std::istream & in, std::ostream & out) : in(in), out(out) {}

void Dialog::connectToApi(Builder* builder) {
    api = builder;
}

int Dialog::run() {
    if (api == nullptr) return 1;
    std::cout << "Type your command or type help" << std::endl;

    while (true) {
        std::cout << "\033[34m>>> \033[36m";

        std::string command;
        std::cin >> command;
        std::string args;
        std::getline(std::cin, args, '\n');
        if (args == " ") args = "";

        std::cout << "\033[0m";

        if (command == "exit") return 0;
        if (command == "help") {
            help();
            continue;
        }

        Response response = api->routeRequest(command, args);
        if (response.getResponseCode() == Ok) {
            if (!response.getResponse().empty())
                std::cout << response.getResponse() << std::endl;
        } else {
            std::cout << "Bad Request" << std::endl;
        }
    }

}

void Dialog::help() {
    std::cout << "Examples of commands:" << std::endl;
    std::cout << "0.   help" << std::endl;
    std::cout << "0.   exit" << std::endl;
    std::cout << "1.   R" << std::endl;
    std::cout << "        Show R" << std::endl;
    std::cout << "1.1. R 3.14" << std::endl;
    std::cout << "        set R" << std::endl;
    std::cout << "2.   cl" << std::endl;
    std::cout << "        Show curve Length" << std::endl;
    std::cout << "2.1. cl 2.64" << std::endl;
    std::cout << "        Show curve Length to angle" << std::endl;
    std::cout << "3.   cr 2.64" << std::endl;
    std::cout << "        Show curvature radius of angle" << std::endl;
    std::cout << "4.   s" << std::endl;
    std::cout << "        Show square" << std::endl;
    std::cout << "5.   x 3.14" << std::endl;
    std::cout << "        Show x(angle)" << std::endl;
    std::cout << "4.   y 3.14" << std::endl;
    std::cout << "        Show y(anlge)" << std::endl;
    std::cout << "6.   yx 0.5" << std::endl;
    std::cout << "        Show y(x)" << std::endl;
    std::cout << std::endl;
}


