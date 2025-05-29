#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Edge
{
  uint64_t to;
  uint64_t weight;
};

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t grid_size;
  uint64_t stun_timer;

  std::cin >> grid_size;
  std::cin >> stun_timer;

  uint64_t total_nodes = grid_size * grid_size;
  std::vector<std::string> grid(grid_size);
  std::vector<std::vector<Edge>> adj_list(total_nodes);

  for ( std::size_t i = 0; i < grid_size; ++i )
  {
    std::cin >> grid[i];
  }




  if ( grid_size == 1 )
  {
    std::cout << 0;

    return 0;
  }


  /*
    generate adjacency list
  */

  // convert (i, j) cell to linear number
  auto CellToNodeNumber = [&](int i, int j)
  {
    return i * grid_size + j;
  };


  // 4 dir
  int64_t dir_i[4] = {1, -1, 0, 0};
  int64_t dir_j[4] = {0, 0, 1, -1};


  // check and validate adjacent cells then add to adj list
  for ( std::size_t i = 0; i < grid_size; ++i )
  {
    for ( std::size_t j = 0; j < grid_size; ++j )
    {
      uint64_t u_node = CellToNodeNumber(i, j);

      for ( std::size_t k = 0; k < 4; k++ )
      {
        int new_i = i + dir_i[k];
        int new_j = j + dir_j[k];

        if ( new_i >= 0 && new_i < grid_size && new_j >= 0 && new_j < grid_size )
        {
          uint64_t v_node = CellToNodeNumber(new_i, new_j);

          uint64_t weight = 1 + (grid[new_i][new_j] == 'b' ? stun_timer : 0);

          adj_list[u_node].push_back({v_node, weight});
        }
      }
    }
  }






  /*
    dijkstra's algorithm
  */
  std::vector<uint64_t> shortest_distance_to(total_nodes, 1e9);
  shortest_distance_to[0] = 0; // start top left (0, 0)

  //                            (distance, node_index), <underlying lying container>
  std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<>> pq;
  pq.push({0, 0}); // {distance, node}

  while ( !pq.empty() )
  {
    uint64_t distance = pq.top().first;
    uint64_t u_node = pq.top().second;

    pq.pop();

    // skip worse distance entry
    if ( distance > shortest_distance_to[u_node] )
    {
      continue;
    }



    // process all neighbors
    for (auto [v_node, weight] : adj_list[u_node])
    {
      // relax edges
      if (shortest_distance_to[u_node] + weight < shortest_distance_to[v_node])
      {
        shortest_distance_to[v_node] = shortest_distance_to[u_node] + weight;

        pq.push({shortest_distance_to[v_node], v_node});
      }
    }
  }


  // arrive bottom right
  std::cout << shortest_distance_to[total_nodes - 1];

  return 0;
}
