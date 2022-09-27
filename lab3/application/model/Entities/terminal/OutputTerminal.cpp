#include "OutputTerminal.h"

namespace Models {


    TerminalType OutputTerminal::type() const {
        return TerminalType::Output;
    }

    int OutputTerminal::getNumberOfConnections() const {
        return numberOfConnections;
    }

    bool OutputTerminal::setNumberOfConnections(int n) {
        if (n < 0 || n > 3)
            return false;
        numberOfConnections = n;
        return true;
    }

    OutputTerminal::OutputTerminal(int signalState, int numberOfConnections) noexcept(false) {
        if (signalState != -1 && signalState != 0 && signalState != 1)
            throw std::range_error("signalState should be equal -1, 0 or 1");
        if (numberOfConnections < 0 || numberOfConnections > 3) {
            throw std::range_error("numberOfConnections should be above 0 and below or equal 3");
        }
        this->numberOfConnections = numberOfConnections;
        this->signalState = signalState;
    }

}
