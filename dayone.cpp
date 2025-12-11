#include <fstream>
#include <iostream>
#include <string>

int count_zeroes(std::string f) {
  std::ifstream input(f);
  std::string line{};
  auto ans{0};
  auto pointing{50};

  while (std::getline(input, line)) {
    auto dir = line[0];
    auto nums = std::stoi(line.substr(1));
    auto zero = false;

    if (dir == 'R') {
      pointing += nums;
      if (pointing > 99) {
        while (pointing > 99) {
          pointing -= 100;
          ans++;
        }
      }

    } else {
      pointing -= nums;

      if (pointing < 0) {
        while (pointing < 0) {
          pointing += 100;
          ans++;
        }
      }
    }
    std::cout << pointing << "\n";
  }
  std::cout << "-------" << "\n";

  return ans;
}

int main() {
  auto input = "input-test.txt";
  std::cout << count_zeroes(input);
  return 0;
}
