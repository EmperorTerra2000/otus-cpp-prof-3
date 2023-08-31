#pragma once

#include <iostream>

template <class T>
struct Node
{
  T data;
  Node<T> *next;
  Node<T> *prev;
};

template <class T, class Allocator = std::allocator<T>>
class ContainerList
{
private:
  Node<T> *m_last;
  size_t m_size;

  using Alloc = typename Allocator::template rebind<Node<T>>::other;
  Alloc __allocator;

public:
  ContainerList()
  {
    m_last = nullptr;
    m_size = 0;
  }

  ContainerList(const ContainerList &other) = default;
  ContainerList &operator=(const ContainerList &other) = default;
  ~ContainerList() = default;

  void push_back(const T &value)
  {
    Node<T> *new_node = __allocator.allocate(1);
    __allocator.construct(new_node);

    new_node->data = value;   // добавляем элемент
    new_node->next = nullptr; // следующего элемента пока нет
    new_node->prev = m_last;  // предыдущим элементом станет последний
    m_last = new_node;        // добавляем указатель на последний

    if (m_last->prev)
    {
      m_last->prev->next = new_node;
    }

    m_size++; // добавляем размер
  }

  size_t size()
  {
    return m_size;
  }

  T operator[](int index)
  {
    Node<T> *current = m_last;

    for (size_t i = 1; i < size() - index; ++i)
    {
      current = current->prev;
    }

    return current->data;
  }
};