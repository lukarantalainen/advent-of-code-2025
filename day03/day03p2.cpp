#include <fstream>
#include <iostream>
#include <string>

void count_joltage(std::string f) {
  std::fstream input(f);
  std::string line;

  while (std::getline(input, line)) {
    for (auto c : line) {
      if (true)
        ;
    }
  }
}

int main() { return 0; }
