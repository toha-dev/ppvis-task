#pragma once
#include <memory>

#include "unidirectional-iterator.h"
#include "unidirectional-constant-iterator.h"

template <class T>
class UnidirectionalIteratorBehaviour {
 public:
  virtual std::shared_ptr<UnidirectionalIterator<T>> Begin() = 0;
  virtual std::shared_ptr<UnidirectionalConstantIterator<T>> CBegin() const = 0;
};