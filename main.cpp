#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

#include "solutions.h"

class Solution {
 public:
  int lengthOfLongestSubstring(std::string s) {
    int longest{};
    int left{};
    int right{};

    if (s.length() == 0) return 0;

    std::unordered_set<char> seen{};
    for (int i{0}; i < s.size(); ++i) {
      
      if (seen.count(s[right])) {
        if (right - left >= longest) {
          longest = right - left;
        }
        
        for (int j{left}; j < right; ++j) {
          seen.erase(s[j]);
          if (s[right] == s[j]) {
            left = j+1;
            break;
          }
        }
      }
      seen.insert(s[right]);
      ++right;
    }
    
    if (right - left >= longest) {
      longest = right - left;
    }

    return longest;
  }
};

int main() {
  // std::map<std::string, std::string*> funcs{};

  Solution s;

  std::cout << s.lengthOfLongestSubstring("") << "\n";
  std::cout << s.lengthOfLongestSubstring("au") << "\n";
  std::cout << s.lengthOfLongestSubstring("babcdbaba") << "\n";
  std::cout << "\n";

  return 0;
}
