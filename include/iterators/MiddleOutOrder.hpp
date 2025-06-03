// eitan.derdiger@gmail.com

#ifndef MIDDLEOUTORDER_HPP
#define MIDDLEOUTORDER_HPP

#include <memory>
#include <vector>
#include "BaseIterator.hpp"

/*
  MiddleOutOrder.hpp defines the nested iterator class MyContainer<T>::MiddleOutOrder,
  which iterates over container elements in a middle-out pattern:
    - Visit the middle element first.
    - Then alternate left and right until all elements are covered.

  This iterator:
    - Computes the container size n.
    - Calculates mid = (n-1)/2.
    - Pushes mid onto orderIndices.
    - Alternately pushes left and right indices until all indices are in orderIndices.
    - Inherits BaseIterator<MyContainer<T>, T> for ++ and * operations.
*/

namespace container {

template<typename T>
class MyContainer;  // forward-declaration 

//Traverses the container in a "middle-out" pattern.
template<typename T>
class MyContainer<T>::MiddleOutOrder : public BaseIterator<MyContainer<T>, T> {
public:
    using Parent = BaseIterator<MyContainer<T>, T>;

    /**
     * @param cont Pointer to the container instance.
     * @param startIdx Starting index (default = 0 for begin; use container size for end).
     */
    MiddleOutOrder(const MyContainer<T>* cont, size_t startIdx = 0)
        : Parent(cont, std::make_shared<std::vector<size_t>>(), startIdx)
    {
        size_t n = cont->elements.size();
        if (n == 0) return;

        auto seqPtr = this->orderIndices;
        seqPtr->reserve(n);

        size_t mid = (n - 1) / 2;
        seqPtr->push_back(mid);

        size_t left = (mid == 0 ? n : mid) - 1;
        size_t right = mid + 1;
        while (seqPtr->size() < n) {
            if (left < n) {
                seqPtr->push_back(left);
                if (seqPtr->size() == n) break;
            }
            if (right < n) {
                seqPtr->push_back(right);
            }
            if (left == 0) {
                left = n;  // mark invalid
            } else {
                --left;
            }
            ++right;
        }
    }
};

} // namespace container

#endif // MIDDLEOUTORDER_HPP
