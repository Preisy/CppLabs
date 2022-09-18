#include "AstroidController.h"

#include <sstream>
#include <functional>
#include <math.h>
//#include <execution>

std::unordered_map<std::string, std::function<Response(const std::string &)>> Controllers::AstroidController::getRequests() {
    std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
    res.emplace("R", [this](const std::string & args) {return R(args);});
    res.emplace("cl", [this](const std::string & args) {return cl(args);});
    res.emplace("cr", [this](const std::string & args) {return cr(args);});
    res.emplace("s", [this](const std::string & args) {return s(args);});
    res.emplace("x", [this](const std::string & args) {return x(args);});
    res.emplace("y", [this](const std::string & args) {return y(args);});
    res.emplace("yx", [this](const std::string & args) {return yx(args);});
    return res;
}

Controllers::AstroidController::AstroidController(Controllers::AstroidController && matrixController) noexcept {
    astroid = std::move(matrixController.astroid);
}

Response Controllers::AstroidController::R(const std::string & args) {
    if (args.empty()) {
        double res = astroid.getR();
        return {std::to_string(res), Ok};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    astroid.setR(value);
    return {std::to_string(value), Ok};
}

Response Controllers::AstroidController::cl(const std::string & args) {
    if (args.empty()) {
        double res = astroid.curveLength(M_PI * 2);
        return {std::to_string(res), Ok};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    double res = astroid.curveLength(value);
    return {std::to_string(res), Ok};
}

Response Controllers::AstroidController::cr(const std::string & args) {
    if (args.empty()) {
        return {"", BadRequest};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    double res = astroid.curvatureRadius(value);
    return {std::to_string(res), Ok};
}

Response Controllers::AstroidController::s(const std::string & args) {
    if (args.empty()) {
        double res = astroid.square();
        return {std::to_string(res), Ok};
    }
    return {"", BadRequest};
}

Response Controllers::AstroidController::x(const std::string & args) {
    if (args.empty()) {
        return {"", BadRequest};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    double res = astroid.x(value);
    return {std::to_string(res), Ok};
}

Response Controllers::AstroidController::y(const std::string & args) {
    if (args.empty()) {
        return {"", BadRequest};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    double res = astroid.y(value);
    return {std::to_string(res), Ok};
}

Response Controllers::AstroidController::yx(const std::string & args) {
    if (args.empty()) {
        return {"", BadRequest};
    }

    std::istringstream ss(args);

    double value;
    ss >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    double res = astroid.getYfromX(value);
    return {std::to_string(res), Ok};
}


