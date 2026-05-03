/*#define CATCH_CONFIG_MAIN

#include <cmath>

#include "catch.hpp"
#include "../image/color.h"

bool AreEqual(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

TEST_CASE("Color Default Constructor") {
    Color c;
    REQUIRE(AreEqual(c.GetR(), 0.0));
    REQUIRE(AreEqual(c.GetG(), 0.0));
    REQUIRE(AreEqual(c.GetB(), 0.0));
}

TEST_CASE("Color Normalized Constructor") {
    Color::ErrorCode status;
    Color c1(0.5, 0.25, 0.75, status);
    REQUIRE(status == Color::ErrorCode::Ok);
    REQUIRE(AreEqual(c1.GetR(), 0.5));
    REQUIRE(AreEqual(c1.GetG(), 0.25));
    REQUIRE(AreEqual(c1.GetB(), 0.75));

    Color c2(2.0, -1.0, 0.5, status);
    REQUIRE(status == Color::ErrorCode::InvalidValue);
}

TEST_CASE("Color Byte Constructor") {
    Color c(255, 150, 0);
    REQUIRE(AreEqual(c.GetR(), 1.0));
    REQUIRE(AreEqual(c.GetG(), 150.0 / 255.0));
    REQUIRE(AreEqual(c.GetB(), 0.0));
}
*/