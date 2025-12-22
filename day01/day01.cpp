#include <fstream>
#include <iostream>
#include <string>

int count_zeroes(std::string f) {
  std::ifstream input(f);
  std::string line{};
  int ans{0};
  auto pointing{50};

  while (std::getline(input, line)) {
    auto dir = line[0];
    auto num = std::stoi(line.substr(1));
    // first add/subtract number aka rotion
    pointing = (dir == 'R') ? pointing + num : pointing - num;
    // next if negative&not 0 -> pointing = 100-modulo ->
    // e.g. 100-160%100 -> 100-60 -> 40
    pointing = (pointing <= 0 && pointing % 100 != 0) ? 100 + (pointing % 100)
                                                      : pointing % 100;
    if (pointing == 0) ans++;
  }
  return ans;
}

int main() {
  auto input = "../inputs/input01.txt";
  std::cout << count_zeroes(input);
  return 0;
}
