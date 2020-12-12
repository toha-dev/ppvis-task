#pragma once
#include <memory>

#include "bidirectional-iterator.h"
#include "bidirectional-constant-iterator.h"

template <class T>
class BidirectionalIteratorBehaviour {
 public:
  virtual std::shared_ptr<BidirectionalIterator<T>> Begin() = 0;
  virtual std::shared_ptr<BidirectionalConstantIterator<T>> CBegin() const = 0;
};