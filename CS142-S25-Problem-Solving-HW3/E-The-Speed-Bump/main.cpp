#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>


// edge properties destination, bump count, and distance
// u to v with #bumps and #distance
struct Edge
{
  uint64_t v;
  uint64_t num_bumps;
  uint64_t distance;
};


struct CurrentNodeProcessed
{
  uint64_t num_bumps_required; // total bumps to reach node
  uint64_t distance_required; // total distance to reach node
  uint64_t u; // v node index

  // comparison op for min-heap by lexicographic order of bumps > distance
  bool operator<(CurrentNodeProcessed const& o) const
  {
    if ( num_bumps_required != o.num_bumps_required )
    {
      return num_bumps_required > o.num_bumps_required; // fewer bumps = higher priority
    }

    return ( distance_required > o.distance_required ); // then shorter distance
  }
};

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t best_bumps;
  uint64_t best_distance;

  uint64_t num_nodes;
  uint64_t num_edges;

  std::cin >> num_nodes;
  std::cin >> num_edges;



  // build adj list
  std::vector<std::vector<Edge>> adj_list(num_nodes);

  for ( std::size_t i = 0; i < num_edges; ++i )
  {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    adj_list[a].push_back({b, c, d}); // a connect to b with c bumps and d distance
    adj_list[b].push_back({a, c, d}); // b connect to a with c bumps and d distance
  }








  /*
    dijkstra's algorithm
  */
  // best[v] holds best (num_bumps, distance) to reach v from 0
  std::vector<std::pair<uint64_t, uint64_t>> best_route_to(num_nodes, {1e9, 1e9});
  best_route_to[0] = {0, 0}; // best[0] from 0 is 0,0

  // minheap of processing current node
  std::priority_queue<CurrentNodeProcessed> pq;
  pq.push({0, 0, 0}); // starting at node 0 with (0 bumps, 0 distance)


  while ( !pq.empty() )
  {
    uint64_t current_bumps = pq.top().num_bumps_required;
    uint64_t current_distance = pq.top().distance_required;
    uint64_t u_node = pq.top().u;

    pq.pop();

    // skip if lexicographically worse entry
    if ( std::make_pair(current_bumps, current_distance) > best_route_to[u_node] )
    {
      continue;
    }



    // process neighboring edges
    for ( auto& [v_node, edge_num_bumps, edge_distance] : adj_list[u_node] )
    {
      // if new bumps and distance are lexicographically better for v
      // relax edges
      if ( std::make_pair(current_bumps + edge_num_bumps, current_distance + edge_distance) < best_route_to[v_node] )
      {
        best_route_to[v_node] = {current_bumps + edge_num_bumps, current_distance + edge_distance};

        pq.push({current_bumps + edge_num_bumps, current_distance + edge_distance, v_node});
      }
    }
  }

  best_bumps = best_route_to[num_nodes - 1].first;
  best_distance = best_route_to[num_nodes - 1].second;

  std::cout << best_bumps << " " << best_distance;

  return 0;
}
