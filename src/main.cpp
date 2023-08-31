#include <map>
#include <algorithm>

#include "containerList.hpp"

#include "custom_allocator.hpp"

int calc_factorial(int num)
{
  int accum = 1;
  for (int i = 2; i <= num; ++i)
    accum *= i;
  return accum;
}

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

  for (int i{}; i < 10; i++)
  {
    map_std_alloc.insert({i, calc_factorial(i)});
  }

  std::map<int,
           int,
           std::less<int>,
           custom_allocator<std::pair<int, int>>>
      map_custom_alloc;

  for (int i{}; i < 10; i++)
  {
    map_custom_alloc.insert({i, calc_factorial(i)});
  }

  showElements(map_custom_alloc);

  ContainerList<int> custom_list{};

  for (size_t i = 0; i < 10; ++i)
  {
    custom_list.push_back(i);
  }

  ContainerList<int, custom_allocator<int>> custom_list_alloc{};

  for (size_t i = 0; i < 10; ++i)
  {
    custom_list_alloc.push_back(i);

    std::cout << custom_list_alloc[i] << " ";
  }

  std::cout << std::endl;

  return 0;
}