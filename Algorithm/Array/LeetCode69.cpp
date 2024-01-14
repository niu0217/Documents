class Solution {
public:
    int mySqrt(int x) {
        if(x == 1) {
            return 1;
        }
        int leftValue = 1;
        int rightValue = x;
        long long midValue = 0;
        while(leftValue <= rightValue) {
            midValue = leftValue + (rightValue - leftValue) / 2;
            if(midValue * midValue == x) {
                return midValue;
            }
            else if( midValue * midValue < x) {
                leftValue = midValue + 1;
            }
            else {
                rightValue = midValue - 1;
            }
        }
        return rightValue;
    }
};
