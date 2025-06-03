// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify exception behavior of MyContainer<T> and its iterators.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test that dereferencing end() throws an exception
TEST_CASE("Dereferencing end() throws runtime_error") {
    MyContainer<int> c;
    c.add(5);
    c.add(10);

    auto it = c.beginOrder();
    ++it; // now at second element
    ++it; // now at end (no exception yet)
    CHECK_THROWS_AS(*it, std::runtime_error);
}

// Test that incrementing past end() throws an exception
TEST_CASE("Incrementing past end() throws runtime_error") {
    MyContainer<int> c;
    c.add(5);
    c.add(10);

    auto it = c.beginOrder();
    ++it; // now at second element
    ++it; // now at end (no exception yet)
    CHECK_THROWS_AS(++it, std::runtime_error);
}

// Test exception behavior for all iterators when size == 2
TEST_CASE("All iterators throw when incremented past end for size == 2") {
    // AscendingOrder
    MyContainer<int> cA;
    cA.add(2);
    cA.add(1);
    auto itA = cA.beginAscendingOrder();
    ++itA; ++itA; // moves to end
    CHECK_THROWS_AS(++itA, std::runtime_error);

    // DescendingOrder
    MyContainer<int> cD;
    cD.add(2);
    cD.add(1);
    auto itD = cD.beginDescendingOrder();
    ++itD; ++itD;
    CHECK_THROWS_AS(++itD, std::runtime_error);

    // ReverseOrder
    MyContainer<int> cR;
    cR.add(2);
    cR.add(1);
    auto itR = cR.beginReverseOrder();
    ++itR; ++itR;
    CHECK_THROWS_AS(++itR, std::runtime_error);

    // SideCrossOrder
    MyContainer<int> cS;
    cS.add(2);
    cS.add(1);
    auto itS = cS.beginSideCrossOrder();
    ++itS; ++itS;
    CHECK_THROWS_AS(++itS, std::runtime_error);

    // MiddleOutOrder
    MyContainer<int> cM;
    cM.add(2);
    cM.add(1);
    auto itM = cM.beginMiddleOutOrder();
    ++itM; ++itM;
    CHECK_THROWS_AS(++itM, std::runtime_error);
}

// Test that remove throws when element not found
TEST_CASE("remove() throws when element does not exist") {
    MyContainer<int> c;
    c.add(5);
    CHECK_THROWS_AS(c.remove(999), std::runtime_error);
}
