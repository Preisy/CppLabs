#pragma once

#include "Terminal.h"

namespace Models {

    class OutputTerminal : public Terminal {
    public:
        OutputTerminal() = default;

        OutputTerminal(int signalState, int numberOfConnections);

        TerminalType type() const override;

        int getNumberOfConnections() const override;

        bool setNumberOfConnections(int n) override;
    };

}
