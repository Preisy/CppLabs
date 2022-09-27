#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../application/model/Entities/logicalElement/LogicalElement.h"
#include <math.h>


TEST_CASE( "Logical Element", "[LE]" ) {
    Models::LogicalElement logicalElement;

    SECTION("LogicalElement(int inputLength, int outputLength)") {
        logicalElement = Models::LogicalElement(5, 6);
        CHECK(logicalElement.getInputsLen() == 5);
        CHECK(logicalElement.getOutputsLen() == 6);
        logicalElement = Models::LogicalElement(16, 3);
        CHECK(logicalElement.getInputsLen() == 16);
        CHECK(logicalElement.getOutputsLen() == 3);
        logicalElement = Models::LogicalElement(1, 1);
        CHECK(logicalElement.getInputsLen() == 1);
        CHECK(logicalElement.getOutputsLen() == 1);
    }

    SECTION("checking if LogicalElement(...) by copying Vectors copies correctly") {
        Vector<Models::InputTerminal> v1 = {{-1, 1}, {0, 0}, {1, 1}};
        Vector<Models::OutputTerminal> v2 = {{-1, 1}, {0, 2}, {1, 3}};
        logicalElement = Models::LogicalElement(std::move(v1), std::move(v2));

        CHECK(logicalElement.getInputTerminals()[0].getSignalState() == -1);
        CHECK(logicalElement.getInputTerminals()[0].getNumberOfConnections() == 1);
        CHECK(logicalElement.getInputTerminals()[1].getSignalState() == 0);
        CHECK(logicalElement.getInputTerminals()[1].getNumberOfConnections() == 0);
        CHECK(logicalElement.getInputTerminals()[2].getSignalState() == 1);
        CHECK(logicalElement.getInputTerminals()[2].getNumberOfConnections() == 1);


        CHECK(logicalElement.getOutputTerminals()[0].getSignalState() == -1);
        CHECK(logicalElement.getOutputTerminals()[0].getNumberOfConnections() == 1);
        CHECK(logicalElement.getOutputTerminals()[1].getSignalState() == 0);
        CHECK(logicalElement.getOutputTerminals()[1].getNumberOfConnections() == 2);
        CHECK(logicalElement.getOutputTerminals()[2].getSignalState() == 1);
        CHECK(logicalElement.getOutputTerminals()[2].getNumberOfConnections() == 3);
    }

    SECTION("Checking if getting Terminal working correctly") {
        Vector<Models::InputTerminal> v1 = {{-1, 1}, {0, 0}, {1, 1}};
        Vector<Models::InputTerminal> v2 = {{-1, 1}, {0, 0}, {1, 1}};
        logicalElement = Models::LogicalElement(std::move(v1), {});
        for (int i = 0; i < logicalElement.getInputTerminals().size(); ++i) {
            CHECK(logicalElement.getInput(i).getSignalState() == v2[i].getSignalState());
            CHECK(logicalElement.getInput(i).getNumberOfConnections() == v2[i].getNumberOfConnections());
        }

        Vector<Models::OutputTerminal> v3 = {{-1, 1}, {0, 2}, {1, 3}};
        Vector<Models::OutputTerminal> v4 = {{-1, 1}, {0, 2}, {1, 3}};
        logicalElement = Models::LogicalElement({}, std::move(v3));
        for (int i = 0; i < logicalElement.getInputTerminals().size(); ++i) {
            CHECK(logicalElement.getOutput(i).getSignalState() == v2[i].getSignalState());
            CHECK(logicalElement.getOutput(i).getNumberOfConnections() == v2[i].getNumberOfConnections());
        }
    }

    SECTION("Adding Terminals") {
        for (int i = 0; i < 10; ++i) {
            logicalElement.addInputTerminal({i % 2, 1 - i % 2});
            logicalElement.addOutputTerminal({1 - i % 2, i % 2});
        }

        for (int i = 0; i < 10; ++i) {
            CHECK(logicalElement.getInput(i).getSignalState() == i % 2);
            CHECK(logicalElement.getInput(i).getNumberOfConnections() == 1 - i % 2);
            CHECK(logicalElement.getOutput(i).getSignalState() == 1 - i % 2);
            CHECK(logicalElement.getOutput(i).getNumberOfConnections() == i % 2);
        }
    }
}


SCENARIO("Terminals can change their state", "[Terminal states]") {
    Models::InputTerminal inp;
    Models::OutputTerminal out;

    WHEN("signal state changed") {
        inp.setSignalState(-1);
        out.setSignalState(-1);
        THEN("checking") {
            CHECK(inp.getSignalState() == -1);
            CHECK(out.getSignalState() == -1);
        }
    }

    WHEN("number of connections changed") {
        inp.setNumberOfConnections(1);
        out.setNumberOfConnections(1);
        THEN("checking") {
            CHECK(inp.getNumberOfConnections() == 1);
            CHECK(out.getNumberOfConnections() == 1);
        }
    }

    WHEN("both type terminals was created") {
        inp = Models::InputTerminal();
        out = Models::OutputTerminal();
        THEN("they should return their type correctly") {
            CHECK(inp.type() == Models::TerminalType::Input);
            CHECK(out.type() == Models::TerminalType::Output);
        }
    }
}