#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <set>
#include <utility>
#include <deque>

namespace day07 {
const std::string FILENAME{"inputs/input07.txt"};

struct Point {
    int x;
    int y;  
};

Point operator+(Point a, Point b) {
    return {a.x+b.x, a.y+b.y};
}

void operator+=(Point& a, Point b) {
    a = a+b;
}

std::ostream& operator<<(std::ostream& out, Point point) {
    out << "current.x: "<< point.x << ", current.y: " << point.y << "\n";
    return out;
}


long long part_one() {
    std::ifstream input(FILENAME);
    std::string line;

    std::vector<std::string> grid;
    while (std::getline(input, line)) {
        grid.push_back(line);
    }
    input.close();

    Point point{static_cast<int>(grid[0].find('S')), 1};
    std::vector<std::vector<bool>> seen(grid.size(), std::vector<bool>(grid[0].size(), false));
    long long count{};

    std::deque<Point> nodes;
    nodes.push_back(point);
    while (nodes.size()) {
        point = nodes.front();
        nodes.pop_front();
        if (seen[point.y][point.x]) continue;
        if (point.y+1 == grid.size()) continue;
        char c = grid[point.y][point.x];
        if (c == '^') {
            seen[point.y][point.x] = true;
            nodes.push_back({point.x-1, point.y});
            nodes.push_back({point.x+1, point.y});
            ++count;
        } else {
            grid[point.y][point.x] = '|';
            nodes.push_back({point.x, point.y+1});
        }
    }

    for (auto l : grid) std::cout << l << "\n";
    return count;
}

long long traverse(std::vector<std::string>& grid, std::vector<std::vector<bool>>& visited, Point point, long long count) {
    Point current{point};

    while (0 < current.x && current.x < grid[0].size() && 0 <= current.y && current.y < grid.size()) {
        if (grid[current.y][current.x] == '^') {
            current += {-1, 1};
            traverse(grid, visited, {point.x-1, point.y+1}, count);
            traverse(grid, visited, {point.x+1, point.y+1}, count);
        } else {
            traverse(grid, visited, {point.x, point.y+1}, count);
            current += {0, 1};
        }
    }

    std::cout << current;
    grid[current.y][current.x] = 'O';
    visited[current.y][current.x] = true;
    
    return count;
}

long long part_two() {
    std::ifstream input("inputs/test.txt");
    std::string line;
    std::vector<std::string> grid;
    
    while (std::getline(input, line)) {
        grid.push_back(line);
    }
    Point start{static_cast<int>(grid[0].find('S')), 0};
    std::vector<std::vector<bool>> visited;
    visited.resize(grid.size(), std::vector<bool>(grid[0].size()));
    for (auto v : visited) v.resize(grid[0].size());
    long long count = traverse(grid, visited, start, 0);

    for (auto l : grid) {
        for (auto c : l) {
            std::cout << c;
        }
        std::cout << "\n";
    }

    return count;
}
}

int main()  {
    using namespace day07;
    std::cout << day07::part_one() << "\n"; 
    //std::cout << part_two() << "\n";

    return 0;
}
    