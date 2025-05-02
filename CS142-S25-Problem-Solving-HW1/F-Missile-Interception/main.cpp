#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

double DistanceSquared(double x1, double y1, double x2, double y2)
{
  return ( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) );
}

int main()
{
  int n;
  int x1, y1, x2, y2;

  std::cin >> x1;
  std::cin >> y1;
  std::cin >> x2;
  std::cin >> y2;

  std::cin >> n;

  std::vector<std::pair<int, int>> missiles(n);
  std::vector<double> dist1(n);
  std::vector<double> dist2(n);

  for ( std::size_t i = 0; i < n; ++i )
  {
    std::cin >> missiles[i].first >> missiles[i].second;
  }








  // precompute distances each missile to both systems
  for ( std::size_t i = 0; i < n; ++i )
  {
    dist1[i] = DistanceSquared(x1, y1, missiles[i].first, missiles[i].second);
    dist2[i] = DistanceSquared(x2, y2, missiles[i].first, missiles[i].second);
  }

  // deprecated but fk it we ball
  double result = LLONG_MAX;

  // try all pairs of missile radius
  for ( int i = -1; i < n; ++i )
  {
    for ( int j = -1; j < n; ++j )
    {
      // set radius based on chosen missiles
      // -1 represents using radius 0 (not covering any missiles)
      double r1_squared = (i == -1) ? 0 : dist1[i];
      double r2_squared = (j == -1) ? 0 : dist2[j];

      // check if all missiles covered with these radius
      bool all_covered = true;

      for ( int k = 0; k < n; ++k )
      {
        if ( dist1[k] > r1_squared && dist2[k] > r2_squared )
        {
          all_covered = false;
          break;
        }
      }


      if ( all_covered )
      {
        result = std::min(result, r1_squared + r2_squared);
      }
    }
  }

  cout << result << "\n";

  return 0;
}