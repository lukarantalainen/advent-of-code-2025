#include <fstream>
#include <iostream>
#include <string>

int count_zeroes() {
  std::ifstream input("input.txt");
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
          if (pointing == 0) zero = true;
          pointing -= 100;
          ans++;
        }
      }
    } else {
      pointing -= nums;
      if (pointing < 0) {
        while (pointing < 0) {
          if (pointing == 0) zero = true;
          pointing += 100;
          ans++;
        }
      }
    }

    if (zero && pointing == 0) {
      ans++;
    }
  }

  return ans;
}

int main() {
  std::cout << count_zeroes();
  return 0;
}
