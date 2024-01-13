class Solution {
public:
    int search(vector<int>& nums, int target) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        while(leftIndex <= rightIndex) {
            int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
            if(target < nums[midIndex]) {
                rightIndex = midIndex - 1;
            }
            else if(target > nums[midIndex]) {
                leftIndex = midIndex + 1;
            }
            else {
                return midIndex;
            }
        }
        return -1;
    }
};
