// eitan.derdiger@gmail.com

#ifndef ASCENDINGORDER_HPP
#define ASCENDINGORDER_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include "BaseIterator.hpp"

/*
  AscendingOrder.hpp defines the nested iterator class MyContainer<T>::AscendingOrder,
  which iterates over container elements in ascending value order.

  This iterator:
    - Precomputes an index sequence [0,1,…,n-1].
    - Sorts indices by comparing container.elements[a] < container.elements[b].
    - Inherits BaseIterator<MyContainer<T>, T> for ++ and * operations.
*/

namespace container {

template<typename T>
class MyContainer;  // forward-declaration

//Traverses the container in ascending order of element values.
template<typename T>
class MyContainer<T>::AscendingOrder : public BaseIterator<MyContainer<T>, T> {
public:
    using Parent = BaseIterator<MyContainer<T>, T>;

    /**
     * @param cont Pointer to the container instance.
     * @param startIdx Starting index (default = 0 for begin; use container size for end).
     */
    AscendingOrder(const MyContainer<T>* cont, size_t startIdx = 0)
        : Parent(cont,
                 std::make_shared<std::vector<size_t>>(cont->elements.size()),
                 startIdx)
    {
        auto& seq = *this->orderIndices;
        size_t n = seq.size();
        for (size_t i = 0; i < n; ++i) {
            seq[i] = i;
        }
        std::sort(seq.begin(), seq.end(),
                  [&](size_t a, size_t b) {
                      return cont->elements[a] < cont->elements[b];
                  });
    }
};

} // namespace container

#endif // ASCENDINGORDER_HPP
