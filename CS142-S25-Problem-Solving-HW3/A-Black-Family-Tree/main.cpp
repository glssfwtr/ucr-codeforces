#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

uint64_t CountComponentSizeBFS(uint64_t start_node, const std::vector<std::vector<uint64_t>>& adjacency_list, std::vector<bool>& visited, const std::unordered_set<uint64_t>& traitors_set)
{
  std::queue<uint64_t> bfs_queue;
  uint64_t component_size = 0;

  bfs_queue.push(start_node);

  visited[start_node] = true;

  while ( !bfs_queue.empty() )
  {
    uint64_t current_node = bfs_queue.front();
    bfs_queue.pop();

    ++component_size;

    // explore adjacent nodes
    for ( uint64_t connected_vertex : adjacency_list[current_node] )
    {
      if ( traitors_set.count(connected_vertex) || visited[connected_vertex] ) // if traitor or already visited, skip
      {
        continue;
      }

      visited[connected_vertex] = true;

      bfs_queue.push(connected_vertex);
    }
  }

  return component_size;
}

uint64_t CountComponentSizeDFS(uint64_t node_num, const std::vector<std::vector<uint64_t>>& adjacency_list, std::vector<bool>& visited, const std::unordered_set<uint64_t>& traitors_set)
{
  visited[node_num] = true;

  uint64_t component_size = 1; // root itself count

  for ( uint64_t connected_vertex : adjacency_list[node_num] )
  {
    if ( traitors_set.count(connected_vertex) || visited[connected_vertex] ) // if traitor or already visited, skip
    {
      continue;
    }

    // DFS recursive stack call explore
    component_size += CountComponentSizeDFS(connected_vertex, adjacency_list, visited, traitors_set);
  }

  return component_size;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t current_max_component_size = 0;
  uint64_t found_component_size;
  uint64_t num_people;
  uint64_t num_traitors;
  uint64_t traitor;

  std::cin >> num_people;
  std::cin >> num_traitors;

  std::unordered_set<uint64_t> traitors_set;
  std::vector<bool> visited(num_people, false);
  std::vector<uint64_t> parents(num_people - 1);
  std::vector<std::vector<uint64_t>> adjacency_list(num_people);

  for ( std::size_t i = 0; i < num_people - 1; ++i )
  {
    std::cin >> parents[i];
  }

  for ( std::size_t i = 0; i < num_traitors; ++i )
  {
    std::cin >> traitor;

    traitors_set.insert(traitor);
  }

  // build adjacency list (undirected)
  for ( uint64_t i = 1; i < num_people; ++i )
  {
    uint64_t parent = parents[i - 1];

    adjacency_list[i].push_back(parent);
    adjacency_list[parent].push_back(i);
  }














  // find all connected components
  for (uint64_t i = 0; i < num_people; ++i)
  {
    if (traitors_set.count(i) || visited[i])
    {
      continue;
    }

    found_component_size = CountComponentSizeBFS(i, adjacency_list, visited, traitors_set);

    current_max_component_size = std::max(current_max_component_size, found_component_size);
  }

  std::cout << current_max_component_size;

  return 0;
}
