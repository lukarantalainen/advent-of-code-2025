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

void count_invalid_ids(std::vector<std::pair<std::string, std::string>> input) {
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

int main() {
  auto data = parse_string("inputs\\input02.txt");
  auto pairs = pair_values(data);
  count_invalid_ids(pairs);

  return 0;
}
