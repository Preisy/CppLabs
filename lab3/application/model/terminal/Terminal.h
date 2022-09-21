#pragma once

enum TerminalType {
    Input,
    Output
};
enum SignalState {
    0,
    1,
    X
};

class Terminal {
    virtual TerminalType type() = 0;

    virtual int numberOfConnections() = 0;

    virtual int signalState() = 0;

    virtual ~Terminal() = default;
};
