#include <cstdint>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

// build adjacency list when checking moves
void CreateEdges(std::vector<std::vector<std::pair<uint64_t, uint64_t>>>& adjacency_list, uint64_t u, uint64_t v, uint64_t weight)
{
  adjacency_list[u].emplace_back(weight, v);
  adjacency_list[v].emplace_back(weight, u);

  return;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t rows;
  uint64_t columns;
  uint64_t total_candies = 0;
  uint64_t u_node; // u -> v

  std::pair<uint64_t, uint64_t> top_node; // (cost, node#)
  uint64_t top_node_cost;
  uint64_t top_node_number;

  std::cin >> rows;
  std::cin >> columns;

  // priority queue with pairs of (cost, node)
  std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<>> pq;
  std::vector<bool> visited(rows * columns, false);
  std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adjacency_list(rows * columns);
  std::vector<std::vector<uint64_t>> shyness(rows, std::vector<uint64_t>(columns));

  for ( std::size_t i = 0; i < rows; ++i )
  {
    for ( std::size_t j = 0; j < columns; ++j )
    {
      std::cin >> shyness[i][j];
    }
  }


  for ( std::size_t i = 0; i < rows; ++i )
  {
    for ( std::size_t j = 0; j < columns; ++j )
    {
      u_node = i * columns + j;

      // check moves
      if ( i > 0 )
      {
        CreateEdges(adjacency_list, u_node, u_node - columns, std::min(shyness[i][j], shyness[i - 1][j])); // up
      }

      if ( i < (rows - 1) )
      {
        CreateEdges(adjacency_list, u_node, u_node + columns, std::min(shyness[i][j], shyness[i + 1][j])); // down
      }

      if ( j > 0 )
      {
        CreateEdges(adjacency_list, u_node, u_node - 1, std::min(shyness[i][j], shyness[i][j - 1])); // left
      }

      if ( j < (columns - 1) )
      {
        CreateEdges(adjacency_list, u_node, u_node + 1, std::min(shyness[i][j], shyness[i][j + 1])); // right
      }
    }
  }

  // start with arbitrary node
  pq.emplace(0, 0); // (cost, node)

  while ( !pq.empty() )
  {
    pq.pop();

    top_node_cost = pq.top().first;
    top_node_number = pq.top().second;

    if ( visited[top_node_number] )
    {
      continue;
    }

    visited[top_node_number] = true;
    total_candies += top_node_cost;

    // add neighbors of current popped top to the priority queue
    for ( const std::pair<uint64_t, uint64_t>& neighbor : adjacency_list[top_node_number] )
    {
      // check node number if visited
      if ( !visited[neighbor.second] )
      {
        pq.emplace(neighbor.first, neighbor.second);
      }
    }
  }

  std::cout << total_candies;

  return 0;
}
