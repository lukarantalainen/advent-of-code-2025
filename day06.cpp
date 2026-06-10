#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


std::vector<std::vector<std::string>> parse_input(std::string filename) {
  std::fstream input(filename);
  std::string line;
  std::vector<std::vector<std::string>> worksheet;

  while (std::getline(input, line)) {
    char prev_char{line[0]};
    std::string stripped_line;
    for (int i{0}; i < line.length(); i++) {
      if (line[i] == ' ' && prev_char == ' ' || line[i] == ' ' && !prev_char ||
          line[i] == ' ' && i == line.length() - 1) {
        prev_char = line[i];
      } else {
        stripped_line.push_back(line[i]);
        prev_char = line[i];
      }
    }
    stripped_line.push_back(' ');

    std::string current_item;
    std::vector<std::string> current_line{};
    for (int i{0}; i < stripped_line.length(); i++) {
      if (stripped_line[i] == ' ') {
        current_line.push_back(current_item);
        current_item = "";
      } else {
        current_item.push_back(stripped_line[i]);
      }
    }
    worksheet.push_back(current_line);
  }

  return worksheet;
}



namespace day6 {
const std::string FILENAME{"inputs/input06.txt"};
long long part_one() {
  auto worksheet{parse_input(FILENAME)};
  auto m{worksheet.size()};
  auto n{worksheet[0].size()};
  long long ans{0};

  for (int column{0}; column < n; column++) {
    std::string sign{worksheet[m - 1][column]};
    long long sum{std::stoi(worksheet[0][column])};
    for (int line{1}; line < m - 1; line++) {
      if (sign == "+") {
        sum += std::stoi(worksheet[line][column]);
      } else if (sign == "*") {
        sum *= std::stoi(worksheet[line][column]);
      }
    }
    ans += sum;
  }
  return ans;
}

long long part_two() {
  std::vector<std::string> worksheet;

  std::string line;
  std::ifstream input("inputs/input06.txt");
  while (std::getline(input, line)) {
    if (line == "") break;
    worksheet.push_back(line);
  }

  const int n{static_cast<int>(worksheet.size())};
  const int m{static_cast<int>(worksheet[0].length())};

  long long total{};
  
  std::vector<int> nums;

  char op{'\0'};
  bool space{true};
  for (int i{}; i < m; ++i) {
    int sum{};
    if (space) {
      op = worksheet.back()[i];
    }
    space = true;
    
    
    for (int j{}; j < (n - 1); ++j) {
      if (worksheet[j][i] != ' ') {
        sum *= 10;
        sum += worksheet[j][i] - '0';
        space = false;
      }
    }
    nums.push_back(sum);
    // for (auto num : nums) std::cout << num << " ";
    // std::cout << "\n";

    if (space || i == m-1) {
      
      long long count{0};
      for (auto num : nums) {
        
        switch (op) {
          case '+':
          count += num;
          break;
          case '*':
          if (count == 0) count = 1;
          if (!num) continue;
          count *= num;
          break;  
        }
      }
      total += count;
      nums.clear();
      op = '\0';
    }
  }

  return total;
}
}  // namespace day6



int main() {
  std::cout << day6::part_two();
  return 0;
}

