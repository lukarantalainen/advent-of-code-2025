#include <cassert>
#include <iostream>
#include <string>
#include <array>

#include "solutions.h"

class Solution {
 public:
  int lengthOfLongestSubstring(std::string s) {
    int longest{};
    int left{};

    std::array<int, 256> pos {};
    for (int right{0}; right < s.size(); ++right) {
      left = std::max(left, pos[s[right]]);
      pos[s[right]] = right+1;
      longest = std::max(right-left+1, longest);
    }
    return longest;
  }
};

int main() {
  // std::map<std::string, std::string*> funcs{};

  Solution s;

  std::cout << s.lengthOfLongestSubstring("ab") << "\n";
  std::cout << s.lengthOfLongestSubstring("abcabcbb") << "\n";
  std::cout << s.lengthOfLongestSubstring("pwwkew") << "\n";
  std::cout << "\n";

  return 0;
}
