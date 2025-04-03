#include <algorithm> // for std::min brace initializer list
#include <iostream>
#include <string>
#include <vector>

// // STANDARD: row entries represent first string, column entries represent second string
// void print_dp_array(const std::vector<std::vector<int>> &dp, const std::string &standard_sheldon_answers, const std::string &raj_answers, std::size_t num_problems)
// {
//   std::cout << "  ";
//   for (std::size_t i = 0; i <= num_problems; ++i)
//   {
//     if (i == 0)
//     {
//       std::cout << "  ";
//     }
//     else
//     {
//       std::cout << raj_answers[i - 1] << " ";
//     }
//   }
//   std::cout << "\n";

//   for (std::size_t i = 0; i <= num_problems; ++i)
//   {
//     if (i == 0)
//     {
//       std::cout << "  ";
//     }
//     else
//     {
//       std::cout << standard_sheldon_answers[i - 1] << " ";
//     }

//     for (std::size_t j = 0; j <= num_problems; ++j)
//     {
//       std::cout << dp[i][j] << " ";
//     }
//     std::cout << "\n";
//   }
// }


int main()
{
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(0);

  /*
    Copy (replace)
    Omit (delete)
    Add (insert)

    sounds like a edit distance dp problem to get minimum number of single char edits to convert one string to another
  */

  std::size_t num_problems;
  std::string standard_sheldon_answers;
  std::string raj_answers;


  std::cin >> num_problems;
  std::cin >> standard_sheldon_answers;
  std::cin >> raj_answers;

  // initialize nxn dp array to 0, + 1 for empty string case
  std::vector<std::vector<int>> dp(num_problems + 1, std::vector<int>(num_problems + 1, 0));

  // if raj's string is empty, then the only way to convert sheldon's string to raj's string is to delete i characters from sheldon's string length
  for (std::size_t i = 0; i <= num_problems; ++i)
  {
    dp[i][0] = static_cast<int>(i);
  }

  // if sheldon's string is empty, then the only way to convert raj's string to sheldon's string is to add i characters to sheldon's string length
  for (std::size_t i = 0; i <= num_problems; ++i)
  {
    dp[0][i] = static_cast<int>(i);
  }



  for (std::size_t i = 1; i <= num_problems; ++i)
  {
    for (std::size_t j = 1; j <= num_problems; ++j)
    {
      // std::cout << i << " " << j << "\n";
      if (standard_sheldon_answers[i - 1] == raj_answers[j - 1]) // characters match
      {
        dp[i][j] = dp[i - 1][j - 1]; // no edits neededs
      }
      else // min of delete, insert, replace
      {
        dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}); // add 1 for edit operating, to match is to replace
      }


      // print_dp_array(dp, standard_sheldon_answers, raj_answers, num_problems);
    }
  }





  std::cout << dp[num_problems][num_problems];

  return 0;
}
