#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../application/model/Astroid.h"
#include <math.h>


TEST_CASE( "Astroid coords are computed", "[astroid]" ) {
    Models::Astroid astroid;
    astroid.setR(24);

    SECTION("Astroid::x") {
        astroid.setR(24);
        REQUIRE( astroid.x(0) == astroid.getR() );
        REQUIRE( astroid.x(M_PI_2) == Approx(0).margin(0.1));
        REQUIRE( astroid.x(M_PI) == -astroid.getR());
    }

    SECTION("Astroid::y") {
        REQUIRE(astroid.y(0) == 0);
        REQUIRE(astroid.y(M_PI_2) == astroid.getR());
        REQUIRE(astroid.y(M_PI) == Approx(0).margin(0.1));
    }

    SECTION("Astroid::yx") {
        NEAR(astroid.getYfromX(0), 0);
        REQUIRE(astroid.getYfromX(astroid.getR()) == 0);
        REQUIRE(astroid.getYfromX(-astroid.getR()) == 0);
    }
}

TEST_CASE("Calculate properties", "[astroid]" ) {
    Models::Astroid astroid(2);
    astroid.setR(12);

    SECTION("Astroid::cl") {
        REQUIRE( astroid.curveLength(0) == 0 );
    }

    SECTION("Astroid::s") {
        REQUIRE(astroid.square() == Approx(169.6).margin(0.1));
    }

    SECTION("Astroid::cr") {
        REQUIRE( astroid.curvatureRadius(M_PI) == Approx(0).margin(0.1) );
    }

    SECTION("Astroid::cr") {
        REQUIRE( astroid.curvatureRadius(0) == 0 );
        astroid.setR(24);
        REQUIRE( astroid.curvatureRadius(M_PI_4) == 36 );
    }
}










