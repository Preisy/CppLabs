#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include <catch2/catch_all.hpp>
#include "catch.hpp"

#include "../application/model/Astroid.h"
#include <math.h>


TEST_CASE( "Astroid coords are computed", "[astroid]" ) {
    Models::Astroid astroid;
    astroid.setR(24);

    SECTION("Astroid::x") {
        astroid.setR(24);
        CHECK( astroid.x(0) == astroid.getR() );
        CHECK( astroid.x(M_PI_2) == Approx(0).margin(0.1));
        CHECK( astroid.x(M_PI) == -astroid.getR());
    }

    SECTION("Astroid::y") {
        CHECK(astroid.y(0) == 0);
        CHECK(astroid.y(M_PI_2) == astroid.getR());
        CHECK(astroid.y(M_PI) == Approx(0).margin(0.1));
    }

    SECTION("Astroid::yx") {
        CHECK(astroid.getYfromX(0) == Approx(0).margin(0.1));
        CHECK(astroid.getYfromX(astroid.getR()) == 0);
        CHECK(astroid.getYfromX(-astroid.getR()) == 0);
    }
}

TEST_CASE("Calculate properties", "[astroid]" ) {
    Models::Astroid astroid(2);
    astroid.setR(12);

    SECTION("Astroid::cl") {
        CHECK( astroid.curveLength(0) == 0 );
    }

    SECTION("Astroid::s") {
        CHECK(astroid.square() == Approx(169.6).margin(0.1));
    }

    SECTION("Astroid::cr") {
        CHECK( astroid.curvatureRadius(M_PI) == Approx(0).margin(0.1) );
    }

    SECTION("Astroid::cr") {
        CHECK( astroid.curvatureRadius(0) == 0 );
        astroid.setR(24);
        CHECK( astroid.curvatureRadius(M_PI_4) == 36 );
    }
}










