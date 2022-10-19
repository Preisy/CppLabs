#pragma once
#include "TableController.h"

namespace Controllers {

    class UsersController : public TableController<int, std::string> {
        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override {
            std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
            res.emplace("addu", [this](const std::string & args) { return add(args);} );
            res.emplace("printu", [this](const std::string & args) { return print(args);} );
            return res;
        }
    };
}