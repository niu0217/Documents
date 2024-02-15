//二分法
class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num == 1) {
            return true;
        }
        int leftIndex = 1;
        int rightIndex = num;
        long long midIndex = 0;
        long long curSqrt = 0.0;
        while(leftIndex <= rightIndex) {
            midIndex = leftIndex + (rightIndex - leftIndex) / 2;
            curSqrt = midIndex * midIndex;
            if(curSqrt == num) {
                return true;
            }
            else if(curSqrt < num) {
                leftIndex = midIndex + 1;
            }
            else {
                rightIndex = midIndex - 1;
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

