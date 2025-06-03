// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify correct behavior of MyContainer<T>::MiddleOutOrder iterator.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test MiddleOutOrder on an odd-size container
TEST_CASE("MiddleOutOrder visits odd-size container correctly") {
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    // Insertion indices: [0,1,2,3,4], mid = 2 to value 6
    // Expected pattern: [6, 15, 1, 7, 2]
    std::vector<int> expected = {6, 15, 1, 7, 2};

    std::vector<int> seen;
    for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test MiddleOutOrder on an even-size container
TEST_CASE("MiddleOutOrder visits even-size container correctly") {
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    c.add(30);
    c.add(40);
    // Insertion indices: [0,1,2,3], mid = (4-1)/2 = 1 to value 20
    // Expected pattern: [20, 10, 30, 40]
    std::vector<int> expected = {20, 10, 30, 40};

    std::vector<int> seen;
    for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test MiddleOutOrder on a single-element container
TEST_CASE("MiddleOutOrder on single-element container") {
    MyContainer<int> c;
    c.add(42);

    auto it = c.beginMiddleOutOrder();
    CHECK(*it == 42);
    ++it;
    CHECK(it == c.endMiddleOutOrder());
}
