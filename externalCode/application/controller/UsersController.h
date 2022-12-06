#pragma once
#include "BaseTableController.h"

namespace Controllers {

    class UsersController : public BaseTableController<int, std::string> {
        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override {
            std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
            res.emplace("getu", [this](const std::string & args) { return get(args);} );
            res.emplace("postu", [this](const std::string & args) { return post(args);} );
            res.emplace("putu", [this](const std::string & args) { return put(args);} );
            res.emplace("delu", [this](const std::string & args) { return del(args);} );
            res.emplace("printu", [this](const std::string & args) { return print(args);} );
            return res;
        }
    };
}