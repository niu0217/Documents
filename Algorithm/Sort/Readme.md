# 排序算法

## 参考网站

https://blog.csdn.net/qq_36560894/article/details/114993113

https://blog.csdn.net/pange1991/article/details/85460755

## 排序复杂度对比

| **排序算法**     | **平均时间复杂度** | **最坏时间复杂度** | **最好时间复杂度** | **空间复杂度** | **稳定性** |
| ---------------- | ------------------ | ------------------ | ------------------ | -------------- | ---------- |
| **冒泡排序**     | O(n²)              | O(n²)              | O(n)               | O(1)           | 稳定       |
| **直接选择排序** | O(n²)              | O(n²)              | O(n²)              | O(1)           | 不稳定     |
| **直接插入排序** | O(n²)              | O(n²)              | O(n)               | O(1)           | 稳定       |
| **希尔排序**     | O(nlogn)           | O(ns)              | O(n)               | O(1)           | 不稳定     |
| **归并排序**     | O(nlogn)           | O(nlogn)           | O(nlogn)           | O(n)           | 稳定       |
| **快速排序**     | O(nlogn)           | O(n²)              | O(nlogn)           | O(logn)        | 不稳定     |
| **堆排序**       | O(nlogn)           | O(nlogn)           | O(nlogn)           | O(1)           | 不稳定     |
| **计数排序**     | O(n+k)             | O(n+k)             | O(n+k)             | O(n+k)         | 稳定       |
| **基数排序**     | O(N*M)             | O(N*M)             | O(N*M)             | O(M)           | 稳定       |

