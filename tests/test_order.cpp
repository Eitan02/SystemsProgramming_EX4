// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify that MyContainer<T>::Order iterator visits elements in insertion order.
    - Confirm that range-based for uses Order iterator by default.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test that Order iterator follows insertion order
TEST_CASE("Order iterator visits elements in insertion order") {
    MyContainer<int> c;
    for (int i = 1; i <= 5; ++i) {
        c.add(i * 10);
    }

    std::vector<int> seen;
    for (auto it = c.beginOrder(); it != c.endOrder(); ++it) {
        seen.push_back(*it);
    }
    CHECK(seen == std::vector<int>({10, 20, 30, 40, 50}));
}

// Test that range-based for uses Order (insertion order)
TEST_CASE("Range-based for loop uses Order (insertion order)") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    std::vector<int> seen;
    for (auto x : c) {
        seen.push_back(x);
    }
    CHECK(seen == std::vector<int>({1, 2, 3}));
}
