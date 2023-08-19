#include <map>
#include <algorithm>

#include "custom_allocator.hpp"

int calc_factorial(int num)
{
  int accum = 1;
  for (int i = 2; i <= num; ++i)
    accum *= i;
  return accum;
}

template <typename T>
void setElements(T &arr, int size)
{
  for (int i{}; i < size; i++)
  {
    arr.insert({i, calc_factorial(i)});
  }
};

template <typename T>
void showElements(T &arr)
{
  for (auto &el : arr)
  {
    std::cout << el.first << " " << el.second << " | ";
  }

  std::cout << std::endl;
}

int main()
{
  std::map<int, int> map_std_alloc;

  setElements(map_std_alloc, 10);

  std::map<int,
           int,
           std::less<int>,
           custom_allocator<std::pair<int, int>>>
      map_custom_alloc;

  setElements(map_custom_alloc, 10);
  showElements(map_custom_alloc);

  return 0;
}