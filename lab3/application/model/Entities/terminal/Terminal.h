#pragma once

#include <string>
#include <iostream>

namespace Models {

    enum TerminalType {
        Input,
        Output
    };

    class Terminal {
    protected:
        int signalState = 0;
        int numberOfConnections = 0;

    public:
        virtual TerminalType type() const = 0;

        virtual int getNumberOfConnections() const = 0;

        virtual bool setNumberOfConnections(int n) = 0;

        virtual int getSignalState() const;

        virtual bool setSignalState(int n);

        virtual std::string toString() const;

        virtual ~Terminal() = default;

        friend std::ostream & operator<<(std::ostream & os, const Terminal & terminal);
    };

    std::ostream & operator<<(std::ostream & os, const Terminal & terminal);


}


