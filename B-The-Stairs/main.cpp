#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::size_t num_steps;
  std::vector<int> step_altitudes;
  std::vector<int> altitude_differences;
  std::unordered_map<int, int> altitude_frequency; // <altitude difference, frequency>
  std::size_t bad_step = 0;
  std::pair<int, int> most_common_difference = {0, 0};

  /*'
    INPUT
    The first line contains one integer n, which is the number of steps in the stairs.

    The next line contains n integers, where the i-th integer is the altitude of the i-th stair, for 1≤i≤n.
    The heights can be in either ascending or descending.
  */
  std::cin >> num_steps;

  step_altitudes.resize(num_steps);

  for ( std::size_t i = 0; i < num_steps; ++i )
  {
    std::cin >> step_altitudes[i];
  }


  /*
    Find altered step

    Find dsifference between each step, map difference to frequency counter

    Find highest frequency, which is the common, then find the deviation from common
  */
  altitude_differences.resize(num_steps - 1);
  for ( std::size_t i = 0; i < num_steps - 1; ++i )
  {
    altitude_differences[i] = step_altitudes[i + 1] - step_altitudes[i];
    ++altitude_frequency[altitude_differences[i]];
  }



  // find most common difference to define normal steps
  for ( const std::unordered_map<int, int>::iterator::value_type &unordered_map_pair : altitude_frequency )
  {
    if ( most_common_difference.second < unordered_map_pair.second )
    {
      most_common_difference.first = unordered_map_pair.first;
      most_common_difference.second = unordered_map_pair.second;
    }
  }



  // bad step in middle
  for ( std::size_t i = 0; i < num_steps - 1; ++i )
  {
    if ( (altitude_differences[i] != altitude_differences[i + 1]) )
    {
      bad_step = i + 3; // current i of difference arr + 1 + 1 (for 0 index) + 1 (for bad step)

      break;
    }
  }

  // sanity check the beginning first 2 bad, then has to be 2nd that is bad
  if ( altitude_differences[0] != most_common_difference.first && altitude_differences[1] != most_common_difference.first )
  {
    bad_step = 2;
  }
  else if ( altitude_differences[0] != most_common_difference.first ) // 0th difference (A1 - A0) is the only weird, so has to be one over the first, so 1
  {
    bad_step = 1;
  }


  std::cout << bad_step << '\n';

  return 0;
}