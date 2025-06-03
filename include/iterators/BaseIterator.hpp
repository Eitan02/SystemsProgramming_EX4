// eitan.derdiger@gmail.com

#ifndef BASEITERATOR_HPP
#define BASEITERATOR_HPP

#include <vector>
#include <memory>
#include <stdexcept>
#include "MyContainer.hpp"

/*
  BaseIterator.hpp defines the template class BaseIterator<ContainerType, ValueType>,
  which serves as the common base for all nested iterators of MyContainer<T>.

  Purpose:
    - Stores a pointer to the container instance (containerPtr).
    - Maintains a precomputed sequence of element indices in orderIndices.
    - Tracks the current position (index) within that sequence.
    - Provides operator++ (both prefix and postfix) and operator* for dereferencing.

  Notes:
    - operator++ moves to the next index; if already at last, it advances to “end” without throwing.
      A subsequent ++ from “end” will throw std::runtime_error("Increment past end").
    - operator* throws std::runtime_error("Iterator out of range") if index is invalid.
*/

namespace container {

template<typename ContainerType, typename ValueType>
class BaseIterator {
protected:
    const ContainerType* containerPtr = nullptr;
    size_t index = 0;
    std::shared_ptr<std::vector<size_t>> orderIndices;

    // Validate that dereference is within range
    void validateDereference() const {
        if (!containerPtr || index >= orderIndices->size()) {
            throw std::runtime_error("Iterator out of range");
        }
    }

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = ValueType;
    using pointer           = const ValueType*;
    using reference         = const ValueType&;
    using difference_type   = std::ptrdiff_t;

    BaseIterator() = default;
    BaseIterator(const ContainerType* cont, std::shared_ptr<std::vector<size_t>> seq, size_t startIdx = 0)
        : containerPtr(cont), index(startIdx), orderIndices(std::move(seq)) {}
    BaseIterator(const BaseIterator& other) = default;
    BaseIterator& operator=(const BaseIterator& other) = default;
    virtual ~BaseIterator() = default;

    // Pre-increment: move to next index or to “end”
    BaseIterator& operator++() {
        size_t n = orderIndices->size();
        if (index >= n) {
            throw std::runtime_error("Increment past end");
        }
        if (index + 1 >= n) {
            index = n;  // Move to one-past-last (end)
            return *this;
        }
        ++index;
        return *this;
    }

    // Post-increment: returns old state, then increments
    BaseIterator operator++(int) {
        BaseIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    // Dereference: return the element at the current index
    const ValueType& operator*() const {
        validateDereference();
        return containerPtr->elements[(*orderIndices)[index]];
    }

    // Equality: same container pointer and same index
    bool operator==(const BaseIterator& other) const {
        return containerPtr == other.containerPtr && index == other.index;
    }

    bool operator!=(const BaseIterator& other) const {
        return !(*this == other);
    }
};

} // namespace container

#endif // BASEITERATOR_HPP
