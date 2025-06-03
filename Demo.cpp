// eitan.derdiger@gmail.com

/*
  Purpose:
    - Showcase MyContainer<T> with different types (int, std::string, double).
    - Demonstrate all six traversal orders: insertion (Order), AscendingOrder,
      DescendingOrder, ReverseOrder, SideCrossOrder, MiddleOutOrder.
    - Show exception handling for remove() and invalid iterator operations.
    - Illustrate iterator snapshot behavior when modifying the container.
    - Use range-based for loops (Order) to iterate in insertion order.
*/

#include <iostream>
#include <string>
#include "MyContainer.hpp"

using namespace container;

/*
    Extended Demo for MyContainer<T> showcasing:
    - Multiple types: int, string, double
    - All iterator traversal orders
    - Exception handling for remove and iterator operations
    - Dynamic modifications and iterator independence
    - Range-based for loops (using begin()/end())
*/

void demoIntContainer() {
    std::cout << "----- Integer Container Demo -----\n";
    MyContainer<int> intCont;

    // Add elements (including duplicates)
    intCont.add(42);
    intCont.add(17);
    intCont.add(23);
    intCont.add(17);
    intCont.add(99);
    intCont.add(5);

    // Print current size and contents
    std::cout << "After adds, size = " << intCont.size() << "\n";
    std::cout << "Contents (in insertion order): " << intCont << "\n\n";

    // Ascending order traversal
    std::cout << "Ascending order: ";
    for (auto it = intCont.beginAscendingOrder(); it != intCont.endAscendingOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Descending order traversal
    std::cout << "Descending order: ";
    for (auto it = intCont.beginDescendingOrder(); it != intCont.endDescendingOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Side-cross order traversal
    std::cout << "Side-cross order: ";
    for (auto it = intCont.beginSideCrossOrder(); it != intCont.endSideCrossOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Reverse insertion order traversal
    std::cout << "Reverse insertion order: ";
    for (auto it = intCont.beginReverseOrder(); it != intCont.endReverseOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Middle-out order traversal
    std::cout << "Middle-out order: ";
    for (auto it = intCont.beginMiddleOutOrder(); it != intCont.endMiddleOutOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Demonstrate range-based for (insertion order)
    std::cout << "Range-based for (insertion order): ";
    for (int x : intCont) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Demonstrate remove()
    std::cout << "\nRemoving all occurrences of 17...\n";
    try {
        intCont.remove(17);
        std::cout << "After removal, size = " << intCont.size() << "\n";
        std::cout << "Contents now: " << intCont << "\n";
    } catch (const std::runtime_error& ex) {
        std::cout << "Exception on remove: " << ex.what() << "\n";
    }

    // Attempt to remove an element not present
    std::cout << "\nAttempting to remove 123 (not present)...\n";
    try {
        intCont.remove(123);
    } catch (const std::runtime_error& ex) {
        std::cout << "Caught exception: " << ex.what() << "\n";
    }

    // Iterator exception demonstration
    std::cout << "\nIterator past-end exception demo:\n";
    auto itEnd = intCont.beginAscendingOrder();
    // Advance to the end
    while (true) {
        try {
            ++itEnd;
        } catch (const std::runtime_error&) {
            break;
        }
    }
    // Now itEnd is at one-past-end
    try {
        std::cout << *itEnd << "\n";
    } catch (const std::runtime_error& ex) {
        std::cout << "Caught dereference exception: " << ex.what() << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

void demoStringContainer() {
    std::cout << "----- String Container Demo -----\n";
    MyContainer<std::string> strCont;

    // Add string values
    strCont.add("apple");
    strCont.add("orange");
    strCont.add("banana");
    strCont.add("pear");
    strCont.add("banana");  // duplicate

    // Print size and contents
    std::cout << "After adds, size = " << strCont.size() << "\n";
    std::cout << "Contents: " << strCont << "\n\n";

    // Ascending (lexicographical) order traversal
    std::cout << "Ascending (lex) order: ";
    for (auto it = strCont.beginAscendingOrder(); it != strCont.endAscendingOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Descending (lex) order traversal
    std::cout << "Descending (lex) order: ";
    for (auto it = strCont.beginDescendingOrder(); it != strCont.endDescendingOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Side-cross order traversal
    std::cout << "Side-cross order: ";
    for (auto it = strCont.beginSideCrossOrder(); it != strCont.endSideCrossOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Demonstrate range-based for
    std::cout << "Range-based for: ";
    for (const auto& s : strCont) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    // Remove a string
    std::cout << "\nRemoving \"banana\"...\n";
    try {
        strCont.remove("banana");
        std::cout << "After removal, size = " << strCont.size() << "\n";
        std::cout << "Contents: " << strCont << "\n";
    } catch (const std::runtime_error& ex) {
        std::cout << "Exception: " << ex.what() << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

void demoDoubleContainer() {
    std::cout << "----- Double Container Demo -----\n";
    MyContainer<double> dblCont;

    // Add double values
    dblCont.add(3.14);
    dblCont.add(2.718);
    dblCont.add(1.414);
    dblCont.add(2.718);  // duplicate
    dblCont.add(0.577);

    // Print size and contents
    std::cout << "After adds, size = " << dblCont.size() << "\n";
    std::cout << "Contents: " << dblCont << "\n\n";

    // Demonstrate reverse insertion order
    std::cout << "Reverse insertion order: ";
    for (auto it = dblCont.beginReverseOrder(); it != dblCont.endReverseOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Demonstrate middle-out order
    std::cout << "Middle-out order: ";
    for (auto it = dblCont.beginMiddleOutOrder(); it != dblCont.endMiddleOutOrder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Demonstrate range-based for
    std::cout << "Range-based for: ";
    for (double x : dblCont) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Attempt to remove a value not present
    std::cout << "\nAttempting to remove 9.99...\n";
    try {
        dblCont.remove(9.99);
    } catch (const std::runtime_error& ex) {
        std::cout << "Caught exception: " << ex.what() << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

int main() {
    std::cout << "*** MyContainer<T> Comprehensive Demo ***\n\n";

    // Integer container demonstration
    demoIntContainer();

    // String container demonstration
    demoStringContainer();

    // Double container demonstration
    demoDoubleContainer();

    // Dynamic modification and iterator snapshot demonstration
    std::cout << "----- Iterator Snapshot Demo -----\n";
    MyContainer<int> snapshotCont;
    snapshotCont.add(10);
    snapshotCont.add(20);
    snapshotCont.add(30);

    std::cout << "Original contents: " << snapshotCont << "\n";

    // Create an ascending iterator before modifying the container
    auto itAsc = snapshotCont.beginAscendingOrder();

    // Print first element via iterator
    std::cout << "First value from iterator: " << *itAsc << "\n";  // should be 10

    // Modify container: add and remove
    snapshotCont.add(5);
    snapshotCont.remove(20);

    std::cout << "After modifications, container = " << snapshotCont << "\n";

    // Continue with old iterator (should still follow original sequence [10,20,30])
    ++itAsc;
    std::cout << "Second value from old iterator (snapshot): " << *itAsc << "\n";  // should be 20
    std::cout << "-----------------------------------\n\n";

    std::cout << "*** Demo Completed ***\n";
    return 0;
}
