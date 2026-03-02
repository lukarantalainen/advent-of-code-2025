#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long long vector_to_long(std::vector<int> input) {
  long long result{0};

  for (int n : input) {
    result = (result + n) * 10;
  }
  return result / 10;
}

namespace day3 {
const std::string FILENAME{"inputs/input03.txt"};
int part_one() {
  std::fstream input(FILENAME);
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

int part_two() {
  std::fstream input(FILENAME);
  std::string line;
  int bank_length{12};
  long long joltage{0};

  while (std::getline(input, line)) {
    std::vector<int> bank{};

    for (auto i{line.length() - 1}; i > 0; i--) {
      int num{line[i] - '0'};
      int lowest{line[line.length() - 1]};
      if (line[i] >= lowest) {
        bank.push_back(line[i]);
      } else if (line[i] < lowest) {
        lowest = line[i];
      }
    }

    std::vector<int> final_bank(bank.end() - bank_length, bank.end());

    std::cout << vector_to_long(final_bank) << "\n";
    joltage += vector_to_long(final_bank);

    // for (int n : bank) {
    //   std::cout << n;
    // }
  }
  return 0;
}
}  // namespace day3
