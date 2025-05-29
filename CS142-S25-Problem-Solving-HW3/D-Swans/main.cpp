#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

// Fenwick Tree for finding maximum in a range efficiently
class FenwickTree
{
public:
  std::vector<uint64_t> tree;
  uint64_t size;

  FenwickTree(uint64_t n) : size(n)
  {
    tree.resize(n + 1, 0);
  }


  // set all node in the tree to max of new value if applicable
  void update(uint64_t index, uint64_t value)
  {
    while ( index <= size )
    {
      tree[index] = std::max(tree[index], value);

      index += index & -index;
    }
  }

  // retrieve maximum value within prefix range
  uint64_t query( uint64_t index )
  {
    uint64_t maxVal = 0;

    while ( index > 0 )
    {
      maxVal = std::max(maxVal, tree[index]);

      index -= index & -index;
    }

    return maxVal;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t max_sum = 0;
  uint64_t n;

  std::cin >> n;

  std::vector<uint64_t> fragment_values(n);

  for ( uint64_t i = 0; i < n; ++i )
  {
    std::cin >> fragment_values[i];
  }


  // init fenwick tree
  FenwickTree fenwick(1e6);

  // for each fragment
  for ( uint64_t i = 0; i < n; ++i )
  {
    // query tree for maximum sum of subsequences
    // ending with values less than the current fragment value
    uint64_t best_prev_sum = fenwick.query(fragment_values[i] - 1);

    // compute current sum by adding the current fragment value
    // to the best previous sum
    uint64_t current_sum = best_prev_sum + fragment_values[i];

    // update tree with current fragment value and its sum
    fenwick.update(fragment_values[i], current_sum);

    max_sum = std::max(max_sum, current_sum);
  }

  std::cout << max_sum;

  return 0;
}
