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
    const Vector<Models::InputTerminal> & LogicalElement::getInputTerminals() const {
        return inputTerminals;
    }

    const Vector<Models::OutputTerminal> & LogicalElement::getOutputTerminals() const {
        return outputTerminals;
    }

    size_t LogicalElement::getInputsLen() const {
        return inputTerminals.size();
    }

    size_t LogicalElement::getOutputsLen() const {
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


    std::ostream & operator<<(std::ostream & os, const LogicalElement & el) {
        os << "Inputs:" << std::endl;
        for (int i = 0; i < el.getInputsLen(); ++i) {
            os << i << ": " << el.getInputTerminals()[i] << " ";
        }
        os << std::endl;

        os << "Outputs:" << std::endl;
        for (int i = 0; i < el.getOutputsLen(); ++i) {
            os << i << ": " << el.getOutputTerminals()[i] << " ";
        }
        return os;
    }
}