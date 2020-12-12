#pragma once
#include "list-behaviour.h"

template <class T, class U> 
class Queue {
 static_assert(std::is_base_of<ListBehaviour<T>, U>::value, "U must be derived from ListBehaviour");
 public:
  T Front() const { return list.Front(); }
  T Back() const { return list.Back(); }

  void Push(const T& value) { list.PushBack(value); }
  void Pop() { list.PopFront(); }

  size_t GetSize() const { return list.GetSize(); }
  bool IsEmpty() const { return list.IsEmpty(); }

 private:
  U list;
};