// eitan.derdiger@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <type_traits>

/*
  MyContainer<T> is a generic container for comparable elements.
  It supports:
    - add(const T& value): insert a new element.
    - remove(const T& value): remove all occurrences (throws if not found).
    - size() const: return number of elements.
    - operator<<: print elements in insertion order.
    - Six traversal orders via nested iterator classes:
        Order, AscendingOrder, DescendingOrder,
        ReverseOrder, SideCrossOrder, MiddleOutOrder.
  Each nested iterator class is defined in a separate header under include/iterators/.
*/

namespace container {

/**
 * @brief A generic container for comparable elements that supports
 * dynamic insertion, removal, and multiple custom traversal orders.
 *
 * @tparam T A type that supports operator< and operator==.
 */
template<typename T>
class MyContainer {
    static_assert(std::is_copy_constructible_v<T>, "T must be copy constructible");
    static_assert(std::is_copy_assignable_v<T>, "T must be copy assignable");

    // Check that T supports operator< and operator==
    template<typename U>
    static auto check_less(int) -> decltype(std::declval<U>() < std::declval<U>(), std::true_type());
    template<typename> static std::false_type check_less(...);
    template<typename U>
    static auto check_equal(int) -> decltype(std::declval<U>() == std::declval<U>(), std::true_type());
    template<typename> static std::false_type check_equal(...);

    static_assert(decltype(check_less<T>(0))::value, "T must support operator<");
    static_assert(decltype(check_equal<T>(0))::value, "T must support operator==");

private:
    std::vector<T> elements;  // Underlying storage (in insertion order)

    // Grant access to nested iterator classes
    template<typename ContainerType, typename ValueType>
    friend class BaseIterator;
    friend class Order;
    friend class AscendingOrder;
    friend class DescendingOrder;
    friend class ReverseOrder;
    friend class SideCrossOrder;
    friend class MiddleOutOrder;

public:
    MyContainer() = default;
    MyContainer(const MyContainer& other) = default;
    MyContainer& operator=(const MyContainer& other) = default;
    MyContainer(MyContainer&& other) noexcept = default;
    MyContainer& operator=(MyContainer&& other) noexcept = default;
    ~MyContainer() = default;

    /**
     * @brief Insert a new element into the container.
     */
    void add(const T& value) {
        elements.push_back(value);
    }

    /**
     * @brief Remove all occurrences of a given element.
     * @throws std::runtime_error if the element is not found.
     */
    void remove(const T& value) {
        size_t originalSize = elements.size();
        elements.erase(
            std::remove(elements.begin(), elements.end(), value),
            elements.end()
        );
        if (elements.size() == originalSize) {
            throw std::runtime_error("Element not found in container");
        }
    }

    /**
     * @brief Return the number of elements currently stored.
     */
    size_t size() const noexcept {
        return elements.size();
    }

    /**
     * @brief Print the container in a human-readable format: [a, b, c]
     */
    friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& cont) {
        os << "[";
        for (size_t i = 0; i < cont.elements.size(); ++i) {
            os << cont.elements[i];
            if (i + 1 < cont.elements.size()) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // Forward declarations of nested iterator types.
    class Order;
    class AscendingOrder;
    class DescendingOrder;
    class ReverseOrder;
    class SideCrossOrder;
    class MiddleOutOrder;

    // Iterator factory methods (declarations only).
    Order beginOrder() const;
    Order endOrder()   const;

    Order begin() const { return beginOrder(); }
    Order end()   const { return endOrder(); }

    AscendingOrder beginAscendingOrder() const;
    AscendingOrder endAscendingOrder()   const;

    DescendingOrder beginDescendingOrder() const;
    DescendingOrder endDescendingOrder()   const;

    ReverseOrder beginReverseOrder() const;
    ReverseOrder endReverseOrder()   const;

    SideCrossOrder beginSideCrossOrder() const;
    SideCrossOrder endSideCrossOrder()   const;

    MiddleOutOrder beginMiddleOutOrder() const;
    MiddleOutOrder endMiddleOutOrder()   const;
};

} // namespace container

// Include nested iterator definitions and implement begin()/end() methods.
// All nested iterator classes are defined under include/iterators/.
#include "iterators/BaseIterator.hpp"
#include "iterators/Order.hpp"
#include "iterators/AscendingOrder.hpp"
#include "iterators/DescendingOrder.hpp"
#include "iterators/ReverseOrder.hpp"
#include "iterators/SideCrossOrder.hpp"
#include "iterators/MiddleOutOrder.hpp"

namespace container {

// Implementations of the iterator factory methods:

template<typename T>
typename MyContainer<T>::Order MyContainer<T>::beginOrder() const {
    return Order(this, 0);
}

template<typename T>
typename MyContainer<T>::Order MyContainer<T>::endOrder() const {
    return Order(this, elements.size());
}

template<typename T>
typename MyContainer<T>::AscendingOrder MyContainer<T>::beginAscendingOrder() const {
    return AscendingOrder(this, 0);
}

template<typename T>
typename MyContainer<T>::AscendingOrder MyContainer<T>::endAscendingOrder() const {
    return AscendingOrder(this, elements.size());
}

template<typename T>
typename MyContainer<T>::DescendingOrder MyContainer<T>::beginDescendingOrder() const {
    return DescendingOrder(this, 0);
}

template<typename T>
typename MyContainer<T>::DescendingOrder MyContainer<T>::endDescendingOrder() const {
    return DescendingOrder(this, elements.size());
}

template<typename T>
typename MyContainer<T>::ReverseOrder MyContainer<T>::beginReverseOrder() const {
    return ReverseOrder(this, 0);
}

template<typename T>
typename MyContainer<T>::ReverseOrder MyContainer<T>::endReverseOrder() const {
    return ReverseOrder(this, elements.size());
}

template<typename T>
typename MyContainer<T>::SideCrossOrder MyContainer<T>::beginSideCrossOrder() const {
    return SideCrossOrder(this, 0);
}

template<typename T>
typename MyContainer<T>::SideCrossOrder MyContainer<T>::endSideCrossOrder() const {
    return SideCrossOrder(this, elements.size());
}

template<typename T>
typename MyContainer<T>::MiddleOutOrder MyContainer<T>::beginMiddleOutOrder() const {
    return MiddleOutOrder(this, 0);
}

template<typename T>
typename MyContainer<T>::MiddleOutOrder MyContainer<T>::endMiddleOutOrder() const {
    return MiddleOutOrder(this, elements.size());
}

} // namespace container

#endif // MYCONTAINER_HPP
