#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// 4 direction vectors for movement
const int64_t dx[4] = {-1, 1, 0, 0};
const int64_t dy[4] = {0, 0, -1, 1};

uint64_t rows;
uint64_t columns;

std::vector<std::string> lake_grid;

// track earliest day a cell can be reached
std::vector<std::vector<int64_t>> days; // use signedness for sentinel value

bool IsValidCell(int64_t x, int64_t y)
{
  return ( (x >= 0) && (x < static_cast<int64_t>(rows)) && (y >= 0) && (y < static_cast<int64_t>(columns)) );
}

// BFS to calculate days needed for ice to melt
void MeltIce(std::queue<std::pair<uint64_t, uint64_t>>& ice_queue)
{
  while ( !ice_queue.empty() )
  {
    uint64_t x = ice_queue.front().first;
    uint64_t y = ice_queue.front().second;

    ice_queue.pop();

    for ( std::size_t i = 0; i < 4; ++i )
    {
      int64_t new_x = static_cast<int64_t>(x) + dx[i];
      int64_t new_y = static_cast<int64_t>(y) + dy[i];

      // melt neighbors
      if (IsValidCell(new_x, new_y) && lake_grid[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] == 'X' && days[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] == -1)
      {
        // update day map with reachable area
        days[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] = days[x][y] + 1;
        ice_queue.push({new_x, new_y});
      }
    }
  }
}

// BFS to check if swans can meet tracing the day map, try threshold max day
bool CanMeet(uint64_t max_day, std::pair<uint64_t, uint64_t> start, std::pair<uint64_t, uint64_t> target_pos)
{
  uint64_t x;
  uint64_t y;
  std::queue<std::pair<uint64_t, uint64_t>> swan_queue;
  std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns, false));

  swan_queue.push(start);

  visited[start.first][start.second] = true;


  // bfs traversal
  while ( !swan_queue.empty() )
  {
    x = swan_queue.front().first;
    y = swan_queue.front().second;

    swan_queue.pop();

    if ( (x == target_pos.first) && (y == target_pos.second) )
    {
      return true;
    }

    // try traversing all directions less than max day threshold
    for ( std::size_t i = 0; i < 4; ++i )
    {
      int64_t new_x = static_cast<int64_t>(x) + dx[i];
      int64_t new_y = static_cast<int64_t>(y) + dy[i];

      if ( IsValidCell(new_x, new_y) && !visited[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] && (days[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] <= static_cast<int64_t>(max_day)) )
      {
        visited[static_cast<uint64_t>(new_x)][static_cast<uint64_t>(new_y)] = true;

        swan_queue.push({new_x, new_y});
      }
    }
  }


  return false;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::pair<int, int> swan1;
  std::pair<int, int> swan2;
  std::queue<std::pair<uint64_t, uint64_t>> ice_queue;

  std::cin >> rows;
  std::cin >> columns;

  // grid of rows of strings
  lake_grid.resize(rows);

  days.assign(rows, std::vector<int64_t>(columns, -1));

  for ( std::size_t i = 0; i < rows; ++i )
  {
    std::cin >> lake_grid[i];

    for ( std::size_t j = 0; j < columns; ++j )
    {
      if ( lake_grid[i][j] == 'L' )
      {
        if ( swan1 == std::make_pair(0, 0) )
        {
          swan1 = {i, j};
        }
        else
        {
          swan2 = {i, j};
        }

        lake_grid[i][j] = '.'; // under swan is water
      }

      if (lake_grid[i][j] == '.')
      {
        days[i][j] = 0; // water cells are reachable day 0

        ice_queue.push({i, j});
      }
    }
  }








  // try melting ice
  MeltIce(ice_queue);

  // binary search to find earliest meeting day
  uint64_t left = 0;
  uint64_t right = 1500;
  int64_t result = -1;

  while ( left <= right )
  {
    uint64_t mid = (left + right) / 2; // try meeting on or before mid

    if ( CanMeet(mid, swan1, swan2) )
    {
      result = static_cast<int64_t>(mid);
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
  }

  std::cout << result;

  return 0;
}
