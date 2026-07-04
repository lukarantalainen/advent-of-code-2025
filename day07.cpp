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
using namespace std;
const string FILENAME{"inputs/input07.txt"};

struct Point {
  int x;
  int y;
};

Point operator+(Point a, Point b) { return {a.x + b.x, a.y + b.y}; }

void operator+=(Point& a, Point b) { a = a + b; }

ostream& operator<<(ostream& out, Point point) {
  out << "current.x: " << point.x << ", current.y: " << point.y << "\n";
  return out;
}

bool operator!=(Point a, Point b) { return !(a.x == b.x && a.y == b.y); }

bool operator==(Point a, Point b) { return (a.x == b.x && a.y == b.y); }

long long part_one() {
  ifstream input(FILENAME);
  string line;

  vector<string> grid;
  while (getline(input, line)) {
    grid.push_back(line);
  }
  input.close();

  Point point{static_cast<int>(grid[0].find('S')), 1};
  vector<vector<bool>> seen(grid.size(),
                                      vector<bool>(grid[0].size(), false));
  long long count{};

  deque<Point> nodes;
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
  ifstream input("inputs/input07.txt");
  string line;
  vector<string> grid;

  while (getline(input, line)) {
    grid.push_back(line);
  }

  Point start{static_cast<int>(grid[0].find('S')), 1};

  auto grid_copy{grid};

  string previous = grid[0];
  vector<long long> sum(grid[0].size());
  sum[grid[0].find('S')] = 1;
  for (int i = 1; i < grid.size(); ++i) {
    auto sum_copy{sum};
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] == '^' && sum[j]) {
        if (j > 0) sum_copy[j-1] += sum[j];
        if (j < grid[0].size()) sum_copy[j+1] += sum[j];
          sum_copy[j] = 0;
          grid_copy[i][j-1] = '|';
          grid_copy[i][j+1] = '|';
      } else if (sum[j]) {
        grid_copy[i][j] = '|';
      }
    }
    sum = sum_copy;
  }

  long long count{accumulate(sum.begin(), sum.end(), 0LL)};
  
  return count;
}
}  // namespace day07

int main() {
  using namespace day07;
  cout << day07::part_one() << "\n";
  cout << part_two() << "\n";

  return 0;
}
