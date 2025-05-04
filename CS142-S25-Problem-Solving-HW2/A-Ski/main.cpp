#include <algorithm>
#include <iostream>
#include <vector>

struct location
{
  int height;
  int i;
  int j;
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int rows;
  int columns;
  std::vector<location> locations;

  int longest_route = 1;

  // define 2D movement
  const int direction_i[4] = {-1, 1, 0, 0};
  const int direction_j[4] = {0, 0, -1, 1};

  std::cin >> rows;
  std::cin >> columns;

  std::vector<std::vector<int>> heights_input(rows, std::vector<int>(columns));
  std::vector<std::vector<int>> dp(rows, std::vector<int>(columns, 1));

  for ( int i = 0; i < rows; ++i )
  {
    for ( int j = 0; j < columns; ++j )
    {
      std::cin >> heights_input[i][j];
    }
  }

  for ( int i = 0; i < rows; ++i )
  {
    for ( int j = 0; j < columns; ++j )
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
    int current_height = location.height;
    int i = location.i;
    int j = location.j;

    int current_dp_height = dp[i][j];



    // check neighbors
    for ( int directions = 0; directions < 4; ++directions )
    {
      int new_i = i + direction_i[directions];
      int new_j = j + direction_j[directions];



      // check boundaries and height decrease
      if ( new_i >= 0 && new_i < rows && new_j >= 0 && new_j < columns && heights_input[new_i][new_j] < current_height )
      {
        dp[new_i][new_j] = std::max(dp[new_i][new_j], current_dp_height + 1);



        longest_route = std::max(longest_route, dp[new_i][new_j]);
      }
    }
  }


  std::cout << longest_route;





  return 0;
}
