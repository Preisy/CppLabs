#include "InputTerminal.h"

namespace Models {

    TerminalType InputTerminal::type() const {
        return TerminalType::Input;
    }


    int InputTerminal::getNumberOfConnections() const {
        return numberOfConnections;
    }

    bool InputTerminal::setNumberOfConnections(int n) {
        if (n < 0 || n > 1)
            return false;
        numberOfConnections = n;
        return true;
    }

    InputTerminal::InputTerminal(int signalState, int numberOfConnections) {
        if (signalState != -1 && signalState != 0 && signalState != 1)
            throw std::range_error("signalState should be equal -1, 0 or 1");
        if (numberOfConnections < 0 || numberOfConnections > 1) {
            throw std::range_error("numberOfConnections should be above 0 and below or equal 1");
        }
        this->numberOfConnections = numberOfConnections;
        this->signalState = signalState;
    }


}
