#include<iostream>
#include<vector>
#include<algorithm>

//调整堆结构
void heapify(std::vector<int>& nums, int n, int i) {
    int largest = i;  //初始化largest为根节点
    int left = 2 * i + 1;  //左子节点
    int right = 2 * i + 2;  //右子节点
    if(left < n && nums[left] > nums[largest]) {
        largest = left;
    }
    if(right < n && nums[right] > nums[largest]) {
        largest = right;
    }
    if(largest != i) {
        std::swap(nums[i], nums[largest]);
        heapify(nums, n, largest);
    }
}

//堆排序
void heap_sort(std::vector<int>& nums) {
    int n = nums.size();
    //构建大顶堆，从最后一个非叶子节点开始调整堆结构
    for(int i = (n / 2) - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }
    //从堆顶开始，将最大的元素交换到末尾，然后调整剩余元素
    //为堆结构，如此循环直到排好序
    for(int i = n - 1; i >= 0; i--) {
        std::swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}

int main()
{
    std::vector<int> nums = {
        12, 13, 11, 5, 6, 7
    };
    heap_sort(nums);
    for(auto num : nums) {
        printf("%d ", num);
    }
    printf("\n");
}
