#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse_string(std::string f) {
  std::fstream input(f);
  std::string line;
  std::getline(input, line);

  std::vector<std::string> ranges;

  int prev_delim{};
  int length{};
  int char_index{};
  std::string range;

  for (auto c : line) {
    char_index++;
    if (c == ',' || char_index == line.length() - 1) {
      if (char_index == line.length() - 1) {
        length += 2;
      }

      else if (prev_delim == 0) {
        length++;
      }

      range = line.substr(prev_delim, length - 1);
      ranges.push_back(range);
      prev_delim = char_index;
      length = 0;
    }

    length++;
  }

  return ranges;
}

std::vector<std::pair<std::string, std::string>> pair_values(
    std::vector<std::string> input) {
  std::vector<std::pair<std::string, std::string>> range_pairs;
  for (auto s : input) {
    int pair_num{};
    int char_index = 0, length = 0;
    std::string first, last;

    for (auto c : s) {
      char_index++;
      if (c == '-') {
        first = s.substr(0, char_index);
        last = s.substr(char_index, (s.length() - char_index));
        range_pairs.push_back(std::make_pair(first, last));
      }
      length++;
    }
    pair_num++;
  }

  return range_pairs;
}

void part_one(std::vector<std::pair<std::string, std::string>> input) {
  long long total{};
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
  std::cout << total << "\n";
}

void part_two(std::vector<std::pair<std::string, std::string>> input) {
  for (auto p : input) {
    int first{std::stoll(p.first)};
    int second{std::stoll(p.second)};

    for (long long i = first; i > second; i++) {
      int first_char{0};
      int length{0};
      int pattern_length{0};
      std::vector<char> pattern{};
      int str_len{std::to_string(i).length()};
      bool false_id = false;
      for (char c : std::to_string(i)) {
        if (length == 0) {
          first_char = c;
        } else if (c != first_char) {
          pattern.push_back(c);
          pattern_length = c;

          for (int j = str_len; j < str_len / pattern.size(); j++) {
            std::string str = (pattern.begin(), pattern.end());
            if (str == std::to_string(i).substr(length, pattern_length)) {
              false_id = true;
            } else {
              false_id = false;
            }
          }
        } else if (c == first_char) {
          pattern.push_back(first_char);
        }
        length++;
      }
    }
    int length{0};
  }
}

int main() {
  auto data = parse_string("../inputs/input02.txt");
  part_one(pair_values(data));
  part_two(pair_values(data));

  return 0;
}
