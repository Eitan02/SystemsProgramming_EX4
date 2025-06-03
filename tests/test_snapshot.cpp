// eitan.derdiger@gmail.com

/*
  Purpose:
    - Verify that iterators capture a snapshot of the container’s sequence at creation.
    - Confirm that copying and assigning iterators preserves independent state.
*/

#include "doctest.h"
#include "MyContainer.hpp"

using namespace container;

// Test that iterators maintain their original visitation sequence
// even after the container is modified
TEST_CASE("Iterator snapshot remains valid after container modification") {
    MyContainer<int> c;
    c.add(3);
    c.add(1);
    c.add(2);

    // Create an ascending iterator before modifications
    auto itAsc = c.beginAscendingOrder();

    // Collect first two values from the iterator
    std::vector<int> collected;
    collected.push_back(*itAsc); // should be 1
    ++itAsc;
    collected.push_back(*itAsc); // should be 2

    // Modify the container: add and remove
    c.add(0);
    c.remove(2);

    // Continue using the old iterator: it should still yield the third original value (3)
    ++itAsc;
    collected.push_back(*itAsc);
    CHECK(collected == std::vector<int>({1, 2, 3}));
}

// Test that copying and assigning iterators works as expected
TEST_CASE("Iterator copy and assignment maintain independent state") {
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    auto it1 = c.beginAscendingOrder();
    auto it2 = it1; // copy constructor
    CHECK(*it1 == *it2);

    ++it1; // it1 now at second element
    CHECK(*it1 != *it2);

    auto it3 = c.beginAscendingOrder();
    ++it3; // it3 now at second element
    it2 = it3; // assignment operator
    CHECK(*it2 == *it3);
}
