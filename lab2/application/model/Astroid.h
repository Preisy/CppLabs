#pragma once

namespace Models {

    class Astroid {
        double R = 0;

    public:
        Astroid() = default;

        explicit Astroid(double r);

        double getR() const;

        void setR(double r);

        double curveLength(double angle);

        double curvatureRadius(double angle);

        double square();

        double x(double angle);

        double y(double angle);

        double getYfromX(double x);
    };

}