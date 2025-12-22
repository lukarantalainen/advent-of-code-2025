#include <fstream>
#include <iostream>
#include <string>
class SecretEntrance {
  std::string f = "../inputs/input01.txt";

 public:
  int part_one() {
    std::ifstream input(f);
    std::string line{};
    int ans{0};
    auto pointing{50};

    while (std::getline(input, line)) {
      auto dir = line[0];
      auto num = std::stoi(line.substr(1));
      pointing = (dir == 'R') ? pointing + num : pointing - num;
      pointing = (pointing % 100 + 100) % 100;
      if (pointing == 0) ans++;
    }
    input.close();
    return ans;
  }

 public:
  int part_two() {
    std::ifstream input(f);
    std::string line;
    int ans{0};
    int pointing{50};
    while (std::getline(input, line)) {
      char dir = line[0];
      int num = std::stoi(line.substr(1));
      bool start_zero = (pointing == 0);
      pointing = (dir == 'R') ? pointing + num : pointing - num;

      if ((abs(pointing) / 100) > 0) {
        ans += ((abs(pointing) / 100));
        if (pointing % 100 <= 0 && dir == 'L' && !start_zero) {
          std::cout << "here ->";
          ans++;
        }
      } else if (pointing == 0) {
        ans++;
      } else if (pointing < 0 && !start_zero) {
        ans++;
      }
      std::cout << pointing << "\n";
      pointing = (pointing % 100 + 100) % 100;
    }
    input.close();
    return ans;
  }
};

int main() {
  SecretEntrance task;
  std::cout << "Part 1: " << task.part_one() << "\n";
  std::cout << "Part 2: " << task.part_two() << "\n";
  return 0;
}
