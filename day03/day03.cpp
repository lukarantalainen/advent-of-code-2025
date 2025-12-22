#include <fstream>
#include <iostream>
#include <string>

void count_joltage(std::string f) {
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

      else if (second_highest < c) {
        second_highest = c;
      }

      list_index++;
    }

    std::string jolt_str =
        std::to_string(highest -= '0') + std::to_string(second_highest -= '0');

    joltage += std::stoi(jolt_str);
  }

  std::cout << joltage;
}

int main() {
  count_joltage("inputs\\input03.txt");
  return 0;
}
