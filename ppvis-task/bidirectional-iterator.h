#pragma once
#include "unidirectional-iterator.h"

template <class T>
class BidirectionalIterator : public UnidirectionalIterator<T> {
 public:
  virtual bool Previous() = 0;
};