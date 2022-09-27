#pragma once

#include "IController.h"
#include "Entities/logicalElement/LogicalElement.h"

namespace Controllers {

    class TerminalController : public IController {
        LogicalElement logicalElement{2, 2};

    public:
        TerminalController() = default;

        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override;

        // set new array of input terminal
        Response setInputTerminalArrays(const std::string & args);

        // set new array of output terminal
        Response setOutputsTerminalArrays(const std::string & args);

        // print all terminals
        Response printTerminalArrays(const std::string & args);

        // get or set Terminal by id
        Response getSetTerminal(const std::string & args);

        // add newTerminal
        Response addTerminal(const std::string & args);
    };



}

