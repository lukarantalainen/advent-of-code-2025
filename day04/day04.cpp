#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::vector<std::vector<char>> grid{};

void read_file() {
  std::string f{"../inputs/input04.txt"};
  std::fstream input(f);
  std::string line;

  while (std::getline(input, line)) {
    std::vector<char> row{};

    for (char c : line) {
      row.push_back(c);
    }
    grid.push_back(row);
  }
}

std::set<std::pair<int, int>> list_coords() {
  std::set<std::pair<int, int>> roll_coords;
  int count{0};
  int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      std::pair<int, int> coords{row, col};
      if (grid[row][col] == '@') {
        roll_coords.insert(coords);
        count++;
      }
    }
  }
  return roll_coords;
}

void reconstruct_grid(std::vector<std::vector<char>> grid) {
  const int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    const int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      std::cout << grid[row][col];
    }
    std::cout << "\n";
  }
}

int count_rolls(std::set<std::pair<int, int>> roll_coords) {
  const int y[]{-1, -1, -1, 0, 1, 1, 1, 0};
  const int x[]{-1, 0, 1, 1, 1, 0, -1, -1};

  int accessible{0};

  auto grid_copy = grid;

  const int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    const int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      if (grid[row][col] != '@') continue;
      int roll_count{0};
      for (int i{0}; i < 8; i++) {
        int y_coord{(row + y[i])};
        int x_coord{(col + x[i])};
        std::pair<int, int> coords{y_coord, x_coord};
        if (roll_coords.count(coords) == 1) {
          roll_count++;
        }
      }

      if (roll_count < 4) {
        grid_copy[row][col] = 'x';
        accessible++;
      }
    }
  }
  reconstruct_grid(grid_copy);
  return accessible;
}

int main() {
  read_file();
  std::set<std::pair<int, int>> roll_coords{list_coords()};
  std::cout << count_rolls(roll_coords);
  return 0;
}
