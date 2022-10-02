#include "TerminalController.h"

#include <sstream>

namespace Controllers {
    std::unordered_map<std::string, std::function<Response(const std::string &)>> TerminalController::getRequests() {
        std::unordered_map<std::string, std::function<Response(const std::string &)>> mp;
        mp.emplace("setiarr", [this](const std::string & args) {return setInputTerminalArrays(args);});
        mp.emplace("setoarr", [this](const std::string & args) {return setOutputsTerminalArrays(args);});
        mp.emplace("print", [this](const std::string & args) {return printTerminalArrays(args);});
        mp.emplace("t", [this](const std::string & args) {return getSetTerminal(args);});
        mp.emplace("addt", [this](const std::string & args) {return addTerminal(args);});
        return mp;
    }

    Response TerminalController::setInputTerminalArrays(const std::string & args) {
        std::istringstream ss(args);

        Vector<Models::InputTerminal> v;

        while (true) {
            int signalState;
            ss >> signalState;
            if (!ss) return {"", ResponseCode::BadRequest};
            int numberOfConnections;
            ss >> numberOfConnections;
            if (!ss) return {"", ResponseCode::BadRequest};

            Models::InputTerminal terminal;
            try {
                terminal = Models::InputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }


            v.emplaceBack(std::move(terminal));

            if (ss.eof())
                break;
        }

        logicalElement.getInputTerminals() = std::move(v);

        return {"", Ok};
    }

    Response TerminalController::setOutputsTerminalArrays(const std::string & args) {
        std::istringstream ss(args);

        Vector<Models::OutputTerminal> v;

        while (true) {
            int signalState;
            ss >> signalState;
            if (!ss) return {"", ResponseCode::BadRequest};
            int numberOfConnections;
            ss >> numberOfConnections;
            if (!ss) return {"", ResponseCode::BadRequest};

            Models::OutputTerminal terminal;
            try {
                terminal = Models::OutputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }

            v.emplaceBack(std::move(terminal));

            if (ss.eof())
                break;
        }

        logicalElement.getOutputTerminals() = std::move(v);

        return {"", Ok};
    }

    Response TerminalController::printTerminalArrays(const std::string & args) {
        if (!args.empty()) return {"", BadRequest};

        std::ostringstream ss;
        ss << logicalElement;

        return {std::move(ss.str()), Ok};
    }


    Response TerminalController::getSetTerminal(const std::string & args) {
        std::istringstream ss(args);

        std::string type;
        ss >> type;
        if (!ss || ss.eof()) return {"", ResponseCode::BadRequest};
        if (type != "o" && type != "i") return {"enter correct type", ResponseCode::BadRequest};

        int index;
        ss >> index;
        if (!ss) return {"", ResponseCode::BadRequest};
        if (type == "o") {
            if (index >= logicalElement.getOutputsLen())
                return {"index is above than array length", ResponseCode::BadRequest};
        } else if (type == "i") {
            if (index >= logicalElement.getInputsLen())
                return {"index is above than array length", ResponseCode::BadRequest};
        }


        if (ss.eof()) {
            std::ostringstream os;
            os << index << ": ";
            if (type == "o") {
                os << logicalElement.getOutputTerminals()[index];
                return {std::move(os.str()), Ok};
            } else if (type == "i") {
                os << logicalElement.getInputTerminals()[index];
                return {std::move(os.str()), Ok};
            }
            return {"", ResponseCode::BadRequest};
        }

        int signalState;
        ss >> signalState;
        if (!ss) return {"", ResponseCode::BadRequest};
        int numberOfConnections;
        ss >> numberOfConnections;
        if (!ss) return {"", ResponseCode::BadRequest};

        if (type == "o") {
            Models::OutputTerminal terminal;
            try {
                terminal = Models::OutputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }
            logicalElement.getOutputTerminals()[index] = std::move(terminal);
            return {"", Ok};
        } else if (type == "i") {
            Models::InputTerminal terminal;
            try {
                terminal = Models::InputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }
            logicalElement.getInputTerminals()[index] = std::move(terminal);
            return {"", Ok};
        }



        return {"", BadRequest};
    }

    Response TerminalController::addTerminal(const std::string & args) {
        std::istringstream ss(args);

        std::string type;
        ss >> type;
        if (!ss || ss.eof()) return {"", ResponseCode::BadRequest};
        if (type != "o" && type != "i") return {"enter correct type", ResponseCode::BadRequest};

        int signalState;
        ss >> signalState;
        if (!ss) return {"", ResponseCode::BadRequest};
        int numberOfConnections;
        ss >> numberOfConnections;
        if (!ss) return {"", ResponseCode::BadRequest};

        if (type == "o") {
            Models::OutputTerminal terminal;
            try {
                terminal = Models::OutputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }
            logicalElement.getOutputTerminals().pushBack(std::move(terminal));
            return {"", Ok};
        } else if (type == "i") {
            Models::InputTerminal terminal;
            try {
                terminal = Models::InputTerminal(signalState, numberOfConnections);
            } catch (std::range_error & range_error) {
                return {range_error.what(), BadRequest};
            }
            logicalElement.getInputTerminals().pushBack(std::move(terminal));
            return {"", Ok};
        }

        return {"", BadRequest};
    }
}
