// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify correct behavior of MyContainer<T>::ReverseOrder iterator.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test ReverseOrder (reverse insertion order) on a container
TEST_CASE("ReverseOrder visits elements in reverse insertion order") {
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);

    std::vector<int> expected = {6, 15, 7};
    std::vector<int> seen;
    for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == expected);
}

// Test ReverseOrder on a single-element container
TEST_CASE("ReverseOrder on single-element container") {
    MyContainer<int> c;
    c.add(42);

    auto it = c.beginReverseOrder();
    CHECK(*it == 42);
    ++it;
    CHECK(it == c.endReverseOrder());
}
