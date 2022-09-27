#include "LogicalElement.h"

namespace Models {

    LogicalElement::LogicalElement() = default;


    LogicalElement::LogicalElement(int inputLength, int outputLength)
            : inputTerminals(Vector<Models::InputTerminal>(inputLength)),
              outputTerminals(Vector<Models::OutputTerminal>(outputLength)) {}

    LogicalElement::LogicalElement(
            Vector<Models::InputTerminal> && inputTerminals,
            Vector<Models::OutputTerminal> && outputTerminals
    ) : inputTerminals(std::move(inputTerminals)),
        outputTerminals(std::move(outputTerminals)) {}

    Vector<Models::InputTerminal> & LogicalElement::getInputTerminals() {
        return inputTerminals;
    }

    Vector<Models::OutputTerminal> & LogicalElement::getOutputTerminals() {
        return outputTerminals;
    }

    size_t LogicalElement::getInputsLen() {
        return inputTerminals.size();
    }

    size_t LogicalElement::getOutputsLen() {
        return outputTerminals.size();
    }

    Models::InputTerminal & LogicalElement::getInput(size_t index) {
        return inputTerminals[index];
    }

    Models::OutputTerminal & LogicalElement::getOutput(size_t index) {
        return outputTerminals[index];
    }

    void LogicalElement::addInputTerminal(const Models::InputTerminal & terminal) {
        inputTerminals.pushBack(terminal);
    }

    void LogicalElement::addOutputTerminal(const Models::OutputTerminal & terminal) {
        outputTerminals.pushBack(terminal);
    }


}