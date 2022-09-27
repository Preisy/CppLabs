#include "Terminal.h"


namespace Models {

    int Terminal::getSignalState() const {
        return signalState;
    }

    bool Terminal::setSignalState(int n) {
        if (n != -1 && n != 0 && n != 1)
            return false;
        signalState = n;
        return true;
    }

    std::string Terminal::toString() const {
        return "ss: " + std::to_string(signalState) + ", nc: " + std::to_string(numberOfConnections);
    }

    std::ostream & operator<<(std::ostream & os, const Terminal & terminal) {
        std::string typeStr = (terminal.type() == Input) ? "i" : "o";
        os << "[" << typeStr << " " << terminal.signalState << ", " << terminal.numberOfConnections << "]";
        return os;
    }
}

