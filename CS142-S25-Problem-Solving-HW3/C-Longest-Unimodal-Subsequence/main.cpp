#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  unsigned int current_lus_length;
  unsigned int max_lus_length = 0;
  unsigned int n;

  std::cin >> n;

  std::vector<unsigned int> a(n);
  for ( unsigned int i = 0; i < n; ++i )
  {
    std::cin >> a[i];
  }






  // compute LIS ending at each position i
  // extend longest subsequence of i - 1 for i
  // store length of LIS ENDING with element a[i]
  std::vector<unsigned int> LIS_DP(n, 1); // init LIS length for each element to 1
  for ( unsigned int i = 0; i < n; ++i )
  {
    // iterate through prev elements for (j < i)
    for ( unsigned int j = 0; j < i; ++j )
    {
      if ( a[j] < a[i] )
      {
        LIS_DP[i] = std::max(LIS_DP[i], LIS_DP[j] + 1);
      }
    }
  }





  // compute LDS at position i, only traversal is reversed from LIS to LDS
  // store length of the LDS STARTING with element a[i]
  std::vector<unsigned int> LDS_DP(n, 1);
  for ( int i = static_cast<int>(n) - 1; i >= 0; --i )
  {
    for ( unsigned int j = n - 1; static_cast<int>(j) > i; --j )
    {
      // if a[j] is smaller than a[i], we can start LDS at a[i]
      if ( a[j] < a[static_cast<unsigned int>(i)] )
      {
        LDS_DP[static_cast<unsigned int>(i)] = std::max(LDS_DP[static_cast<unsigned int>(i)], LDS_DP[j] + 1);
      }
    }
  }


  for ( unsigned int i = 0; i < n; ++i )
  {
    // sum of LIS length ending at i and LDS length starting at i
    // is length of the unimodal subsequence with a[i] as peak
    // subtract 1 because a[i] is counted in both
    current_lus_length = LIS_DP[i] + LDS_DP[i] - 1;

    max_lus_length = std::max(max_lus_length, current_lus_length);
  }

  std::cout << max_lus_length;

  return 0;
}