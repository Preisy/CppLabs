#include "Astroid.h"
#include <math.h>
#include <stdexcept>

namespace Models {

    Astroid::Astroid(double r) : R(r) {}

    double Astroid::getR() const {
        return R;
    }

    void Astroid::setR(double r) {
        R = r;
    }

    double Astroid::curveLength(double angle) {
        if (angle < 0) angle = -angle;
        double sum = 0;
        for (int i = 0; i < angle / M_PI_2; ++i) {
            sum += (double) 3/2 * pow(R, (double) 1/3);
        }
        angle = angle - M_PI_2 * (int) (angle / M_PI_2);
        sum += (double) 3/2 * pow(R, (double) 1/3) * (pow(sin(angle), 2));

        return sum;
    }

    double Astroid::curvatureRadius(double angle) {
        return (double) 3/2 * R * sin(2 * angle);
    }

    double Astroid::square() {
        return 3 * M_PI * pow(R, 2) / 8;
    }

    double Astroid::x(double angle) {
        return R * pow(cos(angle), 3);
    }

    double Astroid::y(double angle) {
        return R * pow(sin(angle), 3);
    }

    double Astroid::getYfromX(double x) {
        if (abs(x) > R) throw std::invalid_argument("out of scope");
        double angle = 0;
        if (x < 0)
            angle = acos(pow(-x / R, (double) 1 / 3));
        else
            angle = acos(pow(x / R, (double) 1 / 3));
        return R * pow(sin(angle), 3);
    }

}