#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  unsigned int length;
  unsigned int num_flavors;
  std::string candy_string;

  std::cin >> length;
  std::cin >> num_flavors;

  // dp[i][j] = min cost to make substring from [i...j] to palindrome
  std::vector<std::vector<unsigned int>> dp(length, std::vector<unsigned int>(length, 0));

  std::vector<unsigned int> prices(num_flavors);

  for ( unsigned int i = 0; i < num_flavors; i++ )
  {
    std::cin >> prices[i];
  }

  std::cin >> candy_string;









  // recursive -> iterative base: single characters already palindrome

  // check substrings of length [2...L]
  for ( unsigned int L = 2; L <= length; ++L )
  {
    for ( unsigned int i = 0; i <= length - L; i++)
    {
      unsigned int j = i + L - 1;

      // if match, current substring depends on inner cost, bottom right
      if ( candy_string[i] == candy_string[j] )
      {
        dp[i][j] = dp[i + 1][j - 1];
      }
      else
      {
        /*
          1. insert character matching right boundary at left boundary
          OR
          2. insert character matching  left boundary at right boundary
        */

        // get price at p[x]  then insert, problem is moving pointer after insert
        unsigned int left_insert_cost = prices[static_cast<unsigned int>(candy_string[j] - 'a')] + dp[i][j - 1];
        unsigned int right_insert_cost = prices[static_cast<unsigned int>(candy_string[i] - 'a')] + dp[i + 1][j];

        dp[i][j] = std::min(left_insert_cost, right_insert_cost);
      }
    }
  }




  std::cout << dp[0][length - 1];

  return 0;
}