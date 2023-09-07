#pragma once

#include <iostream>

template <class T>
struct Node
{
  T data;
  Node<T> *next;
  Node<T> *prev;

  ~Node()
  {
    std::cout << "Node destructor " << data << std::endl;

    // delete next;
  }
};

template <class T, class Allocator = std::allocator<T>>
class ContainerList
{
private:
  Node<T> *new_node;
  Node<T> *m_last;
  size_t m_size;

  using Alloc = typename Allocator::template rebind<Node<T>>::other;
  Alloc __allocator;

public:
  ContainerList()
  {
    m_last = nullptr;
    new_node = nullptr;
    m_size = 0;
  }

  ContainerList(const ContainerList &other) = default;
  ContainerList &operator=(const ContainerList &other) = default;
  ~ContainerList()
  {
    // запоминаем предыдущий элемент в списке
    Node<T> *current = m_last->prev;

    // деаллоцируем последний элемент
    __allocator.deallocate(m_last, 1);

    // деаллоцируем от последнего до первого элемента списка
    for (size_t i = 0; i < size() - 2; ++i)
    {
      current = current->prev;

      __allocator.deallocate(current->next, 1);
    }

    // деаллоцируем первый элемент
    __allocator.deallocate(current, 1);
  };

  void push_back(const T &value)
  {
    new_node = __allocator.allocate(1);
    __allocator.construct(new_node);

    new_node->data = value;   // добавляем элемент
    new_node->next = nullptr; // следующего элемента пока нет
    new_node->prev = m_last;  // предыдущим элементом станет последний
    m_last = new_node;        // добавляем указатель на последний

    if (m_last->prev)
    {
      m_last->prev->next = new_node;
    }

    m_size++; // увеличиваем размер
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