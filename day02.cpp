#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool check_repeating(long long num);

std::vector<std::string> parse_string(const std::string& f) {
  std::fstream input(f);
  std::string line;
  std::getline(input, line);
  std::vector<std::string> ranges;

  int prev_delim{0};
  int length{0};
  int char_index{0};
  std::string range;

  for (int i = 0; i <= line.length(); i++) {
    char_index++;
    if (line[i] == ',' || i == line.length()) {
      range = line.substr(prev_delim, length);
      ranges.push_back(range);
      prev_delim = char_index;
      length = 0;
    } else {
      length++;
    }
  }
  return ranges;
}

std::vector<std::pair<std::string, std::string>> pair_values(
    const std::vector<std::string>& input) {
  std::vector<std::pair<std::string, std::string>> range_pairs;
  for (std::string s : input) {
    int char_index{0};
    for (char c : s) {
      char_index++;
      if (c == '-') {
        std::string first{s.substr(0, char_index)};
        std::string last{s.substr(char_index)};
        range_pairs.push_back(std::make_pair(first, last));
      }
    }
  }
  return range_pairs;
}

bool check_repeating(long long num) {
  std::string id = std::to_string(num);
  bool repeating = false;
  const int id_len = id.length();

  for (int i = 1; i <= id_len / 2; i++) {
    if (id_len % i != 0) continue;
    std::string pattern = id.substr(0, i);
    std::string counterpart{};
    for (int j = 0; j < id_len / i; j++) {
      counterpart.append(pattern);
    }
    if (id == counterpart) {
      return true;
    }
  }
  return repeating;
}

namespace day2 {
const std::string FILENAME{"inputs/input02.txt"};
long long part_one() {
  auto input = pair_values(parse_string(FILENAME));
  long long total{0};
  for (auto p : input) {
    auto first = std::stoll(p.first);
    auto second = std::stoll(p.second);
    for (long long i = first; i <= second; i++) {
      auto id = std::to_string(i);
      if (id.length() % 2 == 0) {
        auto first_half = id.substr(0, id.length() / 2);
        auto second_half = id.substr(id.length() / 2, id.length() / 2);

        if (first_half == second_half) {
          total += i;
        }
      } else {
        continue;
      }
    }
  }
  return total;
}

long long part_two() {
  auto input = pair_values(parse_string(FILENAME));
  long long total{0};
  for (auto p : input) {
    long long first{std::stoll(p.first)};
    long long second{std::stoll(p.second)};
    for (long long i = first; i <= second; i++) {
      if (check_repeating(i) == true) {
        total += i;
      }
    }
  }
  return total;
}
}  // namespace day2
