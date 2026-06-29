#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <queue>

namespace day07 {
const std::string FILENAME{"inputs/input07.txt"};

struct Point {
  int x;
  int y;
};

Point operator+(Point a, Point b) { return {a.x + b.x, a.y + b.y}; }

void operator+=(Point& a, Point b) { a = a + b; }

std::ostream& operator<<(std::ostream& out, Point point) {
  out << "current.x: " << point.x << ", current.y: " << point.y << "\n";
  return out;
}

bool operator!=(Point a, Point b) { return !(a.x == b.x && a.y == b.y); }

bool operator==(Point a, Point b) { return (a.x == b.x && a.y == b.y); }

long long part_one() {
  std::ifstream input(FILENAME);
  std::string line;

  std::vector<std::string> grid;
  while (std::getline(input, line)) {
    grid.push_back(line);
  }
  input.close();

  Point point{static_cast<int>(grid[0].find('S')), 1};
  std::vector<std::vector<bool>> seen(grid.size(),
                                      std::vector<bool>(grid[0].size(), false));
  long long count{};

  std::deque<Point> nodes;
  nodes.push_back(point);
  while (nodes.size()) {
    point = nodes.front();
    nodes.pop_front();
    if (seen[point.y][point.x]) continue;
    if (point.y + 1 == grid.size()) continue;
    char c = grid[point.y][point.x];
    if (c == '^') {
      seen[point.y][point.x] = true;
      nodes.push_back({point.x - 1, point.y});
      nodes.push_back({point.x + 1, point.y});
      ++count;
    } else {
      nodes.push_back({point.x, point.y + 1});
    }
  }

  return count;
}

long long traverse(const std::vector<std::string>& grid, const Point start) {
  long long count{};

  std::queue<Point> path;
  path.push(start);

  std::vector<std::vector<bool>> visited;
  visited.resize(grid.size(), std::vector<bool>(grid[0].size()));
  assert(visited.size() == grid.size() && visited[0].size() == grid[0].size());

  Point current{start};
  while (current.y > 0) {  // do until walked back past the starting node
    while (current.y + 2 < grid.size() &&
           (!visited[current.y + 1][current.x + 1] ||
            !visited[current.y + 1][current.x - 1])) {  // walk down
      if (grid[current.y][current.x] == '^' &&
          !visited[current.y + 1][current.x - 1]) {
        current = {current.x - 1, current.y + 1};
      } else if (grid[current.y][current.x] == '^' &&
                 !visited[current.y + 1][current.x - 1]) {
        current = {current.x - 1, current.y + 1};
      } else {
        ++current.y;
      }
      path.push(current);
    }
    ++count;


    while (visited[current.y + 1][current.x + 1] &&
           visited[current.y + 1][current.x - 1] || current.y+2 == grid.size()) {  // walk up
      visited[current.y + 1][current.x + 1] = false;
      visited[current.y + 1][current.x - 1] = false;
      // backtracking so that future paths can still use these nodes
      visited[current.y][current.x] = true;
      current = path.back();
      path.pop();
    }
    if (current == start) {
      if (visited[current.y + 1][current.x + 1] &&
          visited[current.y + 1][current.x - 1]) {
        current.y = 0;
      }
    }
  }
  return count;
}

long long part_two() {
  std::ifstream input("inputs/test.txt");
  std::string line;
  std::vector<std::string> grid;

  while (std::getline(input, line)) {
    grid.push_back(line);
  }

  Point start{static_cast<int>(grid[0].find('S')), 1};

  long long count{traverse(grid, start)};
  return count;
}
}  // namespace day07

int main() {
  using namespace day07;
  std::cout << day07::part_one() << "\n";
  std::cout << part_two() << "\n";

  return 0;
}
