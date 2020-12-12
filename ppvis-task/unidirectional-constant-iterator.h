#pragma once

template <class T>
class UnidirectionalConstantIterator {
 public:
  virtual const T& Value() const = 0;
  virtual bool IsEnd() const = 0;
  virtual bool Next() = 0;
};