#include <iostream>
#include <vector>

#include "../application/model/Entities/logicalElement/LogicalElement.h"

int main() {
    Vector<Models::InputTerminal> v1 = {{-1, 1}, {0, 0}, {1, 1}};
    Vector<Models::OutputTerminal> v2 = {{-1, 1}, {0, 2}, {1, 3}};

    auto logicalElement = Models::LogicalElement(std::move(v1), std::move(v2));
    for (int i = 0; i < logicalElement.getInputsLen(); ++i) {
        std::cout << logicalElement.getInput(i) << " ";
    }
    std::cout << std::endl;


    for (int i = 0; i < logicalElement.getOutputsLen(); ++i) {
        std::cout << logicalElement.getOutput(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}