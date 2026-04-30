#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

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

bool comparison(std::pair<long long, long long> p1, std::pair<long long, long long> p2) {
  return p1.first<p2.first;
}

long long part_two() {
  std::ifstream input(FILENAME);
  std::string line{};

  std::vector<std::pair<long long, long long>> list{};

  while (std::getline(input, line)) {
    if (line=="") break;

    auto pos {line.find('-')};
    auto first{std::stoll(line.substr(0, pos))};
    auto second{std::stoll(line.substr(pos+1))};
    
    list.push_back({first, second});
  }
  std::sort(list.begin(), list.end(), comparison);

  std::vector<std::pair<long long, long long>> ranges{};
  for (const auto& raw : list) {
    bool mod{};
    for (auto& range : ranges) {
      if (raw.first>=range.first && raw.second<=range.second) {
        mod = true;
        break;
      } else if (raw.first<range.first && raw.second>=range.first && raw.second<=range.second) {
        range.first = raw.first;
        mod = true;
      } else if (raw.second>range.second && raw.first>=range.first && raw.first<=range.second) {
        range.second = raw.second;
        mod = true;
      }
    }
    
    if (!mod) {
      ranges.push_back({raw.first, raw.second}); 
    }
  }

  long long fresh{};
  for (auto p : ranges) {
    fresh+=p.second-p.first+1;
    std::cout << p.first << "-" << p.second << "\n";
  }
  
  return fresh;
}
}  // namespace day5

int main() {
  std::cout << day5::part_one() << "\n";
  std::cout << day5::part_two() << "\n";
  return 0;
}
