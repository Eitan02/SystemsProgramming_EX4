// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify correct behavior of MyContainer<T>::SideCrossOrder iterator.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test SideCrossOrder on an odd-size container
TEST_CASE("SideCrossOrder visits odd-size container correctly") {
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    // Ascending sorted values: [1, 2, 6, 7, 15]
    // Side-cross pattern: [1, 15, 2, 7, 6]
    std::vector<int> expected = {1, 15, 2, 7, 6};

    std::vector<int> seen;
    for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test SideCrossOrder on an even-size container
TEST_CASE("SideCrossOrder visits even-size container correctly") {
    MyContainer<int> c;
    c.add(4);
    c.add(1);
    c.add(3);
    c.add(2);
    // Ascending sorted values: [1, 2, 3, 4]
    // Side-cross pattern: [1, 4, 2, 3]
    std::vector<int> expected = {1, 4, 2, 3};

    std::vector<int> seen;
    for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test SideCrossOrder on a single-element container
TEST_CASE("SideCrossOrder on single-element container") {
    MyContainer<int> c;
    c.add(99);

    auto it = c.beginSideCrossOrder();
    CHECK(*it == 99);
    ++it;
    CHECK(it == c.endSideCrossOrder());
}
