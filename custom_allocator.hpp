#pragma once

#include <iostream>

template <typename T, std::size_t DEFAULT_SIZE = 10>
class custom_allocator
{
public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;

  custom_allocator()
  {
    data = reinterpret_cast<T *>(std::malloc(DEFAULT_SIZE * sizeof(T)));

    if (data == nullptr)
    {
      std::cout << "exception: bad alloc (data = nullptr)";
      throw std::bad_alloc();
    }
  };

  ~custom_allocator()
  {
    delete data;
  };

  template <typename U>
  custom_allocator(const custom_allocator<U> &);

  template <typename U, std::size_t SIZE>
  custom_allocator(const custom_allocator<U, SIZE> &);

  T *allocate(std::size_t n)
  {
    if (memory_pool + n > DEFAULT_SIZE)
    {
      std::cout << "exception: bad alloc " << memory_pool << std::endl;
      throw std::bad_alloc();
    }

    memory_pool += n;

    return data + (memory_pool - n);
  };

  void deallocate(T *ptr, std::size_t size)
  {
    memory_pool -= size;

    if (memory_pool == 0)
    {
      std::free(data);
      data = nullptr;
    }
  };

  template <typename U>
  struct rebind
  {
    using other = custom_allocator<U>;
  };

private:
  std::size_t memory_pool{};
  T *data = nullptr;
};

template <typename T, typename U>
constexpr bool operator==(
    const custom_allocator<T> &a,
    const custom_allocator<U> &b) noexcept
{
  return a.data == b.data;
}

template <typename T, typename U>
constexpr bool operator!=(
    const custom_allocator<T> &a,
    const custom_allocator<U> &b) noexcept
{
  return a.data != b.data;
}

template <typename T, typename U, std::size_t X, std::size_t Y>
constexpr bool operator==(
    const custom_allocator<T, X> &a,
    const custom_allocator<U, Y> &b) noexcept
{
  return a.data == b.data;
}

template <typename T, typename U, std::size_t X, std::size_t Y>
constexpr bool operator!=(
    const custom_allocator<T, X> &a,
    const custom_allocator<U, Y> &b) noexcept
{
  return a.data != b.data;
}