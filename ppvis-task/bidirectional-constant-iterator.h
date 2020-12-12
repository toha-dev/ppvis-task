#pragma once
#include "unidirectional-constant-iterator.h"

template <class T>
class BidirectionalConstantIterator : public UnidirectionalConstantIterator<T> {
 public:
  virtual bool Previous() = 0;
};