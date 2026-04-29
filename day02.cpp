#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, std::string>> parse_string(const std::string& f) {
  std::fstream input(f);
  std::string line;
  std::getline(input, line);
  std::vector<std::pair<std::string, std::string>> ranges;

  int length{0};

  std::pair<std::string, std::string> pair{};
  for (int i = 0; i < line.length(); ++i) {
    if (line[i] == '-') {
      pair.first = line.substr(i-length, length);
      length = 0;
    } else if (line[i] == ',') {
      pair.second = line.substr(i-length, length);
      ranges.push_back(pair);
      pair = {};
      length = 0;
    } else if (i == line.length() - 1) {
      pair.second = line.substr(i-length, length+1);
      ranges.push_back(pair);
    }
     else {
      ++length;
    }
  }
  return ranges;
}

bool check_double(long long num) {
  
  long long num_copy{num};
  int num_length{};
  while (num_copy>0) {
    num_copy/=10;
    ++num_length;
  }
  if (num_length%2!=0) return 0;

  long long a{};
  long long b{};

  int index{};
  while (num>0) {
    if (index<num_length/2) {
      a*=10;
      a+=num%10;
    } else {
      b*=10;
      b+=num%10;
    }
    num/=10;
    ++index;
  }
  return (a==b); 
}

bool check_repeating(const long long &num) {
  long long num_copy{num};
  int num_length{};
  while (num_copy>0) {
    num_copy/=10;
    ++num_length;
  }
  
  for (int i{1}; i<=num_length/2; ++i) {
    if (num_length%i!=0) continue;

    int target{};
    long long n{num};
    
    for (int j{0}; j<i; ++j) {
      target*=10;
      target+=n%10;
      n/=10;
    }

    int test{};
    int len{};
    bool repeating{};
    while (n>0) {
      test*=10;
      test+=n%10;
      n/=10;
      ++len;
      if (len==i) {
        if (test==target && test!=0) {
          repeating = true;
        } else {
          repeating = false;
          break;
        }
        test=0;
        len=0;
      }
    }

    if (repeating || test == target && test!=0) { 
      return true;
    }
  }
  return false;
}

namespace day2 {
const std::string FILENAME{"inputs/input02.txt"};
long long part_one() {
  auto input = parse_string(FILENAME);
  long long total{0};
  for (auto p : input) {
    auto first = std::stoll(p.first);
    auto second = std::stoll(p.second);
    for (auto i = first; i <= second; i++) {
      if (check_double(i)) {
        total += i;
      }
    }
  }
  return total;
}

long long part_two() {
  auto input = parse_string(FILENAME);
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

int main() {
  std::cout << day2::part_one() << "\n";
  std::cout << day2::part_two() << "\n";
  return 0;
}
