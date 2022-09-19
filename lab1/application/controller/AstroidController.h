#pragma once
#include <string>

#include "IController.h"
#include "Astroid.h"
#include "Response.h"

namespace Controllers {
    class AstroidController : public IController {
        Models::Astroid astroid{2};

        Response R(const std::string & args);
        Response cl(const std::string & args);
        Response cr(const std::string & args);
        Response s(const std::string & args);
        Response x(const std::string & args);
        Response y(const std::string & args);
        Response yx(const std::string & args);

    public:
        AstroidController() = default;

        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override;

        ~AstroidController() override = default;

        AstroidController(AstroidController && matrixController) noexcept;

    };
}