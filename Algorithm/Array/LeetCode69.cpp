class Solution {
public:
    int mySqrt(int x) {
        if(x == 1) {
            return 1;
        }
        int leftIndex = 1;
        int rightIndex = x;
        long long midIndex = 0;
        long long curSqrt = 0.0;
        while(leftIndex <= rightIndex) {
            midIndex = leftIndex + (rightIndex - leftIndex) / 2;
            curSqrt = midIndex * midIndex;
            if(curSqrt < x) {
                leftIndex = midIndex + 1;
            }
            else if(curSqrt > x) {
                rightIndex = midIndex - 1;
            }
            else {
                return midIndex;
            }
        }
        return rightIndex;
    }
};
