#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        int l1{static_cast<int>(nums1.size())};
        int l2{static_cast<int>(nums2.size())};
        if (!l1 && !l2) {
            return 0;
        }

        else if (!l1) {
            if (nums2.size()%2==0) {
                return (nums2[l2/2-1]+nums2[l2/2])/2.0;
            } else {
                return nums2[l2/2];
            }
        }
        
        else if (!l2) {
            if (nums1.size()%2==0) {
                return (nums1[l1/2-1]+nums1[l1/2])/2.0;
            } else {
                return nums1[l1/2];
            }
        }

        int i1{};
        int i2{};

        std::vector<int> merged{};
        
        for (int i{0}; i<l1+l2; ++i) {
            if (i1<l1 && i2<l2) {
                if (nums1[i1]<nums2[i2]) {
                    merged.push_back(nums1[i1]);
                    ++i1;
                } else {
                    merged.push_back(nums2[i2]);
                    ++i2;
                }
            } else if (i1>=l1 && i2<l2) {
                merged.push_back(nums2[i2]);
                ++i2;
            } else if (i1<l1) {
                merged.push_back(nums1[i1]);
                ++i1;
            }
        }
        
        if (merged.size()%2==0) {
            return (merged[merged.size()/2-1]+merged[merged.size()/2])/2.0;
        } else {
            return merged[merged.size()/2];
        }
    }
};

int main() {
    Solution s;

    std::vector<int> v1 {3, 4, 5};
    std::vector<int> v2 {6, 7};

    cout << s.findMedianSortedArrays(v1, v2);
    return 0;
}
