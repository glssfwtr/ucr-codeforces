#include <bits/stdc++.h>
#include <string>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::pair<std::string, int> house1;
  std::pair<std::string, int> house2;
  std::string line;

  /*
    The first line includes two strings, which are the two houses competing in the game. Each string will be one of the four: Gryffindor, Hufflepuff, Ravenclaw, and Slytherin.


    INIT DATA
    std::cin default delimiter whitespace
    ex input: Gryffindor Hufflepuff
  */
  std::cin >> house1.first;
  std::cin >> house2.first;
  house1.second = 0;
  house2.second = 0;


  /*
    From the second line to the second last line, each line is one of the house name in the first line, which means this team scored in the game. Each score is 10 points.

    The last line, which ends the input, is always "[house] caught the Golden Snitch", which means the team [house] (one of the House name in the first line) caught the Golden Snitch and earned 150 points. The game then ended.


    Take inputs indefinitely until "[house] caught the Golden Snitch".
    For every individual house input, += 10 points.
  */

  while (std::getline(std::cin, line))
  {
    if (line.back() == 'h') // check final line for snitch caught, find last letter not matching any house in "Snitch"
    {
      std::string house_caught_snitch = line.substr(0, line.find(" ")); // from index 0 to index of first space, excluding latter index

      if (house_caught_snitch == house1.first)
      {
        house1.second += 150;
      }
      else if (house_caught_snitch == house2.first)
      {
        house2.second += 150;
      }

      break; // exit input loop as it is always the last line given by problem
    }
    else // single house input, += 10 points
    {
      if (line == house1.first)
      {
        house1.second += 10;
      }
      else if (line == house2.first)
      {
        house2.second += 10;
      }
    }
  }

  /*
    The first line in output is the winner of the game. It is either in the form of "[house] wins", where [house] is the winner, or "Tie", when it's a tie.

    The second line is the final score, in the form of "x-y" (no space around "-"), where x is the higher score and y is the lower score.
  */
  if (house1.second > house2.second)
  {
    std::cout << house1.first << " wins\n";
  }
  else if (house2.second > house1.second)
  {
    std::cout << house2.first << " wins\n";
  }
  else
  {
    std::cout << "Tie\n";
  }

  std::cout << std::max(house1.second, house2.second) << "-" << std::min(house1.second, house2.second) << "\n";

  return 0;
}
