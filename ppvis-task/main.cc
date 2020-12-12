#include <iostream>
#include "single-linked-list.h"
#include "double-linked-list.h"

#include "queue.h"

void PrintTestSingleList() {
  std::cout << "Single linked list: " << std::endl;
  SingleLinkedList<int> list;

  list.PushBack(4);
  list.PushFront(3);
  list.PushBack(5);
  list.PushFront(2);
  list.PushFront(1);

  std::cout << " Print: " << std::endl;
  for (auto it = list.CBegin(); !it->IsEnd(); it->Next()) {
    std::cout << "  " << it->Value() << std::endl;
  }

  std::cout << std::endl;

  auto it = list.Find(2);

  std::cout << " Value 2 found: " << (!it->IsEnd()) << std::endl;

  std::cout << " Erase 2" << std::endl;
  list.Erase(*it);

  it = list.Find(2);
  std::cout << " Value 2 found: " << (!it->IsEnd()) << std::endl;

  std::cout << std::endl;

  std::cout << " Print: " << std::endl;
  for (auto it = list.CBegin(); !it->IsEnd(); it->Next()) {
    std::cout << "  " << it->Value() << std::endl;
  }
}

void PrintTestDoubleList() {
  std::cout << "Double linked list: " << std::endl;
  DoubleLinkedList<int> list;

  list.PushBack(4);
  list.PushFront(3);
  list.PushBack(5);
  list.PushFront(2);
  list.PushFront(1);

  std::cout << " Print: " << std::endl;
  for (auto it = list.CBegin(); !it->IsEnd(); it->Next()) {
    std::cout << "  " << it->Value() << std::endl;
  }

  std::cout << std::endl;

  auto it = list.Find(2);

  std::cout << " Value 2 found: " << (!it->IsEnd()) << std::endl;

  std::cout << " Erase 2" << std::endl;
  list.Erase(*it);

  it = list.Find(2);
  std::cout << " Value 2 found: " << (!it->IsEnd()) << std::endl;

  std::cout << std::endl;

  std::cout << " Print: " << std::endl;
  for (auto it = list.CBegin(); !it->IsEnd(); it->Next()) {
    std::cout << "  " << it->Value() << std::endl;
  }
}

void TestQueueSingle() {
  std::cout << "Queue as SingleLinkedList: " << std::endl;
  Queue<int, SingleLinkedList<int>> q;

  q.Push(1);
  q.Push(2);
  q.Push(3);

  while (!q.IsEmpty()) {
    std::cout << "  " << q.Front() << std::endl;

    q.Pop();
  }
}

void TestQueueDouble() {
  std::cout << "Queue as DoubleLinkedList: " << std::endl;
  Queue<int, DoubleLinkedList<int>> q;

  q.Push(1);
  q.Push(2);
  q.Push(3);

  while (!q.IsEmpty()) {
    std::cout << "  " << q.Front() << std::endl;

    q.Pop();
  }
}

int main()
{
  PrintTestSingleList();

  std::cout << "*****************************" << std::endl;

  PrintTestDoubleList();

  std::cout << "*****************************" << std::endl;
  
  TestQueueSingle();

  std::cout << "*****************************" << std::endl;

  TestQueueDouble();

  std::cout << "*****************************" << std::endl;


	system("pause");
	return 0;
}