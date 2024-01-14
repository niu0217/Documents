//二分法
class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num == 1) {
            return true;
        }
        int leftValue = 1;
        int rightValue = num / 2;
        int midValue = 0;
        long long result = 0;
        while(leftValue <= rightValue) {
            midValue = leftValue + (rightValue - leftValue) / 2;
            result = (long long)midValue * midValue;
            if(result > num) {
                rightValue = midValue - 1;
            }
            else if(result < num){
                leftValue = midValue + 1;
            }
            else {
                return true;
            }
        }
        return false;
    }
};

//牛顿迭代法
class Solution {
public:
    bool isPerfectSquare(int num) {
        double x0 = num;
        while (true) {
            double x1 = (x0 + num / x0) / 2;
            if (x0 - x1 < 1e-6) {
                break;
            }
            x0 = x1;
        }
        int x = (int) x0;
        return x * x == num;
    }
};

