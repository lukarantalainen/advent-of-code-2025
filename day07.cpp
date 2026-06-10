#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace day07 {
const std::string FILENAME{"inputs/input07.txt"};
long long part_one() {
    std::ifstream input(FILENAME);
    std::string line;

    long long beams{};
    std::unordered_set<int> previous_line{};
    std::unordered_set<int> current_line{};

    std::vector<std::string> tree{};
    std::string prev{};
    std::string curr{};

    while (std::getline(input, line)) {
        curr = line;

        for (int i{0}; i<line.length(); ++i) {
            if (line[i] == 'S') {
                current_line.insert(i);
                curr[i] = 'S';
                break;
            } else if (line[i] == '^' && previous_line.count(i)) {
                current_line.erase(i);
                ++beams;
                if (!current_line.count(i-1)) {
                    curr[i-1] = '|';
                    current_line.insert(i-1);                    
                }
                if (!current_line.count(i+1)) {
                    curr[i+1] = '|';
                    current_line.insert(i+1);
                }
            } else if (previous_line.count(i)) {
                curr[i] = '|';
                current_line.insert(i);
            } 
        }
        tree.push_back(std::string(curr.begin(), curr.end()));
        previous_line = current_line;
        prev = curr;
    }
    input.close();
    
    for (auto l : tree) {
        std::cout << l << "\n";
    }

    return beams;
}

long long part_two() {
    
}

}

int main()  {
    std::cout << day07::part_one() << "\n"; 

    return 0;
}
    