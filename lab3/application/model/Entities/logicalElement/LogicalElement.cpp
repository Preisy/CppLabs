#include "LogicalElement.h"

LogicalElement::LogicalElement() = default;


LogicalElement::LogicalElement(int inputLength, int outputLength)
        : inputTerminals(Vector<Models::InputTerminal>(inputLength)),
          outputTerminals(Vector<Models::OutputTerminal>(outputLength))  {}

LogicalElement::LogicalElement(
            const Vector<Models::InputTerminal> & inputTerminals,
            const Vector<Models::OutputTerminal> & outputTerminals
        ) : inputTerminals(inputTerminals),
            outputTerminals(outputTerminals) {}

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