## 冒泡排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void bubbleSort(vector<int>& elements) {
    int elementsSize = elements.size();
    for(int i = 0; i < elementsSize; i++) {
        bool isSwaped = false;
        for(int j = 1; j < elementsSize - i; j++) {
            if(elements[j - 1] > elements[j]) {
                swap(elements[j - 1], elements[j]);
                isSwaped = true;
            }
        }
        if(!isSwaped) {
            break;
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    bubbleSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

## 选择排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void selectSort(vector<int>& elements) {
    int elementsSize = elements.size();
    for(int i = 0; i < elementsSize; i++) {
        int minValueIndex = i;
        for(int j = i + 1; j < elementsSize; j++) {
            if(elements[j] < elements[minValueIndex]) {
                minValueIndex = j;
            }
        }
        if(minValueIndex != i) {
            swap(elements[minValueIndex], elements[i]);
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    selectSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

选择排序的时间复杂度：

1. **最好情况**：当输入数组已经是完全有序时，选择排序仍然会进行 n-1 轮的比较和交换操作来完成排序。尽管在每一轮中，它都能立即找到正确位置上的元素，不需要做实际的交换，但算法仍需要遍历整个数组来验证这一点。因此，即使在最好情况下，选择排序的时间复杂度仍然是 O(n^2)。
2. **最坏情况**：当输入数组是逆序排列时，选择排序同样需要进行 n-1 轮比较和交换，在每一轮中都要遍历剩余未排序部分以找到最小（或最大）值，并与当前轮次的第一个元素交换。这样会导致每轮都有一次交换，因此最坏时间复杂度也是 O(n^2)。

关于不稳定性的说明： 选择排序不稳定性体现在它可能改变相等元素之间的相对顺序。在每次迭代中，选择排序都会找出剩余部分中的最小（或最大）元素并将其与当前未排序部分的起始元素交换位置。例如，考虑以下数组：

```
[5, 8, 5, 2, 9]
```

第一轮排序后，最小值 `2` 会被移动到第一个位置，得到：

```code
[2, 8, 5, 5, 9]
```

第二轮时，尽管有两个相等的 `5`，但是由于选择排序的过程，第二个 `5` 不一定会被移动到第一个 `5` 的后面。如果第二个 `5` 被选中，那么数组将变为：

```code
[2, 5, 8, 5, 9]
```

此时原本两个连续的 `5` 已经被打乱了顺序，这就是选择排序不稳定的体现。在稳定排序算法中，相同数值的相对顺序在排序前后应当保持不变。

## 插入排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void insertSort(vector<int>& elements) {
    int size = elements.size();
    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0; j--) {
            if(elements[j - 1] > elements[j]) {
                swap(elements[j - 1], elements[j]);
            }
            else {
                break;
            }
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    insertSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

插入排序的时间复杂度：

1. **最好情况**：当输入数组已经是完全有序时，插入排序只需要进行 n-1 轮的比较。在每一轮中，当前元素都恰好位于正确的位置上，因此不需要做任何交换操作。由于内层循环在每次迭代中最多只需要移动一个元素到其最终位置，所以最好的时间复杂度是 O(n)。
2. **最坏情况**：当输入数组是逆序排列时，插入排序需要进行最多的比较和移动操作。对于每个新元素，它都要与前面的所有元素进行比较并可能逐个后移这些元素以便为新元素腾出位置。因此，在最坏情况下（即每次插入都需要将所有后续元素后移一位），算法需要执行 (n-1) + (n-2) + ... + 1 次比较和移动，因此最坏时间复杂度是 O(n^2)。

是稳定算法。

## 希尔排序

https://www.runoob.com/data-structures/shell-sort.html

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void shellSort(vector<int>& elements) {
    int gap = 1;
    int size = elements.size();
    while(gap < size / 3) {
        gap = 3 * gap + 1;
    }
    while(gap >= 1) {
        for(int i = gap; i < size; i++) {
            for(int j = i; j >= gap && elements[j] < elements[j - gap]; j -= gap) {
                swap(elements[j], elements[j - gap]);
            }
        }
        gap = gap / 3;
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    shellSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

希尔排序的时间复杂度：

1. **最好情况**：尽管没有一个固定的“最好”时间复杂度，但通过精心设计的增量序列可以显著降低希尔排序的实际运行时间。理论上，如果增量序列和数据分布恰好使得每一轮子排序都能接近最佳状态（例如，元素已经大致按照最终排序顺序分布），并且最后阶段的插入排序也能近乎在已部分有序的数据上进行，那么希尔排序的性能会非常接近O(n log n)。然而，实际中难以精确控制这些条件。
2. **最坏情况**：希尔排序的最坏时间复杂度是O(n^2)，这是当增量序列选择不当或数据极其逆序时可能出现的情况。由于算法的核心是对子序列进行插入排序，而在最坏情况下，插入排序的复杂度为O(n^2)，因此若各个子序列划分得不理想，则整个希尔排序也会表现出线性对数级别的性能优势消失，退化为类似简单插入排序的效果。

希尔排序的不稳定性体现在其多趟插入排序的过程中。考虑以下数组作为例子：

```code
[5, 8, 5, 2, 9]
```

首先，希尔排序会选择一个较大的增量h，并将数组分成多个间隔为h的子序列进行插入排序。假设第一轮以增量h=3开始，那么子序列将是 `[5]`, `[8, 5]`, `[2, 9]` 分别排序。第一轮结束后数组可能变为 `[2, 5, 5, 8, 9]` 或者 `[2, 5, 8, 5, 9]`（取决于两个5之间的相对位置）。

然后，随着增量逐渐减小到1，希尔排序会在更细粒度的子序列上进行插入排序。但在之前的较大增量排序过程中，原本相邻且相等的 `5` 已经被拆分到不同子序列中，并且它们在插入排序后可能不再保持原来的前后顺序。所以，即使最终完成所有增量下的排序，我们可能会得到如 `[2, 5, 8, 5, 9]` 这样的结果，其中第二个 `5` 不再位于第一个 `5` 的后面，这证明了希尔排序的非稳定性。

是不稳定算法：在不同步长下进行插入排序时，相同值的元素可能会相互交换位置，导致排序完成后，原本相同的元素之间的相对顺序发生了变化。

## 归并排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void merge(vector<int>& elements, int idxStart, int idxMid, int idxEnd) {
    vector<int> leftSubArray(begin(elements) + idxStart,
                             begin(elements) + idxMid + 1);
    vector<int> rightSubArray(begin(elements) + idxMid + 1,
                              begin(elements) + idxEnd + 1);
    leftSubArray.insert(end(leftSubArray), numeric_limits<int>::max());
    rightSubArray.insert(end(rightSubArray), numeric_limits<int>::max());
    int idxLeft = 0;
    int idxRight = 0;
    for(int i = idxStart; i <= idxEnd; i++) {
        if(leftSubArray[idxLeft] < rightSubArray[idxRight]) {
            elements[i] = leftSubArray[idxLeft];
            idxLeft++;
        }
        else {
            elements[i] = rightSubArray[idxRight];
            idxRight++;
        }
    }
}

void mergeSort(vector<int>& elements, int idxStart, int idxEnd) {
    if(idxStart >= idxEnd) {
        return;
    }
    int idxMid = idxStart + (idxEnd - idxStart) / 2;
    mergeSort(elements, idxStart, idxMid);
    mergeSort(elements, idxMid + 1, idxEnd);
    merge(elements, idxStart, idxMid, idxEnd);
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    int elementsSize = elements.size();
    mergeSort(elements, 0, elementsSize - 1);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

## 快速排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int partition(vector<int>& elements, int low, int high) {
    int pivot = elements[low];
    while(low < high) {
        //从右边找第一个小于pivot的数的位置
        while(low < high && elements[high] >= pivot) {
            high--;
        }
        if(low < high) {
            elements[low++] = elements[high];
        }
        //从左边找第一个大于pivot的数的位置
        while(low < high && elements[low] <= pivot) {
            low++;
        }
        if(low < high) {
            elements[high--] = elements[low];
        }
    }
    elements[low] = pivot;
    return low;
}

void quickSort(vector<int>& elements, int low, int high) {
    if(low < high) {
        int pivot = partition(elements, low, high);
        quickSort(elements, low, pivot - 1);
        quickSort(elements, pivot + 1, high);
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    int elementsSize = elements.size();
    quickSort(elements, 0, elementsSize - 1);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

1. **最好情况**：当快速排序的每次划分都能均匀地将数组分成大小大致相等的两部分时，时间复杂度为O(n log n)。例如，考虑一个近乎完全随机分布的数组：

   ```code
   [7, 2, 5, 8, 3, 9, 1, 6, 4]
   ```

   在一次理想划分后，可能会变成：

   ```code
   [1, 2, 3, 4 | 5, 6, 7, 8, 9]
   ```

   这种情况下，递归树接近完全平衡，因此整体时间复杂度达到最优。

2. **最坏情况**：当快速排序在划分过程中每次都只能将数组划分为一个元素和n-1个元素时（即每次划分的基准值都是当前子数组中的最大或最小值），时间复杂度退化为O(n^2)。比如，对于已逆序排列的数组：

   ```code
   [9, 8, 7, 6, 5, 4, 3, 2, 1]
   ```

   如果每次基准值都选为第一个元素，则每次划分结果是：

   ```code
   1[x] | [8, 7, 6, 5, 4, 3, 2, 1]
   2    [x] | [7, 6, 5, 4, 3, 2, 1]
   3        ...
   ```

   此时，算法会进行n次划分，每次划分只减少一个问题规模，并且需要对剩余n-1个元素进行处理，故总体时间复杂度为O(n^2)。

**不稳定算法：**

## 堆排序

```c++
#include<iostream>
#include<vector>
#include<algorithm>

//调整堆结构,使其满足大顶堆的性质
void heapify(std::vector<int>& elements, int maxheapSize, int rootIndex) {
    int largest = rootIndex;  //初始化largest为根节点
    int left = 2 * rootIndex + 1;  //左子节点
    int right = 2 * rootIndex + 2;  //右子节点
    if(left < maxheapSize && elements[left] > elements[largest]) {
        largest = left;
    }
    if(right < maxheapSize && elements[right] > elements[largest]) {
        largest = right;
    }
    if(largest != rootIndex) {
        std::swap(elements[rootIndex], elements[largest]);
        heapify(elements, maxheapSize, largest);
    }
}

//堆排序
void heapSort(std::vector<int>& elements) {
    int maxheapSize = elements.size();
    //构建大顶堆，从最后一个非叶子节点开始调整堆结构
    for(int i = (maxheapSize / 2) - 1; i >= 0; i--) {
        heapify(elements, maxheapSize, i);
    }
    //从堆顶开始，将最大的元素交换到末尾，然后调整剩余元素
    //为堆结构，如此循环直到排好序
    for(int i = maxheapSize - 1; i >= 0; i--) {
        std::swap(elements[0], elements[i]);
        heapify(elements, i, 0);
    }
}

int main()
{
    std::vector<int> elements = {
        12, 13, 11, 5, 6, 7
    };
    heapSort(elements);
    for(auto element : elements) {
        printf("%d ", element);
    }
    printf("\n");
}

```

堆排序的时间复杂度：

1. **最好情况**：无论输入数组的顺序如何，堆排序总能保证时间复杂度为O(n log n)。这是因为构建初始堆和每次下沉操作（sift down）都需要O(log n)的时间复杂度，并且需要进行n次这样的操作来完全排序数组。

2. **最坏情况**：同样地，堆排序在最坏情况下也有O(n log n)的时间复杂度。即使数组已经有序或逆序，堆排序仍然需要经历同样的n次提取最大（或最小）元素并重新调整堆的过程。

**不稳定算法：**
堆排序不稳定性体现在它可能会改变相同键值（数值）的元素之间的相对顺序。例如，考虑以下数组：

```
[5, 10, 15, 10, 20]
```

假设我们使用最大堆对这个数组进行升序排序：

- 首先构建堆：
  ```
  [10, 15, 10, 20, 5]     // 堆顶是最大的15
  ```

- 提取堆顶元素（最大的），并重新调整堆：
  ```
  提取15后得到:   [10, 10, 20, 5] 
  调整堆后变成:   [10, 20, 10, 5]    // 这里两个10的相对位置发生了变化
  ```

- 继续此过程直到所有元素都被正确排序。

最终排序后的数组可能是这样的：

```
[5, 10, 10, 20] 或者 [5, 10, 20, 10]
```

这里可以看到原本相邻的两个 `10` 在排序后可能不再保持原有的前后顺序，这就是堆排序不稳定的体现。在稳定排序算法中，相同的元素其排序前后的相对位置应保持不变。

## 计数排序

```c++
#include<iostream>
#include<vector>
#include<string>
using namespace std;

void countSort(vector<int>& arr, int maxVal) {
    int size = arr.size();
    if(size < 1) {
        return;
    }
    vector<int> count(maxVal + 1, 0);
    vector<int> temp(arr);
    for(auto element : arr) {
        count[element]++;
    }
    for(int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i >= 0; i--) {
        arr[count[temp[i]] - 1] = temp[i];
        count[temp[i]]--;
    }
}

int main()
{
    vector<int> arr = {
        1, 5, 3, 7, 6, 2, 8, 9, 4, 3, 3
    };
    int maxVal = 9;
    countSort(arr, maxVal);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

计数排序的时间复杂度：

- **最好情况**：无论输入数组的具体内容如何，计数排序的时间复杂度总是O(n + k)，其中n是待排序数组的元素个数，k是待排序整数的最大值与最小值之间的差加1（即所有可能取到的不同数值的数量）。这是因为计数排序的主要操作包括遍历输入数组一次以统计每个数字出现的次数、填充输出数组以及恢复原始顺序，这些操作的时间复杂度都是线性的。
- **最坏情况**：同样地，计数排序在最坏情况下的时间复杂度也是O(n + k)。即使输入数组已经是有序或无序，算法所需的时间和空间开销保持不变。

## 基数排序

https://www.bilibili.com/video/BV1zF411G7AU/?spm_id_from=333.337.search-card.all.click&vd_source=c6838f09fbfc9766e04f0c65ca196c42

```c++
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

int maxbit(vector<int>& arr) {
    int size = arr.size();
    int maxData = arr[0];
    for(int i = 1; i < size; i++) {
        if(maxData < arr[i]) {
            maxData = arr[i];
        }
    }
    int d = 1;
    while(maxData >= 10) {
        maxData /= 10;
        ++d;
    }
    return d;
}

void countSort(vector<int>& arr, int maxVal, int radix) {
    int arrSize = arr.size();
    if(arrSize < 1) {
        return;
    }
    vector<int> counts(maxVal + 1, 0);
    vector<int> tempArr(arr);
    int k = 0;
    for(int j = 0; j < arrSize; j++) {
        k = (arr[j] / radix) % 10;
        counts[k]++;
    }
    for(int j = 1; j < 10; j++) {
        counts[j] += counts[j - 1];
    }
    for(int j = arrSize - 1; j >= 0; j--) {
        k = (tempArr[j] / radix) % 10;
        arr[counts[k] - 1] = tempArr[j];
        counts[k]--;
    }
}

void radixSort(vector<int>& arr) {
    int d = maxbit(arr);
    int radix = 1;
    for(int i = 1; i <= d; i++) {
        countSort(arr, 9, radix);
        radix = radix * 10;
    }
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    radixSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```



## 桶排序

https://www.bilibili.com/video/BV1QA411j7qV?p=1&vd_source=c6838f09fbfc9766e04f0c65ca196c42

数组实现桶排序：

```c++
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

void bucketSort(vector<int>& arr) {
    vector<vector<int>> bucketArray(5, vector<int>(5, INT_MAX));
    vector<int> bucketSizeArray(5, 0);
    int arrSize = arr.size();
    for(int i = 0; i < arrSize; i++) {
        bucketArray[arr[i] / 10][bucketSizeArray[arr[i] / 10]++] = arr[i];
    }
    for(int i = 0; i < 5; i++) {
        sort(begin(bucketArray[i]), end(bucketArray[i]));
    }
    int k = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < bucketSizeArray[i]; j++) {
            arr[k++] = bucketArray[i][j];
        }
    }
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    bucketSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}

```

链表实现桶排序：

```c++
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

struct ListNode {
    explicit ListNode(int initialData)
        : data{ initialData }, next{ nullptr } { }
    ~ListNode() {
        cout<<"Destructure   "<<data<<"  ...\n";
    }
    int data;
    ListNode* next;
};

ListNode* insertNode(ListNode* head, int value) {
    ListNode* dummyNode = new ListNode(0);
    dummyNode->next = head;
    ListNode* newNode = new ListNode(value);
    ListNode* pre = dummyNode;
    ListNode* cur = head;
    while(cur != nullptr && cur->data <= value) {
        pre = cur;
        cur = cur->next;
    }
    newNode->next = cur;
    pre->next = newNode;

    ListNode* resultNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return resultNode;
}

ListNode* mergeList(ListNode* head1, ListNode* head2) {
    ListNode* dummyNode = new ListNode(0);
    ListNode* cur = dummyNode;
    while(head1 != nullptr && head2 != nullptr) {
        if(head1->data <= head2->data) {
            cur->next = head1;
            head1 = head1->next;
        }
        else {
            cur->next = head2;
            head2 = head2->next;
        }
        cur = cur->next;
    }
    if(head1 != nullptr) {
        cur->next = head1;
    }
    else if(head2 != nullptr) {
        cur->next = head2;
    }

    cur = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return cur;
}

void clearAllNodes(vector<ListNode*> buckets, ListNode* head) {
    ListNode* nextNode = nullptr;
    while(head != nullptr) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    int size = buckets.size();
    for(int i = 0; i < size; i++) {
        buckets[i] = nullptr;
    }
}

void bucketSort(vector<int>& arr) {
    vector<ListNode*> buckets(10, (ListNode*)(0));
    int arrSize = arr.size();
    for(int i = 0; i < arrSize; i++) {
        int index = arr[i] / 10;
        ListNode* head = buckets.at(index);
        buckets.at(index) = insertNode(head, arr[i]);
    }
    ListNode* head = buckets.at(0);
    for(int i = 1; i < 10; i++) {
        head = mergeList(head, buckets.at(i));
    }
    for(int i = 0; i < arrSize; i++) {
        arr[i] = head->data;
        head = head->next;
    }

    head = buckets.at(0);
    clearAllNodes(buckets, head);
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    bucketSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}
```

