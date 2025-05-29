#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

const int NEG_INF = -1e9;
const int array_size = 200001; // -100000 to 0 to +100000, [0, 200000]
const int index_offset = 100000;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> dp(array_size, NEG_INF);
  uint64_t max_sum = 0;
  uint64_t n;

  // dead on middle
  // init state: sum_smartness = 0, sum_funness = 0
  dp[index_offset] = 0;


  std::cin >> n;

  std::vector<std::pair<int, int>> cows(n);

  for ( uint64_t i = 0; i < n; ++i )
  {
    std::cin >> cows[i].first;
    std::cin >> cows[i].second;
  }














  for ( uint64_t i = 0; i < cows.size(); ++i )
  {
    int current_cow_smartness = cows[i].first;
    int current_cow_funness = cows[i].second;

    std::vector<int> temp_dp(dp); // copy current dp to temp w/o taking current cow

    // check every smartness i guess??????? [0, 200000]
    for ( uint64_t j = 0; j < array_size; ++j )
    {

      // check if subset of cows is possible
      if ( dp[j] == NEG_INF )
      {
        continue;
      }

      // get new TS and convert TS back to index
      int new_TS = (static_cast<int>(j) - index_offset) + current_cow_smartness; // get new sum_s
      int new_TS_index = new_TS + index_offset;

      if ( new_TS_index < 0 || new_TS_index >= array_size )
      {
        continue;
      }

      // update temp if this cow gives a better TF with the new TS index access
      if ( temp_dp[static_cast<uint64_t>(new_TS_index)] < dp[j] + current_cow_funness )
      {
        temp_dp[static_cast<uint64_t>(new_TS_index)] = dp[j] + current_cow_funness;
      }
    }

    dp.swap(temp_dp); // update dp with new possible cow
  }


  // all cows processed, now find the max sum starting from non-negative smartness
  // since question constraints bans us from having negative smartness and funness
  for ( uint64_t i = index_offset; i < array_size; ++i )
  {
    if ( dp[i] >= 0 ) // check valid TF first
    {
      // TS as the index, and TF as value at i
      max_sum = std::max(max_sum, static_cast<uint64_t>(static_cast<int64_t>(i - index_offset) + dp[i]));
    }
  }

  std::cout << max_sum;

  return 0;
}