#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

/*
try out hashing set instead of std::set
https://en.cppreference.com/w/cpp/utility/hash
*/
struct IntegerPairHash
{
  std::size_t operator()(const std::pair<int, int> &pair) const
  {
    auto hash1 = std::hash<int>{}(pair.first);
    auto hash2 = std::hash<int>{}(pair.second);

    return hash1 ^ (hash2 << 1);
  }
};

static std::unordered_set<std::pair<int, int>, IntegerPairHash> knight_moves =
{
  {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {2, -1}, {2, 1}, {1, -2}, {1, 2}
};

std::pair<int, int> ParseBoardPosition(const std::string &position)
{
  return std::pair<int, int>(position[0] - 'a', position[1] - '1'); // a is like 1 counting, but not 0 so if - '0' then off by 1 for index 0 grid
}

int FindMinimumMoves(const std::unordered_set<std::pair<int, int>, IntegerPairHash> &occupied_positions, const std::pair<int, int> &start_position, const std::pair<int, int> &end_position)
{
  std::pair<std::pair<int, int>, int> current_queue_temp;
  std::pair<int, int> position_temp;
  int moves_needed;
  int new_row;
  int new_col;

  // "minimum" so we want an optimial solution and thus bfs
  std::queue<std::pair<std::pair<int, int>, int>> bfs_queue; // <position, moves req to reach from start>/'
  std::unordered_set<std::pair<int, int>, IntegerPairHash> visited_positions;


  bfs_queue.push({start_position, 0});
  visited_positions.insert(start_position);

  while ( !bfs_queue.empty() )
  {
    current_queue_temp = bfs_queue.front();
    bfs_queue.pop();

    position_temp = current_queue_temp.first;

    for ( const auto &it : knight_moves )
    {
      new_row = position_temp.first + it.first;
      new_col = position_temp.second + it.second;

      if ( (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7) // 0-7 inclusive square board
        || (occupied_positions.find({new_row, new_col}) != occupied_positions.end())
        || (visited_positions.find({new_row, new_col}) != visited_positions.end()) )
      {
        continue;
      }

      moves_needed = current_queue_temp.second + 1;

      if ( new_row == end_position.first && new_col == end_position.second )
      {
        return moves_needed;
      }

      visited_positions.insert({new_row, new_col});
      bfs_queue.push({{new_row, new_col}, moves_needed});
    }

  }

  return -1; // queue empty and hasnt returned yet
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int num_positions_taken;
  std::string position_input;
  std::pair<int, int> start_position;
  std::pair<int, int> end_position;
  std::vector<int> results;


  while( std::cin >> num_positions_taken && num_positions_taken != -1 )
  {
    std::unordered_set<std::pair<int, int>, IntegerPairHash> occupied_positions;
    std::unordered_set<std::pair<int, int>, IntegerPairHash> visited_positions;

    // convert to 0 based index board notation
    for ( int i = 0 ; i < num_positions_taken; ++i )
    {
      std::cin >> position_input;

      occupied_positions.insert(ParseBoardPosition(position_input));
    }

    // for ( const auto &it : occupied_positions )
    // {
    //   std::cout << it.first << it.second << " ";
    // }

    // std::cout << "\n";

    std::cin >> position_input;
    start_position = ParseBoardPosition(position_input);

    std::cin >> position_input;
    end_position = ParseBoardPosition(position_input);

    results.push_back(FindMinimumMoves(occupied_positions, start_position, end_position));
  }

  for ( std::size_t i = 0; i < results.size(); ++i )
  {
    if ( results[i] == -1 )
    {
      std::cout << "Board " << i + 1 << ": not reachable\n";
    }
    else
    {
      std::cout << "Board " << i + 1 << ": " << results[i] << " moves\n";
    }
  }

  return 0;
}