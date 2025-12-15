#include <fstream>
#include <iostream>
#include <string>

void count_joltage(std::string f) {
  std::fstream input(f);
  std::string line;
  while (std::getline(input, line)) {
    int first{line[0]};
    int highest{0};
    for (auto c : line) {
      if (c > highest) highest = c;
      first = c;
    }
  }
}

int main() {
  count_joltage("tests\\input03-test.txt");
  return 0;
}
