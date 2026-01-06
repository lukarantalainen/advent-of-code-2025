#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define ll long long

auto pair_ranges(std::vector<std::string> ranges) {
  std::vector<std::pair<ll, ll>> range_pairs{};
  int hyphen{0};
  for (std::string range : ranges) {
    for (int i{0}; i < range.length(); i++) {
      if (range[i] == '-') {
        hyphen = i;
      }
    }
    ll first{std::stoll(range.substr(0, hyphen))};
    ll second{std::stoll(range.substr(hyphen + 1, range.length() - hyphen))};
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

int part_one(std::vector<std::pair<ll, ll>> ranges,
             std::vector<std::string> id_list) {
  int fresh{0};
  std::set<int> fresh_ids{};
  for (auto pair : ranges) {
    auto low{pair.first};
    auto high{pair.second};

    for (auto id : id_list) {
      ll id_num{std::stoll(id)};

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

int part_two(std::vector<std::pair<ll, ll>> ranges) {
  long long fresh{0};
  std::set<int> fresh_ids{};
  for (auto pair : ranges) {
    ll low{pair.first};
    ll high{pair.second};
    for (int i = low; i <= high; i++) {
      if (fresh_ids.count(i) == 0) {
        fresh++;
        fresh_ids.insert(i);
      }
    }
  }
  return fresh;
}

int main() {
  auto file_data = read_file("inputs/input05.txt");
  auto range_list = file_data.first;
  auto id_list = file_data.second;

  auto range_pairs = pair_ranges(range_list);

  std::cout << part_one(range_pairs, id_list) << "\n";
  std::cout << part_two(range_pairs);

  return 0;
}
