// eitan.derdiger@gmail.com

#ifndef REVERSEORDER_HPP
#define REVERSEORDER_HPP

#include <memory>
#include <vector>
#include "BaseIterator.hpp"

/*
  ReverseOrder.hpp defines the nested iterator class MyContainer<T>::ReverseOrder,
  which traverses container elements in reverse insertion order: last inserted to first.

  Behavior:
    - Precomputes an index sequence [n-1, n-2, ..., 0], where n = container size.
    - Inherits BaseIterator<MyContainer<T>, T> for operator++ and operator*.
*/

namespace container {

template<typename T>
class MyContainer;  // forward-declaration to allow nested definition

//Traverses in reverse insertion order: last inserted to first.
template<typename T>
class MyContainer<T>::ReverseOrder : public BaseIterator<MyContainer<T>, T> {
public:
    using Parent = BaseIterator<MyContainer<T>, T>;

    /**
     * @param cont Pointer to the container instance.
     * @param startIdx Starting index (default = 0 for begin; use container size for end).
     */
    ReverseOrder(const MyContainer<T>* cont, size_t startIdx = 0)
        : Parent(cont,
                 std::make_shared<std::vector<size_t>>(cont->elements.size()),
                 startIdx)
    {
        auto& seq = *this->orderIndices;
        size_t n = seq.size();
        // Fill with indices in reverse: n-1, n-2, …, 0
        for (size_t i = 0; i < n; ++i) {
            seq[i] = n - 1 - i;
        }
    }
};

} // namespace container

#endif // REVERSEORDER_HPP
