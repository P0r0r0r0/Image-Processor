/*#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "../image/matrix.h"

TEST_CASE("Matrix Default Constructor") {
    Matrix<int> m;
    REQUIRE(m.GetRowAmount() == 0);
    REQUIRE(m.GetColAmount() == 0);
    REQUIRE(m.GetPointerObject() == nullptr);
}

TEST_CASE("Matrix MN Constructor") {
    Matrix<int> m(3, 4, 42);
    REQUIRE(m.GetRowAmount() == 3);
    REQUIRE(m.GetColAmount() == 4);
    REQUIRE(m.GetEl(0, 0) == 42);
    m.GetEl(0, 0) = 10;
    REQUIRE(m.GetEl(0, 0) == 10);
}

TEST_CASE("Matrix Row Access") {
    Matrix<int> m(3, 3, 0);
    m[0][0] = 1;
    m[1][1] = 2;
    m[2][2] = 3;

    Matrix<int>::Row row = m[1];
    REQUIRE(row.GetSize() == 3);
    REQUIRE(row.GetRowNum() == 1);
    REQUIRE(row[0] == 0);
    REQUIRE(row[1] == 2);
    REQUIRE(row[2] == 0);
    row[0] = 10;
    REQUIRE(m.GetEl(1, 0) == 10);
}

TEST_CASE("Matrix Column Access") {
    Matrix<int> m(3, 3, 0);
    m[0][0] = 1;
    m[1][1] = 2;
    m[2][2] = 3;

    Matrix<int>::Column col = m(2);
    REQUIRE(col.GetSize() == 3);
    REQUIRE(col.GetColNum() == 2);
    REQUIRE(col(0) == 0);
    REQUIRE(col(1) == 0);
    REQUIRE(col(2) == 3);
    col(0) = 10;
    REQUIRE(m.GetEl(0, 2) == 10);
}

TEST_CASE("Matrix Square Window") {
    Matrix<int> m(3, 3, 0);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;
    m[2][2] = 5;

    Matrix<int>::SquareWindow window1 = m.GetSquareWindow(0, 1, 3);
    REQUIRE(window1.GetSize() == 3);
    REQUIRE(window1.GetCenterRow() == 0);
    REQUIRE(window1.GetCenterCol() == 1);
    REQUIRE(window1(0, 0) == 1);
    REQUIRE(window1(0, 1) == 2);
    REQUIRE(window1(0, 2) == 0);
    REQUIRE(window1(1, 0) == 1);
    REQUIRE(window1(2, 2) == 0);

    window1(1, 2) = 10;
    REQUIRE(m[0][2] == 10);

    Matrix<int>::SquareWindow window2 = m.GetSquareWindow(2, 2, 3);
    REQUIRE(window2(0, 0) == 4);
    REQUIRE(window2(2, 1) == 5);
    REQUIRE(window2(1, 0) == 0);
    window2(0, 0) = 8;
    REQUIRE(m.GetEl(1, 1) == 8);
}

TEST_CASE("Matrix Container") {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    REQUIRE(m.size() == 4);

    auto it = m.begin();
    REQUIRE(*it == 1);
    ++it;
    ++it;
    REQUIRE(*it == 3);
    ++it;
    ++it;
    REQUIRE(it == m.end());

    auto it1 = m.begin();
    auto it2 = m.end();
    it2 = it1;
    REQUIRE(it2 == it1);
    REQUIRE(*it2 == 1);

    const Matrix<int>& cm = m;
    auto cit = cm.begin();
    REQUIRE(*cit == 1);
    ++cit;
    REQUIRE(*cit == 2);
}
*/