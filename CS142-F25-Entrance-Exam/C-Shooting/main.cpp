#include <iostream>
#include <cmath>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int num_shots;
  double x;
  double y;
  double distance_from_center;
  int current_shot_score;
  int total_score = 0;

  std::cin >> num_shots;

  for (int i = 0; i < num_shots; ++i)
  {
    std::cin >> x;
    std::cin >> y;

    // distance formula from center (0, 0) to (x, y)
    distance_from_center = sqrt(std::pow(x, 2) + std::pow(y, 2));

    if ( distance_from_center > 1.0 )
    {
      continue; // skip shot score calculation if outside
    }

    /*
      10 bands to score from 10 to 1 in to out

      0.0 - 0.1 = 10
      0.1 - 0.2 = 9
      0.2 - 0.3 = 8
    */

    // std::cout << "Distance: " << distance_from_center << "\n";

    // convert landing distance to scoring band from center
    current_shot_score = 10 - static_cast<int>(10 * distance_from_center);

    total_score += current_shot_score;
  }

  std::cout << total_score;

  return 0;
}