// eitan.derdiger@gmail.com

#ifndef SIDECROSSORDER_HPP
#define SIDECROSSORDER_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include "BaseIterator.hpp"

/*
  SideCrossOrder.hpp defines the nested iterator class MyContainer<T>::SideCrossOrder,
  which traverses container elements in a "side-cross" pattern:
    - Visit the smallest element, then the largest,
      then the 2nd-smallest, then the 2nd-largest, and so on.

  Behavior:
    - Compute a vector of indices [0, 1, ..., n-1].
    - Sort those indices by comparing container.elements[a] < container.elements[b].
    - Then build a new sequence by alternately taking from the front (smallest)
      and back (largest) of the sorted index list.
    - Inherit BaseIterator<MyContainer<T>, T> for operator++ and operator* functionality.
*/

namespace container {

template<typename T>
class MyContainer;  // forward-declaration to allow nested definition

//Traverses the container in a "side-cross" pattern: smallest, largest, 2nd-smallest, 2nd-largest, etc.
template<typename T>
class MyContainer<T>::SideCrossOrder : public BaseIterator<MyContainer<T>, T> {
public:
    using Parent = BaseIterator<MyContainer<T>, T>;

    /**
     * @param cont Pointer to the container instance.
     * @param startIdx Starting index (default = 0 for begin; use container size for end).
     */
    SideCrossOrder(const MyContainer<T>* cont, size_t startIdx = 0)
        : Parent(cont, std::make_shared<std::vector<size_t>>(), startIdx)
    {
        size_t n = cont->elements.size();
        if (n == 0) {
            return;
        }

        // Create a vector of indices [0, 1, ..., n-1]
        std::vector<size_t> ascIdx(n);
        for (size_t i = 0; i < n; ++i) {
            ascIdx[i] = i;
        }
        // Sort indices by element value
        std::sort(ascIdx.begin(), ascIdx.end(),
                  [&](size_t a, size_t b) {
                      return cont->elements[a] < cont->elements[b];
                  });

        // Build the side-cross sequence: front, back, front+1, back-1, ...
        auto seqPtr = this->orderIndices;
        seqPtr->reserve(n);
        size_t lo = 0, hi = n - 1;
        while (lo <= hi) {
            seqPtr->push_back(ascIdx[lo]);
            if (lo != hi) {
                seqPtr->push_back(ascIdx[hi]);
            }
            ++lo;
            if (hi == 0) break;  // prevent underflow
            --hi;
        }
    }
};

} // namespace container

#endif // SIDECROSSORDER_HPP
