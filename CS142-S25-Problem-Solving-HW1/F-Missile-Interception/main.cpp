#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int DistanceSquared(int x1, int y1, int x2, int y2)
{
  return ( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) );
}


int main()
{
  int x1, y1, x2, y2;
  std::size_t n;

  std::vector<std::pair<int, int>> distance_pairs;

  int m_x;
  int m_y;


  std::cin >> x1;
  std::cin >> y1;
  std::cin >> x2;
  std::cin >> y2;

  std::cin >> n;

  int result = INT_MAX;

  // get all squared distances to both system coordinates
  for ( std::size_t i = 0; i < n; ++i )
  {
    std::cin >> m_x;
    std::cin >> m_y;

    int distance1 = DistanceSquared(x1, y1, m_x, m_y);
    int distance2 = DistanceSquared(x2, y2, m_x, m_y);

    distance_pairs.push_back({distance1, distance2});
  }

  // sort distance based on first system's pair.first increasing order
  std::sort(distance_pairs.begin(), distance_pairs.end());






  // dp[i] = min_radius^2 for system 2 to cover all missiles
  std::vector<int> dp_table(n + 1, 0);

  // the min of radius^2 needed to cover every missile
  // min radius^2 is max of radius^2 needed for next to last missile
  // let min radius determined by farthest missile instead
  for ( int i = n - 1; i >= 0; --i )
  {
    dp_table[i] = std::max(dp_table[i + 1], distance_pairs[i].second);
  }

  result = std::min(result, dp_table[0]);


  // find optimal, minimal point by going through dp table current index and dp + 1
  for ( std::size_t i = 0; i < n; ++i )
  {
    int r1_sqr = distance_pairs[i].first;
    int r2_sqr = dp_table[i + 1];

    result = std::min(result, r1_sqr + r2_sqr);
  }

  result = std::min(result, distance_pairs[n - 1].first);

  std::cout << result;


  return 0;
}