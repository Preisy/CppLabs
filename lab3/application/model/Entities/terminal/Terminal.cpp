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

    int Terminal::operator||(const Terminal & el1) const {
        if (signalState == 1 || el1.signalState == 1)
            return 1;
        if (signalState == 0 || el1.signalState == 0)
            return 0;
        return -1;
    }

    int Terminal::operator&&(const Terminal & el1) const {
        if (signalState == 1 && el1.signalState == 1)
            return 1;
        if (signalState == -1 && el1.signalState == -1)
            return -1;
        return 0;
    }
}

