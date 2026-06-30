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
#include <numeric>
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

long long part_two() {
  using namespace std;
  std::ifstream input("inputs/test.txt");
  std::string line;
  std::vector<std::string> grid;

  while (std::getline(input, line)) {
    grid.push_back(line);
  }

  Point start{static_cast<int>(grid[0].find('S')), 1};

  auto grid_copy{grid};

  string previous = grid[0];
  std::vector<int> sum(grid[0].size());
  sum[grid[0].find('S')] = 1;
  for (int i = 1; i < grid.size(); ++i) {
    for (int j = 1; j < grid[0].size()-1; ++j) {
      if (grid[i][j] == '^') {
        if (sum[j]) {
          sum[j-1] += sum[j];
          sum[j+1] += sum[j];
          sum[j] = 0;
        }
        grid_copy[i][j-1] = '|';
        grid_copy[i][j+1] = '|';
      }
      
    }
    for (auto l : grid_copy) {
      std::cout << l << "\n";
    }
  }


  
  long long count = accumulate(sum.begin(), sum.end(), 0);
  return count;
}
}  // namespace day07

int main() {
  using namespace day07;
  std::cout << day07::part_one() << "\n";
  std::cout << part_two() << "\n";

  return 0;
}
