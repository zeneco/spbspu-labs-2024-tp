#include "checkFuncs.hpp"
#include <algorithm>
#include <functional>
#include <numeric>

double psarev::getArea(Polygon& poly)
{
  std::vector< int > interValues(poly.points.size());
  using namespace std::placeholders;

  std::transform(++(poly.points.begin()), poly.points.end(), poly.points.begin(), interValues.begin(), std::bind(getInterValue, _1, _2));
  int area = std::accumulate(interValues.begin(), interValues.end(), 0);
  return abs(area) / 2.0;
}

int psarev::getInterValue(Point& ptOne, Point& ptTwo)
{
  return ptOne.x * ptTwo.y - ptOne.y * ptTwo.x;
}

double psarev::plusArea(Polygon& poly, double summed)
{
  return res + countArea(shape);
}