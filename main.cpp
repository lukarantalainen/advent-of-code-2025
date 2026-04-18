#include <iostream>
#include <map>
#include "solutions.h"
#include <cassert>
#include <string>
#include <set>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
      if (s.length() == 0) {
        return 0;
      }
      
      int longest{1};
      int left{};
      int right{};
      
      std::unordered_set<char> seen{};
      for (int i{0}; i<s.length(); ++i) {
        if (!seen.count(s[i])) {
          ++right;
        } else {
          longest = right-left+1;
          std::cout << s.substr(left, right-left+1) << "\n";
          seen.clear();
          for (int j{left}; j<s.length(); ++j) {
            if (s[j]==s[i]) {
              left = j+1;
              break;
            }
          }
        }
        seen.insert(s[i]);
      }
      return longest;
    }
};

int main() {
  //std::map<std::string, std::string*> funcs{};

  Solution s;
  std::string str{"ababb"};
  
  s.lengthOfLongestSubstring("abcbadbd");
  s.lengthOfLongestSubstring(str);
  s.lengthOfLongestSubstring("ohomm");
  std::cout << "\n";

  return 0;
}
