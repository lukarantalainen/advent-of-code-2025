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

long long part_two() {
  int length{};

  std::fstream input(FILENAME);
  std::string line{};
  const int bank_length{12};
  long long ans{};

  while (std::getline(input, line)) {
    std::vector<int> new_bank(bank_length);

    int start{0};
    for (int i{0}; i<bank_length; ++i) {
      int largest{0};
      for (int j{start}; j<line.length(); ++j) {
        int num{line[j]-'0'};
        bool space{bank_length-i<=line.length()-j};
        if (num>largest && space) {
          largest = num;
          start = j+1;
        }
      }
      new_bank[i] = largest;
    }

    long long sum{};
    for (auto i : new_bank) {
      sum*=10;
      sum+=i;
    }
    ans+=sum;
  }
  return ans;
}
}  // namespace day3
