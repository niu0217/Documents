class Solution {
public:
    int getFirstPosition(vector<int>& nums, int target) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        int midIndex = 0;
        bool isFind = false;
        while(leftIndex <= rightIndex) {
            midIndex = leftIndex + (rightIndex - leftIndex) / 2;
            if(target <= nums[midIndex]) {
                if(target == nums[midIndex]) {
                    isFind = true;
                }
                rightIndex = midIndex - 1;
            }
            else {
                leftIndex = leftIndex + 1;
            }
        }
        if(!isFind) {
            leftIndex = -1;
        }
        return leftIndex;
    }
    int getLastPosition(vector<int>& nums, int target) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        int midIndex = 0;
        bool isFind = false;
        while(leftIndex <= rightIndex) {
            midIndex = leftIndex + (rightIndex - leftIndex) / 2;
            if(target < nums[midIndex]) {
                rightIndex = midIndex - 1;
            }
            else {
                if(target == nums[midIndex]) {
                    isFind = true;
                }
                leftIndex = leftIndex + 1;
            }
        }
        if(!isFind) {
            rightIndex = -1;
        }
        return rightIndex;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int firstPosition = getFirstPosition(nums, target);
        int lastPosition = getLastPosition(nums, target);
        return { firstPosition, lastPosition };
    }
};
