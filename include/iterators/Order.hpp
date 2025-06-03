// eitan.derdiger@gmail.com

#ifndef ORDER_HPP
#define ORDER_HPP

#include <memory>
#include <vector>
#include "BaseIterator.hpp"

/*
  Order.hpp defines the nested iterator class MyContainer<T>::Order,
  which traverses container elements in insertion order (first inserted to last).

  Behavior:
    - Precomputes an index sequence [0, 1, ..., n-1].
   */

namespace container {

template<typename T>
class MyContainer;  // forward-declaration to allow nested definition

//Traverses the container in insertion order: first inserted to last.
template<typename T>
class MyContainer<T>::Order : public BaseIterator<MyContainer<T>, T> {
public:
    using Parent = BaseIterator<MyContainer<T>, T>;

    /**
     * @param cont Pointer to the container instance.
     * @param startIdx Starting index (default = 0 for begin; use container size for end).
     */
    Order(const MyContainer<T>* cont, size_t startIdx = 0)
        : Parent(cont,
                 std::make_shared<std::vector<size_t>>(cont->elements.size()),
                 startIdx)
    {
        auto& seq = *this->orderIndices;
        size_t n = seq.size();
        for (size_t i = 0; i < n; ++i) {
            seq[i] = i;
        }
    }
};

} // namespace container

#endif // ORDER_HPP
