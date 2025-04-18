#include <iostream>
#include <vector>


bool CheckTvAngle(int x, int y)
{




}


bool CheckWindow(int south_window, int north_window)
{


}


bool CheckRadiator(int closest_c1, int farthest_c2, int radiation_x, int radiation_y)
{

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

  for (std::size_t i = 0; i < num_query_tests; ++i)
  {
    std::cin >> query_answers[i].first.first;
    std::cin >> query_answers[i].first.second;
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
