#pragma once
#include <memory>

#include "list-behaviour.h"
#include "bidirectional-iterator-behaviour.h"
#include "unidirectional-iterator.h"

template <class T>
class DoubleLinkedList : public ListBehaviour<T>, public BidirectionalIteratorBehaviour<T> {
  struct Node {
    Node(const T& node_value, std::shared_ptr<Node> previous_node, 
      std::shared_ptr<Node> next_node) : previous(previous_node), 
        next(next_node), value(node_value) {}

    T value;
    std::shared_ptr<Node> previous;
    std::shared_ptr<Node> next;
  };

 public:
  class DoubleLinkedListIterator : public BidirectionalIterator<T> {
   public:
    DoubleLinkedListIterator(const std::shared_ptr<Node>& iterator_node)
        : current_node_(iterator_node) {}

    T& Value() const override { return current_node_->value; };
    bool IsEnd() const override { return current_node_ == nullptr; };
    bool Next() override { current_node_ = current_node_->next; return !IsEnd(); };
    bool Previous() override { current_node_ = current_node_->previous; return !IsEnd(); }

   private:
    std::shared_ptr<Node> Current() const { return current_node_; }

    std::shared_ptr<Node> current_node_;
    friend DoubleLinkedList;
  };

  class DoubleLinkedListConstantIterator : public BidirectionalConstantIterator<T> {
   public:
     DoubleLinkedListConstantIterator(const DoubleLinkedListIterator& iterator)
         : iterator_(iterator) {}

    const T& Value() const override { return iterator_.Value(); };
    bool IsEnd() const override { return iterator_.IsEnd(); };
    bool Next() override { return iterator_.Next(); };
    bool Previous() override { return iterator_.Previous(); }

   private:
    DoubleLinkedListIterator iterator_;
  };

  void PushFront(const T& value) override;
  void PushBack(const T& value) override;
  void PopFront() override;
  void PopBack() override;

  void Erase(const UnidirectionalIterator<T>& iterator) override;
  std::shared_ptr<UnidirectionalIterator<T>> Find(const T& value) override;

  bool IsEmpty() const override { return size_ == 0; };

  std::shared_ptr<BidirectionalIterator<T>> Begin() override {
    return std::make_shared<DoubleLinkedListIterator>(head_);
  }

  std::shared_ptr<BidirectionalConstantIterator<T>> CBegin() const override {
    return std::make_shared<DoubleLinkedListConstantIterator>(DoubleLinkedListIterator(head_));
  }

 private:
  void InitializeFirstNode(const T& value);
  void Clear();

  size_t size_;

  std::shared_ptr<Node> head_;
};

template <class T>
void DoubleLinkedList<T>::PushFront(const T& value) {
  if (IsEmpty()) {
    InitializeFirstNode(value);
  } else {
    head_ = std::make_shared<Node>(value, nullptr, head_);
    head_->next->previous = head_;
  }

  ++size_;
}

template <class T>
void DoubleLinkedList<T>::PushBack(const T& value) {
  if (IsEmpty()) {
    InitializeFirstNode(value);
  } else {
    std::shared_ptr<Node> current = head_;
    while (current != nullptr && current->next != nullptr)
      current = current->next;

    current->next = std::make_shared<Node>(value, current, nullptr);
  }

  ++size_;
}

template <class T>
void DoubleLinkedList<T>::PopFront() {
  if (IsEmpty()) {
    return; // TODO: Throw exception instead
  }

  if (size_ == 1) {
    Clear();
  } else {
    head_ = head_->next;
    head_->previous = nullptr;
  }

  --size_;
}

template <class T>
void DoubleLinkedList<T>::PopBack() {
  if (IsEmpty()) {
    return; // TODO: Throw exception instead
  }

  if (size_ == 1) {
    Clear();
  } else {
    std::shared_ptr<Node> current = head_;
    while (current != nullptr && current->next != nullptr)
      current = current->next;

    current->next = nullptr;
  }

  --size_;
}

template <class T>
void DoubleLinkedList<T>::Clear() {
  head_ = nullptr;
}

template<class T>
void DoubleLinkedList<T>::Erase(const UnidirectionalIterator<T>& iterator) {
  DoubleLinkedListIterator it = (DoubleLinkedListIterator&)(iterator);
  
  std::shared_ptr<Node> current = it.Current();

  if (current == head_) {
    PopFront();
  } else if (current->next == nullptr) {
    PopBack();
  } else {
    std::shared_ptr<Node> previous = current->previous;
    std::shared_ptr<Node> next = current->next;

    previous->next = next;
    next->previous = previous;
  }
}

template <class T>
std::shared_ptr<UnidirectionalIterator<T>> DoubleLinkedList<T>::Find(const T& value) {
  for (auto it = Begin(); !it->IsEnd(); it->Next()) {
    if (it->Value() == value) {
      return it;
    }
  }

  return std::make_shared<DoubleLinkedListIterator>(nullptr);
}

template <class T>
void DoubleLinkedList<T>::InitializeFirstNode(const T& value) {
  head_ = std::make_shared<Node>(value, nullptr, nullptr);
}