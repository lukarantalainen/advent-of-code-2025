#include <fstream>
#include <iostream>
#include <string>

int count_rotations(std::string filename) {
  std::ifstream input(filename);
  std::string line{};

  int pointing{50};
  int passwd{0};

  while (std::getline(input, line)) {
    int zeroes{0};
    int nums = std::stoi(line.substr(1));

    pointing = (line[0] == 'R') ? pointing + nums : pointing - nums;
    pointing = (pointing % 100 + 100) % 100;

    if (pointing == 0) passwd++;
  }
  return passwd;
}

int main() {
  std::cout << count_rotations("../inputs/input01-test.txt");
  return 0;
}
