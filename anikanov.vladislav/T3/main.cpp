#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include <numeric>
#include <iofmtguard.hpp>

#include "polygon.hpp"
#include "mainExtensions.hpp"

int main(int argc, char **argv)
{
  using namespace anikanov;

  if (argc < 2 || argc > 2) {
    return 1;
  }

  std::string filename = argv[1];
  std::vector< Polygon > polygons;

  try {
    polygons = readPolygons(filename);
  }
  catch (const std::exception &e) {
    std::cerr << "Error reading file: " << e.what() << "\n";
    return 2;
  }

  std::string cmd;
  while (std::cin >> cmd) {
    try {
      if (cmd == "AREA") {
        std::cout << std::fixed << std::setprecision(1) << area(polygons, std::cin) << '\n';
      } else if (cmd == "MAX") {
        std::cout << std::fixed << std::setprecision(1) << max(polygons, std::cin, std::cout) << '\n';
      } else if (cmd == "MIN") {
        std::cout << std::fixed << std::setprecision(1) << min(polygons, std::cin, std::cout) << '\n';
      } else if (cmd == "COUNT") {
        std::cout << count(polygons, std::cin) << "\n";
      } else if (cmd == "RECTS") {
      } else if (cmd == "RIGHTSHAPES") {
      }
    } catch (const std::runtime_error &er) {
      iofmtguard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1);

      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    cmd.clear();
  }

  return 0;
}
