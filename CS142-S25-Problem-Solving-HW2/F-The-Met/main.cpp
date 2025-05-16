#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// find farthest node from given start node using BFS
std::pair<uint64_t, uint64_t> BreadthFirstSearch(uint64_t start, const std::vector<std::vector<uint64_t>>& graph)
{
  uint64_t current_farthest_node = start;
  uint64_t num_nodes = graph.size();
  std::queue<uint64_t> traversal_queue; // from start node to any existing node
  std::vector<uint64_t> traversal_distance(num_nodes, std::numeric_limits<uint64_t>::max()); // indexing node number

  traversal_queue.push(start);
  traversal_distance[start] = 0;

  while ( !traversal_queue.empty() )
  {
    uint64_t current = traversal_queue.front();

    // explore neighbors
    for ( uint64_t i = 0; i < graph[current].size(); ++i )
    {
      uint64_t neighbor = graph[current][i];

      if ( traversal_distance[neighbor] == std::numeric_limits<uint64_t>::max() )
      {
        // unvisited node
        traversal_distance[neighbor] = traversal_distance[current] + 1;


        if (traversal_distance[neighbor] > traversal_distance[current_farthest_node])
        {
          current_farthest_node = neighbor;
        }

        traversal_queue.push(neighbor);
      }
    }

    traversal_queue.pop();
  }

  return {current_farthest_node, traversal_distance[current_farthest_node]};
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t num_nodes;
  uint64_t u;
  uint64_t v;

  std::cin >> num_nodes;

  // adjacency list representing graph
  std::vector<std::vector<uint64_t>> adjacency_list_graph(num_nodes);

  for ( uint64_t i = 0; i < num_nodes - 1; ++i )
  {
    std::cin >> u;
    std::cin >> v;

    // 0 based index since problem statement uses 1 based
    --u;
    --v;

    // connect u and v
    adjacency_list_graph[u].push_back(v);
    adjacency_list_graph[v].push_back(u);
  }









  // 1. find farthest node from some arbitrary node
  // 2. find farthest node from farthest of arbitrary to compute diameter
  uint64_t tree_diameter = BreadthFirstSearch(BreadthFirstSearch(0, adjacency_list_graph).first, adjacency_list_graph).second; // distance to other end of diameter

  // radius is half the diameter, need to round up for odd diameter
  uint64_t radius = (tree_diameter + 1) / 2;

  std::cout << radius;

  return 0;
}
