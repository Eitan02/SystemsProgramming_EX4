// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify correct behavior of MyContainer<T>::DescendingOrder iterator.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test DescendingOrder on a container with distinct values
TEST_CASE("DescendingOrder sorts values in descending order") {
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);

    std::vector<int> expected = {15, 7, 6, 2, 1};
    std::vector<int> seen;
    for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test DescendingOrder on a container with duplicate values
TEST_CASE("DescendingOrder with duplicates places highest duplicates first") {
    MyContainer<int> c;
    c.add(10);
    c.add(5);
    c.add(10);
    c.add(2);

    std::vector<int> expected = {10, 10, 5, 2};
    std::vector<int> seen;
    for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test that descending iterator on single-element container returns that element
TEST_CASE("DescendingOrder on single-element container") {
    MyContainer<int> c;
    c.add(99);

    auto it = c.beginDescendingOrder();
    CHECK(*it == 99);
    ++it;
    CHECK(it == c.endDescendingOrder());
}
