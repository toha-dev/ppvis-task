#pragma once

template <class T>
class UnidirectionalIterator {
 public:
  virtual T& Value() const = 0;
  virtual bool IsEnd() const = 0;
  virtual bool Next() = 0;
};