#include <numeric>
#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "geoStructures.hpp"
#include "Commands.hpp"

void jirkov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(jirkov::getAreaEven, _1, _2);
    area["ODD"] = std::bind(jirkov::getAreaOdd, _1, _2);
    area["MEAN"] = std::bind(jirkov::getAreaMean, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    area.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    size_t size = command.length();
    bool isDigit = true;
    for(size_t i = 0; i < size; i++)
    {
      if(!std::isdigit(command[i]))
      {
        isDigit = false;
      }
    }
    if(isDigit == true)
    {
      std::cout << std::stoll(command);
      getVertex(out);
    }
    else
    {
      std::cerr << "INVALID COMMAND" << "\n";
      is.clear();
      is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

bool jirkov::findEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool jirkov::findOdd(const Polygon& polygon)
{
  return !findEven(polygon);
}

double jirkov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), findEven);
  double area = std::accumulate(even.begin(), even.end(), 0, fullArea);
  out << area;
  return area;
}

double jirkov::getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), findOdd);
  double area = std::accumulate(odd.begin(), odd.end(), 0, fullArea);
  out << area;
  return area;
}
int jirkov::findCordinate(const Point& currentPoint,const Point& prevPoint)
{
  int currentX = currentPoint.x;
  int currentY = currentPoint.y;
  int prevX = prevPoint.x;
  int prevY = prevPoint.y;
  int area = (prevX + currentX) * (prevY - currentY);
  return area;
}

double jirkov::getAreaMean(const std::vector< Polygon >& allData, std::ostream& out)
{
  double area = std::accumulate(allData.begin(), allData.end(), 0, fullArea);
  double result = area / allData.size();
  out << result;
  return result;
}

double jirkov::countArea(const Polygon polygon)
{
  int area = 0;
  std::vector< int > areas(polygon.points.size());
  std::vector< int >::iterator startAreas = areas.begin();
  std::vector< int >::iterator finishAreas = areas.end();

  std::vector< Point >::const_iterator finish = polygon.points.end();
  std::vector< Point >::const_iterator prevPoint = polygon.points.begin();
  std::vector< Point >::const_iterator currentPoint = polygon.points.begin() + 1;

  std::transform(currentPoint, finish, prevPoint, startAreas, findCordinate);
  *(finishAreas - 1) = findCordinate(*prevPoint, *(finish - 1));

  area = std::accumulate(startAreas, finishAreas, 0);
  return std::abs(area / 2.0);
}

double jirkov::fullArea(double sum, const Polygon polygon)
{
  sum += countArea(polygon);
  return sum;
}

void jirkov::getVertex(std::ostream& out)
{
  out << "\n";
}
