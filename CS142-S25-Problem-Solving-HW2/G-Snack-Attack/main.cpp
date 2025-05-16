#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

static const int64_t NEG_INF = -1e9;

// movement directions: stationary, up, down, left, right
static const int64_t move_row[5] = {0, -1, +1, 0, 0};
static const int64_t move_column[5] = {0, 0, 0, -1, +1};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t square_grid_size;
  uint64_t num_popcorn_drops;
  uint64_t num_boulder_drops;
  uint64_t starting_row;
  uint64_t starting_column;
  uint64_t row;
  uint64_t column;
  uint64_t time;
  uint64_t T_max = 0;
  uint64_t temp_time;
  uint64_t temp_row;
  uint64_t temp_column;
  int64_t final_score = 0;

  std::cin >> square_grid_size;
  std::cin >> num_popcorn_drops;
  std::cin >> num_boulder_drops;
  std::cin >> starting_row;
  std::cin >> starting_column;

  std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> popcorn_events(num_popcorn_drops);
  std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> boulder_events(num_boulder_drops);
  std::vector<std::vector<int64_t>> empty_table(square_grid_size, std::vector<int64_t>(square_grid_size, NEG_INF));

  for ( uint64_t i = 0; i < num_popcorn_drops; ++i )
  {
    std::cin >> row;
    std::cin >> column;
    std::cin >> time;

    popcorn_events[i] = { time, row, column };

    T_max = std::max(T_max, time);
  }

  for ( uint64_t i = 0; i < num_boulder_drops; ++i )
  {
    std::cin >> row;
    std::cin >> column;
    std::cin >> time;

    boulder_events[i] = { time, row, column };

    T_max = std::max(T_max, time);
  }

  // popcorn[t][r][c] = number of kernels falling on (r,c) at time t
  // boulder[t][r][c] = does boulder fall on (r, c) at time t
  std::vector<std::vector<std::vector<uint64_t>>> popcorn(T_max + 1, std::vector<std::vector<uint64_t>>(square_grid_size, std::vector<uint64_t>(square_grid_size, 0)));
  std::vector<std::vector<std::vector<bool>>> boulder(T_max + 1, std::vector<std::vector<bool>>(square_grid_size, std::vector<bool>(square_grid_size, false)));

  for ( uint64_t i = 0; i < popcorn_events.size(); ++i )
  {
    // unpack tuple
    std::tie(temp_time, temp_row, temp_column) = popcorn_events[i];

    ++popcorn[temp_time][temp_row][temp_column];
  }

  for ( uint64_t i = 0; i < boulder_events.size(); ++i )
  {
    std::tie(temp_time, temp_row, temp_column) = boulder_events[i];

    boulder[temp_time][temp_row][temp_column] = true;
  }





  // 2D DP tracking previous time world and current time world states
  std::vector<std::vector<int64_t>> dp_previous_time(square_grid_size, std::vector<int64_t>(square_grid_size, NEG_INF));
  std::vector<std::vector<int64_t>> dp_current_time(square_grid_size, std::vector<int64_t>(square_grid_size, NEG_INF));

  // we know our starting point, so we can start by work on next (current) time using initialized previous time
  dp_previous_time[starting_row][starting_column] = 0;



  // already initialized dp_previous_time, so start from t = 1
  for ( uint64_t t = 1; t <= T_max; ++t )
  {
    // for ( uint64_t r = 0; r < square_grid_size; ++r )
    // {
    //   for ( uint64_t c = 0; c < square_grid_size; ++c )
    //   {
    //     dp_current_time[r][c] = NEG_INF;
    //   }
    // }

    // reset dp_current_time to NEG_INF
    dp_current_time = empty_table;




    // compute dp_current_time from dp_previous_time
    for ( uint64_t processing_row = 0; processing_row < square_grid_size; ++processing_row )
    {
      for ( uint64_t processing_column = 0; processing_column < square_grid_size; ++processing_column )
      {
        // find best predecessor
        int64_t best_previous_popcorn = NEG_INF;

        // check all movement directions
        for ( uint64_t d = 0; d < 5; ++d )
        {
          int64_t predecessor_row = static_cast<int64_t>(processing_row) + move_row[d];
          int64_t predecessor_column = static_cast<int64_t>(processing_column) + move_column[d];

          // check predecessor moved bounds
          if ( predecessor_row < 0 || predecessor_row >= static_cast<int64_t>(square_grid_size) || predecessor_column < 0 || predecessor_column >= static_cast<int64_t>(square_grid_size) )
          {
            continue;
          }

          best_previous_popcorn = std::max(best_previous_popcorn, dp_previous_time[static_cast<uint64_t>(predecessor_row)][static_cast<uint64_t>(predecessor_column)]);
        }


        // the initialized 0 score helps avoid this and start buillding up dp_current_time
        if ( best_previous_popcorn == NEG_INF )
        {
          continue;
        }

        // collect popcorn
        uint64_t new_popcorn = static_cast<uint64_t>(best_previous_popcorn) + popcorn[t][processing_row][processing_column];

        // check boulder hit
        if ( boulder[t][processing_row][processing_column] )
        {
          // lose ceil(h/2)
          uint64_t lose = (new_popcorn + 1) / 2;
          new_popcorn -= lose;
        }

        dp_current_time[static_cast<uint64_t>(processing_row)][static_cast<uint64_t>(processing_column)] = static_cast<int64_t>(new_popcorn);
      }
    }

    // swap time world states to process next current time using current as previous time state
    dp_previous_time.swap(dp_current_time);
  }

  // answer should be in previous time world because of swap at end of processing iteration
  for ( uint64_t r = 0; r < square_grid_size; ++r )
  {
    for ( uint64_t c = 0; c < square_grid_size; ++c )
    {
      final_score = std::max(final_score, dp_previous_time[r][c]);
    }
  }


  std::cout << final_score;

  return 0;
}
