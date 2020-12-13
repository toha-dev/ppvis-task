#pragma once
#include "list-behaviour.h"

template <class T, class U> 
class Queue {
 static_assert(std::is_base_of<ListBehaviour<T>, U>::value, "U must be derived from ListBehaviour");
 public:
  T Front() const {
    return list.CBegin()->Value(); 
  }

  T Back() const { 
    const T *result = nullptr;
    for (auto it = list.CBegin(); !it->IsEnd(); it->Next()) {
      result = &it->Value();
    }
    
    return *result;
  }

  void Push(const T& value) { list.PushBack(value); }
  void Pop() { list.PopFront(); }

  bool IsEmpty() const { return list.IsEmpty(); }

 private:
  U list;
};
