// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify correct behavior of MyContainer<T>::AscendingOrder iterator.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test AscendingOrder on a container with distinct values
TEST_CASE("AscendingOrder sorts values correctly") {
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);

    std::vector<int> expected = {1, 2, 6, 7, 15};
    std::vector<int> seen;
    for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test AscendingOrder on a container with duplicate values
TEST_CASE("AscendingOrder with duplicates puts duplicates adjacent") {
    MyContainer<int> c;
    c.add(5);
    c.add(3);
    c.add(5);
    c.add(1);

    std::vector<int> expected = {1, 3, 5, 5};
    std::vector<int> seen;
    for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test that ascending iterator on single-element container returns that element
TEST_CASE("AscendingOrder on single-element container") {
    MyContainer<int> c;
    c.add(42);

    auto it = c.beginAscendingOrder();
    CHECK(*it == 42);
    ++it;
    CHECK(it == c.endAscendingOrder());
}
