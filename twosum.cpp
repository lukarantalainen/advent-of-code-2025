#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> pairs{};
        for (int i{0}; i<nums.size(); ++i) {
            if (pairs.count(nums[i])) {
                return {pairs[nums[i]], i};
            }
            pairs[target-nums[i]] = i;
        }
        return {0, 0};
    }
};

int main() {
    Solution s;
    std::vector v1 {1, 2, 3};
    for (auto i : s.twoSum(v1, 4)) {
        cout << i;
    }

    return 0;
}
