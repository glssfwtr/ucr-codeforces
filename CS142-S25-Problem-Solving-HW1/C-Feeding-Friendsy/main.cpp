#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  // current time, 0/1 = start/end of interval, point status
  // order of pair interval status and point status matters because of std::sort()
  // first sort by time, then sort by interval status (open -> close)
  std::vector<std::pair<int, std::pair<bool, int>>> chomp_interval_events;

  int T; // total duration
  int n; // upper mouth interval
  int m; // lower mouth interval

  int a;
  int b;
  bool c; // 0 = normal, 1 = rainbow
  int points;

  int max_points = 0;
  int previous_time = 0;

  int current_event_time;
  int current_event_mouth_status;
  int current_event_points;

  std::multiset<int, std::greater<int>> available_points;


  std::cin >> T;
  std::cin >> n;
  std::cin >> m;

  // n lines tuple on a, b, c
  for ( int i = 0; i < n; ++i )
  {
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    points = (c == 1) ? 3 : 1;

    chomp_interval_events.emplace_back(std::make_pair(a, std::make_pair(0, points)));
    chomp_interval_events.emplace_back(std::make_pair(b + 1, std::make_pair(1, points))); // b + 1 inclusive
  }

  // m lines tuple on a, b, c
  for ( int i = 0; i < m; ++i )
  {
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    points = (c == 1) ? 3 : 1;

    chomp_interval_events.emplace_back(std::make_pair(a, std::make_pair(0, points)));
    chomp_interval_events.emplace_back(std::make_pair(b + 1, std::make_pair(1, points)));
  }

  // we don't care about "which and when" it happens, we just care about "when" for any Cheep Chomp
  // sort with <, by time, then interval status (open -> close)
  std::sort(chomp_interval_events.begin(), chomp_interval_events.end());


  for ( const auto& event : chomp_interval_events )
  {
    current_event_time = event.first;
    current_event_mouth_status = event.second.first;
    current_event_points = event.second.second;

    // sweep line algorithm on time interval
    if ( !available_points.empty() && previous_time < current_event_time )
    {
      //          possible point at this unit Time * time difference
      max_points += *available_points.begin() * (current_event_time - previous_time);
    }

    // decide if removing or inserting current event points from chomp's status
    if ( current_event_mouth_status == 0 )
    {
      available_points.insert(current_event_points); // mouth opening state
    }
    else
    {
      // need to find and erase because there can be chomp overlapping intervals with different point status (1 : 3)
      available_points.erase(available_points.find(current_event_points)); // mouth closing, find the point and remove from set
    }

    previous_time = current_event_time;
  }


  std::cout << max_points;

  return 0;
}
