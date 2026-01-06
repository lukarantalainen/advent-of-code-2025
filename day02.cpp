#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define ll long long

bool check_repeating(ll num);

std::vector<std::string> parse_string(std::string f) {
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
    std::vector<std::string> input) {
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

ll part_one(std::vector<std::pair<std::string, std::string>> input) {
  ll total{0};
  for (auto p : input) {
    auto first = std::stoll(p.first);
    auto second = std::stoll(p.second);
    for (ll i = first; i <= second; i++) {
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

bool check_repeating(ll num) {
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

auto part_two(std::vector<std::pair<std::string, std::string>> input) {
  ll total{0};
  for (auto p : input) {
    ll first{std::stoll(p.first)};
    ll second{std::stoll(p.second)};
    for (ll i = first; i <= second; i++) {
      if (check_repeating(i) == true) {
        total += i;
      }
    }
  }
  return total;
}

int main() {
  auto data = pair_values(parse_string("inputs/input02.txt"));
  std::cout << part_one(data) << "\n";
  std::cout << part_two(data) << "\n";

  return 0;
}
