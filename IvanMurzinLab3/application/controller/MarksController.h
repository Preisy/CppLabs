#pragma once
#include "BaseTableController.h"

namespace Controllers {

    class MarksController : public BaseTableController<int, double> {
        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override {
            std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
            res.emplace("getm", [this](const std::string & args) { return get(args);} );
            res.emplace("postm", [this](const std::string & args) { return post(args);} );
            res.emplace("putm", [this](const std::string & args) { return put(args);} );
            res.emplace("delm", [this](const std::string & args) { return del(args);} );
            res.emplace("printm", [this](const std::string & args) { return print(args);} );
            return res;
        }
    };
}