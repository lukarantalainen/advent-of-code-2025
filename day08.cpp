#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

namespace day08 {
const std::string FILENAME{"inputs/test.txt"};

struct Coord {
    int x;
    int y;
    int z;

    Coord() : x{}, y{}, z{} {}
    Coord(std::vector<int> nums) : x{nums[0]}, y{nums[1]}, z{nums[2]} {}
};

int distance(Coord p1, Coord p2) {
    return std::sqrt(std::pow(p1.x-p2.x, 2)+std::pow(p1.y-p2.y, 2)+std::pow(p1.z-p2.z, 2));
}

long long part_one() {
    std::ifstream input(FILENAME);

    std::string line;
    std::vector<Coord> coords;
    while (std::getline(input, line)) {
        std::vector<int> nums;
        int start{};
        auto pos{line.find(',')};
        for (int i{0}; i<3; ++i) {
            nums.push_back(std::stoi(line.substr(start, pos)));
            start = pos+1;
            pos = line.find_last_of(',');
        }
        coords.push_back(Coord{nums});
    }
    
    for (int i{0}; i<coords.size(); ++i) {
      int shortest{};
      Coord best;
      for (auto c : coords) {
        int d{distance(coords[i], c)};
        if (d < shortest) {
          shortest = d;
          best = c;
        }
        }

    }
    return 0;
}
}

int main() {
    day08::part_one();

    return 0;
}
