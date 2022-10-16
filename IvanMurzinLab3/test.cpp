#include <iostream>

//#include "GoodTable.h"

//

#include <tuple>

#include "Item.h"




int main() {



    std::tuple<int, bool, std::string> t(-1, true, "12");
    get<2>(t);


    std::cout << item.getSize();

    std::cout << item.get<2>();

    return 0;
}