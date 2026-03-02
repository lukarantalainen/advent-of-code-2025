#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace day5 {

auto pair_ranges(const std::vector<std::string>& ranges) {
  std::vector<std::pair<long long, long long>> range_pairs{};
  int hyphen{0};
  for (std::string range : ranges) {
    for (int i{0}; i < range.length(); i++) {
      if (range[i] == '-') {
        hyphen = i;
      }
    }
    long long first{std::stoll(range.substr(0, hyphen))};
    long long second{
        std::stoll(range.substr(hyphen + 1, range.length() - hyphen))};
    range_pairs.push_back(std::make_pair(first, second));
  }

  return range_pairs;
}

auto read_file(std::string filename) {
  std::fstream input(filename);
  std::string line{};
  std::vector<std::string> ranges{};
  std::vector<std::string> id_list{};

  bool limit;
  while (std::getline(input, line)) {
    if (line == "") {
      limit = true;
      continue;
    }

    if (limit == true) {
      id_list.push_back(line);
    } else {
      ranges.push_back(line);
    }
  }

  return std::make_pair(ranges, id_list);
}

const std::string FILENAME{"inputs/input05.txt"};

int part_one() {
  auto file_data = read_file(FILENAME);
  auto range_list = file_data.first;
  auto id_list = file_data.second;
  auto ranges{pair_ranges(range_list)};

  int fresh{0};
  std::set<int> fresh_ids{};
  for (auto pair : ranges) {
    auto low{pair.first};
    auto high{pair.second};

    for (auto id : id_list) {
      long long id_num{std::stoll(id)};

      if (low <= id_num && id_num <= high) {
        if (fresh_ids.count(id_num) == 0) {
          fresh++;
          fresh_ids.insert(id_num);
        }
      }
    }
  }
  return fresh;
}

int part_two() {
  auto file_data = read_file(FILENAME);
  auto range_list = file_data.first;
  auto ranges{pair_ranges(range_list)};

  long long fresh{0};
  std::set<int> fresh_ids{};
  for (auto pair : ranges) {
    long long low{pair.first};
    long long high{pair.second};
    for (int i = low; i <= high; i++) {
      if (fresh_ids.count(i) == 0) {
        fresh++;
        fresh_ids.insert(i);
      }
    }
  }
  return fresh;
}
}  // namespace day5
