#include "Dialog.h"
#include <iostream>
#include "string"

Dialog::Dialog(std::istream & in, std::ostream & out) : in(in), out(out) {}

void Dialog::connectToApi(Builder* builder) {
    api = builder;
}

int Dialog::run() {
    if (api == nullptr) return 1;
    out << "Type your command or type help" << std::endl;

    while (true) {
        out << "\033[34m>>> \033[36m";

        std::string command;
        in >> command;
        std::string args;
        std::getline(in, args, '\n');

        out << "\033[0m";

        if (command == "exit") return 0;
        if (command == "help") {
            help();
            continue;
        }

        Response response = api->routeRequest(command, args);
        if (response.getResponseCode() == Ok) {
            if (!response.getResponse().empty())
                out << response.getResponse() << std::endl;
        } else {
            out << "Bad Request" << std::endl;
        }
    }

}

void Dialog::help() {
    out << "Examples of commands:" << std::endl;
    out << "0. help" << std::endl;
    out << "0. exit" << std::endl;
    out << "1. add i j value" << std::endl;
    out << "   adding value by index" << std::endl;
    out << "2. mk" << std::endl;
    out << "   make vector" << std::endl;
    out << "3. print" << std::endl;
    out << std::endl;
}


