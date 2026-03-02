#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

constexpr char roll_char{'@'};

std::vector<std::vector<char>> create_grid(std::string filename) {
  std::vector<std::vector<char>> grid{};
  std::fstream input(filename);
  std::string line;

  while (std::getline(input, line)) {
    std::vector<char> row{};

    for (char c : line) {
      row.push_back(c);
    }
    grid.push_back(row);
  }
  return grid;
}

std::set<std::pair<int, int>> list_coords(std::vector<std::vector<char>> grid) {
  std::set<std::pair<int, int>> roll_coords;
  int count{0};
  int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      std::pair<int, int> coords{row, col};
      if (grid[row][col] == roll_char) {
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

int count_rolls(std::set<std::pair<int, int>> roll_coords,
                std::vector<std::vector<char>> grid) {
  const int y[]{-1, -1, -1, 0, 1, 1, 1, 0};
  const int x[]{-1, 0, 1, 1, 1, 0, -1, -1};

  int accessible{0};

  auto coords_copy = roll_coords;
  auto grid_copy = grid;

  const int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    const int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      if (grid[row][col] != roll_char) continue;
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
        coords_copy.erase(std::make_pair(row, col));
        accessible++;
      }
    }
  }
  return accessible;
}

int count_rolls_recursive(std::set<std::pair<int, int>> roll_coords,
                          std::vector<std::vector<char>> grid) {
  const int y[]{-1, -1, -1, 0, 1, 1, 1, 0};
  const int x[]{-1, 0, 1, 1, 1, 0, -1, -1};

  int accessible{0};

  auto new_coords = roll_coords;
  auto new_grid = grid;

  const int grid_height{static_cast<int>(grid.size())};
  for (int row{0}; row < grid_height; row++) {
    const int row_length{static_cast<int>(grid[row].size())};
    for (int col{0}; col < row_length; col++) {
      if (grid[row][col] != roll_char) continue;
      int border_roll_count{0};
      for (int i{0}; i < 8; i++) {
        int y_coord{row + y[i]};
        int x_coord{col + x[i]};
        std::pair<int, int> coords{y_coord, x_coord};
        if (roll_coords.count(coords) == 1) border_roll_count++;
      }
      if (border_roll_count < 4) {
        new_coords.erase(std::make_pair(row, col));
        new_grid[row][col] = '.';  // or x
        accessible++;
      }
    }
  }

  if (accessible == 0) {
    reconstruct_grid(new_grid);
    return accessible;
  }
  return accessible + count_rolls_recursive(new_coords, new_grid);
}

namespace day4 {
const std::string FILENAME = "inputs/input04.txt";
int part_one() {
  std::vector<std::vector<char>> grid{create_grid(FILENAME)};
  std::set<std::pair<int, int>> roll_coords{list_coords(grid)};
  return count_rolls(roll_coords, grid);
}

int part_two() {
  std::vector<std::vector<char>> grid{create_grid(FILENAME)};
  std::set<std::pair<int, int>> coords = list_coords(grid);
  int ans = count_rolls_recursive(coords, grid);
  return ans;
}
}  // namespace day4
