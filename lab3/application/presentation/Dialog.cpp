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
            if (!response.getResponse().empty())
                std::cout << "Bad Request: " << response.getResponse() << std::endl;
            else
                std::cout << "Bad Request" << std::endl;
        }
    }

}

void Dialog::help() {
    std::cout << "Examples of commands:" << std::endl;
	std::cout << "0.   help" << std::endl;
	std::cout << "0.   exit" << std::endl;
    std::cout << "1.   setiarr signalState numberOfConnections ..." << std::endl;
    std::cout << "        Set new array of input terminals" << std::endl;
    std::cout << "        id, signalState and numberOfConnections must be positive integer " << std::endl;
    std::cout << "2.   setoarr signalState numberOfConnections ..." << std::endl;
    std::cout << "        Set new array of output terminals" << std::endl;
    std::cout << "        id, signalState and numberOfConnections must be positive integer " << std::endl;
    std::cout << "3.   print" << std::endl;
    std::cout << "        print all terminals" << std::endl;
    std::cout << "4.   t type id" << std::endl;
    std::cout << "        get Terminal by id" << std::endl;
    std::cout << "        type \"o\" means \"output\" " << std::endl;
    std::cout << "        type \"i\" means \"input\" " << std::endl;
    std::cout << "        id must be positive integer " << std::endl;
    std::cout << "5.   t type id signalState numberOfConnections" << std::endl;
    std::cout << "        set Terminal by id" << std::endl;
    std::cout << "        type \"o\" means \"output\" " << std::endl;
    std::cout << "        type \"i\" means \"input\" " << std::endl;
    std::cout << "        id, signalState and numberOfConnections must be positive integer " << std::endl;
    std::cout << "6.   addt type signalState numberOfConnections" << std::endl;
    std::cout << "        add newTerminal" << std::endl;
    std::cout << "        type \"o\" means \"output\" " << std::endl;
    std::cout << "        type \"i\" means \"input\" " << std::endl;

    std::cout << std::endl;

	std::cout << "Example commads: " << std::endl;
	std::cout << "setiarr -1 1 1 0" << std::endl;
	std::cout << "print" << std::endl;
}


