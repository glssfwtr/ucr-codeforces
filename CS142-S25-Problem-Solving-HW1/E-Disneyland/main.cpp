#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point
{
  int x;
  int y;
};

// find the orientation of ordered triplet (p, q, r) by turning direction
// -1 -> clockwise    0 -> collinear    1 -> counterclockwise
int GetOrientation(const Point& p, const Point& q, const Point& r)
{
  // get cross product pq qr
  int cross_product = ((q.y - p.y) * (r.x - q.x)) -
                      ((q.x - p.x) * (r.y - q.y));

  if ( cross_product == 0 )
  {
    return 0;
  }

  return (cross_product > 0) ? -1 : 1;
}

int DistanceSquared(const Point& p1, const Point& p2)
{
  return ( ((p1.x - p2.x) * (p1.x - p2.x)) +
            ((p1.y - p2.y) * (p1.y - p2.y)) );
}


bool CompareOrientation(const Point& p1, const Point& p2, const Point& pivot)
{
  int orientation = GetOrientation(pivot, p1, p2);

  // collinear from pivot to collinear case points
  if ( orientation == 0 )
  {
    return DistanceSquared(pivot, p1) < DistanceSquared(pivot, p2);
  }

  return orientation == 1;
}


// use shoelace formula to calculate polygon area by vertex
double CalculateConvexArea(const std::vector<Point>& hull)
{
  double area = 0.0;
  std::size_t n = hull.size();

  for ( std::size_t i = 0; i < n; ++i )
  {
    // next vertex wrapping around vertex 0
    std::size_t j = (i + 1) % n;

    // edge contribution of area
    area += hull[i].x * hull[j].y - hull[i].y * hull[j].x;
  }

  return ( std::abs(area) / 2.0 );
}


// Graham's Scan algorithm
std::vector<Point> GrahamsScan(std::vector<Point>& points)
{
  // step 1: find lowest y pivot, then x if tied
  std::size_t n = points.size();
  Point pivot = points[0]; // init pivot
  std::size_t pivot_index = 0;

  // find lowest y, if y tied check x
  for ( std::size_t i = 1; i < n; ++i )
  {
    if ( (points[i].y < pivot.y) ||
          ((points[i].y == pivot.y) && (points[i].x < pivot.x)) )
    {
      pivot = points[i];
      pivot_index = i;
    }
  }

  // put pivot at 0 for reference
  std::swap(points[0], points[pivot_index]);








  // step 2: sort points based on polar angle RELATIVE to pivot found previously
  // compare points by oritentation
  sort(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2)
  {
    return CompareOrientation(p1, p2, pivot);
  });










  // step 3: build hull using stack
  std::vector<Point> hull;

  hull.push_back(points[0]);
  hull.push_back(points[1]);

  for ( std::size_t i = 2; i < n; ++i )
  {

    // check orientation of 2 points on stack
    // as lojng ass not cc pop from stack
    // anything else push to stack
    while ( (hull.size() > 1) &&
            (GetOrientation(hull[hull.size() - 2], hull.back(), points[i]) !=
            1) )
    {
      hull.pop_back();
    }

    hull.push_back(points[i]);
  }

  return hull;
}


int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::vector<Point> points(4);
  std::vector<Point> convex_hull_points;
  double convex_area;

  for ( std::size_t i = 0; i < 4; ++i )
  {
    std::cin >> points[i].x >> points[i].y;
  }




  convex_hull_points = GrahamsScan(points);




  // check collinear
  // example output is 6 places
  if ( convex_hull_points.size() < 3 )
  {
    std::cout << std::fixed << std::setprecision(6) << 0.0 << "\n";
  }
  else
  {
    convex_area = CalculateConvexArea(convex_hull_points);

    std::cout << std::fixed << std::setprecision(6) << convex_area << "\n";
  }

  return 0;
}
