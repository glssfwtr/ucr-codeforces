#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::size_t num_sectors;
  int full_score;
  int current_score;

  std::vector<int> darts_thrown;

  bool found_subtractable = false;

  std::vector<int> result_points(4, 0);




  std::cin >> num_sectors;
  std::cin >> full_score;

  // point-sector pairs
  std::vector<std::pair<int, int>> point_sectors(num_sectors);

  for ( std::size_t i = 0; i < num_sectors; ++i )
  {
    std::cin >> point_sectors[i].first;
    point_sectors[i].second = static_cast<int>(i + 1);
  }

  // sort each point sector based on highest score pair first which should reduce leonard's score faster?
  std::sort(point_sectors.begin(), point_sectors.end(), std::greater_equal<>());






  // each dart find sector without going into negative
  // if subtractable, then reduce the score and add sector index
  current_score = full_score;

  for ( std::size_t i = 0; i < 4; ++i )
  {
    found_subtractable = false;

    for ( const auto &sector : point_sectors )
    {
      if ( current_score >= sector.first || current_score == 0)
      {
        current_score -= sector.first;
        result_points[i] = sector.second;
        found_subtractable = true;



        break;
      }
    }


    if ( current_score < 0 )
    {
      current_score = full_score;
    }

    if ( !found_subtractable )
    {
      result_points[i] = 0;
    }
  }



  for ( std::size_t i = 0; i < 4; ++i )
  {
    std::cout << result_points[i] << " ";
  }

  return 0;
}
