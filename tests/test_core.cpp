// eitan.derdiger@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <sstream>

/*
  Purpose:
    - Verify basic MyContainer<T> functionalities: add, remove, size, and operator<<.
*/

using namespace container;

// Test basic operations: add, remove, size, and operator<<
TEST_CASE("Core functionality: add(), remove(), size(), and operator<<") {
    MyContainer<int> c;
    CHECK(c.size() == 0);

    // Adding elements increases size
    c.add(42);
    CHECK(c.size() == 1);
    c.add(7);
    c.add(42);
    CHECK(c.size() == 3);

    // Removing an existing element removes all occurrences
    c.remove(42);
    CHECK(c.size() == 1);
    CHECK_NOTHROW(c.remove(7));
    CHECK(c.size() == 0);

    // Removing a non-existent element throws
    c.add(5);
    CHECK_THROWS_AS(c.remove(999), std::runtime_error);

    // operator<< prints in insertion order
    c.add(10);
    c.add(20);
    std::ostringstream os;
    os << c;
    CHECK(os.str() == "[5, 10, 20]");
}

// Test that remove does not change size on failed removal
TEST_CASE("remove() does not modify size on failed removal") {
    MyContainer<int> c;
    c.add(5);
    c.add(10);
    CHECK(c.size() == 2);
    CHECK_THROWS_AS(c.remove(123), std::runtime_error);
    CHECK(c.size() == 2);
}
