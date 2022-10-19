#pragma once
#include "BaseTableController.h"

namespace Controllers {

    class MarksController : public BaseTableController<int, double> {
        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override {
            std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
            res.emplace("addm", [this](const std::string & args) { return add(args);} );
            res.emplace("printm", [this](const std::string & args) { return print(args);} );
            return res;
        }
    };
}