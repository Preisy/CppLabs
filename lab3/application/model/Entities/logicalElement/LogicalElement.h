#pragma once

#include "Entities/terminal/InputTerminal.h"
#include "Entities/terminal/OutputTerminal.h"
#include "Vector.h"

namespace Models {

    class LogicalElement {
        Vector<Models::InputTerminal> inputTerminals;
        Vector<Models::OutputTerminal> outputTerminals;

    public:
        LogicalElement();

        LogicalElement(int inputLength, int outputLength);

        LogicalElement(Vector<Models::InputTerminal> && inputTerminals,
                       Vector<Models::OutputTerminal> && outputTerminals);

        Vector<Models::InputTerminal> & getInputTerminals();

        const Vector<Models::InputTerminal> & getInputTerminals() const;

        Vector<Models::OutputTerminal> & getOutputTerminals();

        const Vector<Models::OutputTerminal> & getOutputTerminals() const;

        size_t getInputsLen() const;

        size_t getOutputsLen() const;

        Models::InputTerminal & getInput(size_t index);

        Models::OutputTerminal & getOutput(size_t index);

        void addInputTerminal(const Models::InputTerminal & terminal);

        void addOutputTerminal(const Models::OutputTerminal & terminal);

        friend std::ostream & operator<<(std::ostream & os, const LogicalElement & el);
    };

    std::ostream & operator<<(std::ostream & os, const LogicalElement & el);

}