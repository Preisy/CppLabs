#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../application/model/Astroid.h"
#include <math.h>


TEST_CASE( "Astroid coords are computed", "[astroid]" ) {
    Models::Astroid astroid;

    SECTION("Astroid::x") {
        astroid.setR(24);
        REQUIRE( astroid.x(0) == astroid.getR() );
        REQUIRE( astroid.x(M_PI) == -astroid.getR());
        REQUIRE( astroid.x(4 * M_PI) == astroid.getR());
    }

    SECTION("Astroid::y") {
        REQUIRE(astroid.y(0) == 0);
        REQUIRE(astroid.y(0) == astroid.getR());
    }

    SECTION("Astroid::yx") {
        astroid.setR(24);

        REQUIRE(astroid.getYfromX(0) == astroid.getR());
        REQUIRE(astroid.getYfromX(astroid.getR()) == 0);
        REQUIRE(astroid.getYfromX(-astroid.getR()) == 0);
    }
}

TEST_CASE("Calculate properties", "[astroid]" ) {
    Models::Astroid astroid;

    SECTION("Astroid::cl") {
        REQUIRE( astroid.curveLength(0) == 0 );
    }

    SECTION("Astroid::s") {
        REQUIRE( astroid.square() == 0 );
    }

    SECTION("Astroid::cr") {
        REQUIRE( astroid.curvatureRadius(0) == 0 );
        astroid.setR(24);
        REQUIRE( astroid.curvatureRadius(M_PI_4) == 36 );
    }
}










