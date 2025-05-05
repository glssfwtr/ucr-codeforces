#include <algorithm>
#include <iostream>
#include <vector>

struct location
{
  unsigned int height;
  unsigned int i;
  unsigned int j;
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  unsigned int rows;
  unsigned int columns;
  std::vector<location> locations;

  unsigned int longest_route = 1;

  // define 2D movement
  const int direction_i[4] = {-1, 1, 0, 0};
  const int direction_j[4] = {0, 0, -1, 1};

  std::cin >> rows;
  std::cin >> columns;

  std::vector<std::vector<unsigned int>> heights_input(rows, std::vector<unsigned int>(columns));
  std::vector<std::vector<unsigned int>> dp(rows, std::vector<unsigned int>(columns, 1));

  for ( unsigned int i = 0; i < rows; ++i )
  {
    for ( unsigned int j = 0; j < columns; ++j )
    {
      std::cin >> heights_input[i][j];
    }
  }

  for ( unsigned int i = 0; i < rows; ++i )
  {
    for ( unsigned int j = 0; j < columns; ++j )
    {
      locations.push_back({heights_input[i][j], i, j});
    }
  }

  // sort all heights to be topological highest to lowest
  std::sort(locations.begin(), locations.end(),
  [](const location& a, const location& b)
  {
    return a.height > b.height;
  });











  for ( const auto& location : locations )
  {
    unsigned int current_height = location.height;
    unsigned int i = location.i;
    unsigned int j = location.j;

    unsigned int current_dp_height = dp[i][j];



    // check neighbors
    for ( unsigned int directions = 0; directions < 4; ++directions )
    {
      int new_i = static_cast<int>(i) + direction_i[directions];
      int new_j = static_cast<int>(j) + direction_j[directions];



      // check boundaries and height decrease
      if ( static_cast<int>(new_i) >= 0 && static_cast<unsigned int>(new_i) < rows && static_cast<int>(new_j) >= 0 && static_cast<unsigned int>(new_j) < columns && heights_input[static_cast<unsigned int>(new_i)][static_cast<unsigned int>(new_j)] < current_height )
      {
        dp[static_cast<unsigned int>(new_i)][static_cast<unsigned int>(new_j)] = std::max(dp[static_cast<unsigned int>(new_i)][static_cast<unsigned int>(new_j)], current_dp_height + 1);



        longest_route = std::max(longest_route, dp[static_cast<unsigned int>(new_i)][static_cast<unsigned int>(new_j)]);
      }
    }
  }


  std::cout << longest_route;





  return 0;
}
