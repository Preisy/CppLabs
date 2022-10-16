#include <iostream>

#include "Table.h"

//    auto item = Item<int, std::string, bool>(12, "12", "std"); // а как это работает
//auto item = Item<int, std::string, bool, std::string>(12, "12", true, "as");

int main() {
    Table<int, std::string, bool> table = Table<int, std::string, bool>();


    int a = 0;


    return 0;
}