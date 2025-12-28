#include <fstream>
#include <iostream>
#include <string>

int part_one(std::string f) {
  std::fstream input(f);
  std::string line;
  int joltage{0};
  while (std::getline(input, line)) {
    int highest{};
    int second_highest{};
    int list_index{};

    for (auto c : line) {
      if (c > highest && list_index < line.length() - 1) {
        highest = c;
        second_highest = 0;
      }

      else if (c > second_highest) {
        second_highest = c;
      }
      list_index++;
    }
    std::string jolt_str =
        std::to_string(highest -= '0') + std::to_string(second_highest -= '0');

    joltage += std::stoi(jolt_str);
  }

  return joltage;
}

int part_two(std::string f) {
  std::fstream input(f);
  std::string line;
  long long joltage{0};
  while (std::getline(input, line)) {
    continue;
  }
  return 0;
}

int main() {
  std::string input{"../inputs/inpu03.txt"};
  std::cout << part_one(input) << "\n";

  return 0;
}
