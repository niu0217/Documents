class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        int midIndex = 0;
        while(leftIndex <= rightIndex) {
            midIndex = leftIndex + (rightIndex - leftIndex) / 2;
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
        return leftIndex;
    }
};
