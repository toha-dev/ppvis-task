#pragma once
#include <memory>

#include "list-behaviour.h"
#include "unidirectional-iterator-behaviour.h"

template <class T>
class SingleLinkedList : public ListBehaviour<T>, public UnidirectionalIteratorBehaviour<T> {
  struct Node {
    Node(const T& node_value, std::shared_ptr<Node> next_node) 
        : value(node_value), next(next_node) {}

    T value;
    std::shared_ptr<Node> next;
  };

 public:
  class SingleLinkedListIterator : public UnidirectionalIterator<T> {
   public:
    SingleLinkedListIterator(const std::shared_ptr<Node>& iterator_node)
        : current_node_(iterator_node) {}

    T& Value() const override { return current_node_->value; }
    bool IsEnd() const override { return current_node_ == nullptr; }
    bool Next() override { current_node_ = current_node_->next; return !IsEnd(); }

   private:
    std::shared_ptr<Node> Current() const { return current_node_; }

    std::shared_ptr<Node> current_node_;
    friend SingleLinkedList;
  };

  class SingleLinkedListConstantIterator : public UnidirectionalConstantIterator<T> {
   public:
    SingleLinkedListConstantIterator(const SingleLinkedListIterator& iterator)
        : iterator_(iterator) {}

    const T& Value() const override { return iterator_.Value(); }
    bool IsEnd() const override { return iterator_.IsEnd(); }
    bool Next() override { return iterator_.Next(); }

   private:
    SingleLinkedListIterator iterator_;
  };

  SingleLinkedList() : head_(nullptr), size_(0) {}

  void PushFront(const T& value) override;
  void PushBack(const T& value) override;
  void PopFront() override;
  void PopBack() override;

  void Erase(const UnidirectionalIterator<T>& iterator) override;
  std::shared_ptr<UnidirectionalIterator<T>> Find(const T& value) override;

  bool IsEmpty() const override { return size_ == 0; }

  std::shared_ptr<UnidirectionalIterator<T>> Begin() override {
    return std::make_shared<SingleLinkedListIterator>(head_);
  }

  std::shared_ptr<UnidirectionalConstantIterator<T>> CBegin() const override {
    return std::make_shared<SingleLinkedListConstantIterator>(SingleLinkedListIterator(head_));
  }

 private:
  void InitializeFirstNode(const T& value);
  void Clear();

  std::shared_ptr<Node> head_;

  size_t size_;
};

template <class T>
void SingleLinkedList<T>::PushFront(const T& value) {
  if (IsEmpty()) {
    InitializeFirstNode(value);
  } else {
    head_ = std::make_shared<Node>(value, head_);
  }

  ++size_;
}

template <class T>
void SingleLinkedList<T>::PushBack(const T& value) {
  if (IsEmpty()) {
    InitializeFirstNode(value);
  } else {
    std::shared_ptr<Node> current = head_;
    while (current != nullptr && current->next != nullptr)
      current = current->next;

    current->next = std::make_shared<Node>(value, nullptr);
  }

  ++size_;
}

template <class T>
void SingleLinkedList<T>::PopFront() {
  if (IsEmpty()) {
    return; // TODO: Throw exception instead
  }

  if (size_ == 1) {
    Clear();
  } else {
    head_ = head_->next;
  }

  --size_;
}

template <class T>
void SingleLinkedList<T>::PopBack() {
  if (IsEmpty()) {
    return; // TODO: Throw exception instead
  }

  if (size_ == 1) {
    Clear();
  } else {
    std::shared_ptr<Node> current(head_);
    while (current && current->next && current->next->next)
      current = current->next;

    current->next = nullptr;
  }

  --size_;
}

template <class T>
void SingleLinkedList<T>::Clear() {
  head_ = nullptr;
}

template <class T>
void SingleLinkedList<T>::Erase(const UnidirectionalIterator<T>& iterator) {
  SingleLinkedListIterator it = (SingleLinkedListIterator&)(iterator);

  if (it.Current() == head_) {
    PopFront();
  } else if (it.Current()->next == nullptr) {
    PopBack();
  } else {
    std::shared_ptr<Node> current = head_;

    while (current != nullptr && current->next != it.Current()) {
      current = current->next;
    }

    if (current != nullptr) {
      it.Next();

      current->next = it.Current();
    }
  }
}

template<class T>
std::shared_ptr<UnidirectionalIterator<T>> SingleLinkedList<T>::Find(const T& value)
{
  for (auto it = Begin(); !it->IsEnd(); it->Next()) {
    if (it->Value() == value) {
      return it;
    }
  }

  return std::make_shared<SingleLinkedListIterator>(nullptr);
}

template <class T>
void SingleLinkedList<T>::InitializeFirstNode(const T& value) {
  head_ = std::make_shared<Node>(value, nullptr);
}