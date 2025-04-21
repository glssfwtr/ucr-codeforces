#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>


bool CheckTvAngle(int x, int y)
{
  // tv at center east wall 500/2 = 250
  // y 200->300 height tv center of mass exact y=250 but +-50 for 100 units wide
  // treat entire area covered by tv as rectangle and is considered in front of tv
  // use arctan opp/adj, calculate the triangle of difference


  int tv_x = 500;
  int tv_y = 250;

  // do we really need this?
  // // sheldon is in range of tv rectangle
  // if (x < tv_x && y == tv_y)
  // {
  //   return false;
  // }

  double difference_x = (tv_x - x); // x will always be less than tv_x position on left < right
  double difference_y = abs(y - tv_y); // y can be above or below forming triangle

  // prevent division by zero since sheldon is on the right angle
  // how tf does this dude sit like this??????
  if ( std::abs(difference_x) < 1e-9 )
  {
    return true;
  }

  double angle = std::atan(difference_y / difference_x) * 180.0 / M_PI;

  return ( angle <= 45.0 );
}


bool CheckWindows(int x, int south_window, int north_window)
{
  // simply check is between in terms of x
  // moving along y doesn't make sense since windows are pointing vertically, check x threshold instead
  return ( (x >= south_window && x <= south_window + 100)
            && (x >= north_window && x <= north_window + 100) );
}


bool CheckRadiator(int x, int y, int closest_c1, int farthest_c2, int radiation_x, int radiation_y)
{
  // diff sheldon and radiator
  int difference_x = x - radiation_x;
  int difference_y = y - radiation_y;

  // straight single distance value point to point of closest and farthest radiate
  double euclidean_distance = std::sqrt(std::pow(difference_x, 2) + std::pow(difference_y, 2));

  return ( closest_c1 <= euclidean_distance && euclidean_distance <= farthest_c2 );
}



int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  // radiate distance tolerance
  int closest_c1;
  int farthest_c2;
  // radiate coordinate
  int radiation_x;
  int radiation_y;

  // window coordinates
  int south_window; // (s,0) and (s+100,0)
  int north_window; // (n,500) to (n+100,500)

  size_t num_query_tests;

  // tv values always middle east wall



  // read input values
  std::cin >> closest_c1;
  std::cin >> farthest_c2;
  std::cin >> radiation_x;
  std::cin >> radiation_y;

  std::cin >> south_window;
  std::cin >> north_window;

  std::cin >> num_query_tests;

  std::vector<std::pair<std::pair<int, int>, bool>> query_answers(num_query_tests);

  for ( std::size_t i = 0; i < num_query_tests; ++i )
  {
    std::cin >> query_answers[i].first.first;
    std::cin >> query_answers[i].first.second;

    if ( CheckTvAngle(query_answers[i].first.first, query_answers[i].first.second)
          && CheckWindows(query_answers[i].first.first, south_window, north_window)
          && CheckRadiator(query_answers[i].first.first, query_answers[i].first.second, closest_c1, farthest_c2, radiation_x, radiation_y) )
    {
      query_answers[i].second = true;
    }
    else
    {
      query_answers[i].second = false;
    }
  }



  // std::cout << closest_c1 << " " << farthest_c2 << " " << radiation_x << " " << radiation_y << "\n";
  // std::cout << south_window << " " << north_window << "\n";
  // std::cout << num_query_tests << "\n";
  // for (const auto& query : query_answers)
  // {
  //   std::cout << query.first.first << " " << query.first.second << "\n";
  // }












  // output answer
  for (const auto& query : query_answers)
  {

    std::cout << (query.second ? "yes" : "no") << "\n";
  }


  return 0;
}
