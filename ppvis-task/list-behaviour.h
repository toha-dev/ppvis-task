#pragma once
#include "unidirectional-iterator.h"

template <class T>
class ListBehaviour {
 public:
  virtual void PushFront(const T& value) = 0;
  virtual void PushBack(const T& value) = 0;
  virtual void PopFront() = 0;
  virtual void PopBack() = 0;

  virtual void Erase(const UnidirectionalIterator<T>& iterator) = 0;
  virtual std::shared_ptr<UnidirectionalIterator<T>> Find(const T& value) = 0;

  virtual bool IsEmpty() const = 0;
};