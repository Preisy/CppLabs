#pragma once

#include "Terminal.h"

namespace Models {

    class InputTerminal : public Terminal {
    public:
        InputTerminal() = default;

        InputTerminal(int signalState, int numberOfConnections);

        TerminalType type() const override;

        bool setNumberOfConnections(int n) override;

        int getNumberOfConnections() const override;
    };

}
