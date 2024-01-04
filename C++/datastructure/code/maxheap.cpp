#include<iostream>
#include<vector>
#include<stdexcept>

class MaxHeap {
public:
    size_t size() const;  //返回堆的大小
    bool empty() const;  //判断堆是否为空
    void push(int value);  //向队中插入元素
    int pop();  //从队中删除堆顶元素，并返回它
    int top() const;  //获取堆顶元素
private:
    std::vector<int> data_vec;  //用于保存堆数据

    //私有辅助函数
    void heapify_down(size_t parent);  //向下调整堆
    void heapify_up(size_t parent);  //向上调整堆
};

void MaxHeap::heapify_down(size_t parent) {
    size_t child = 2 * parent + 1;  //左孩子索引
    while(child < data_vec.size()) {
        //如果有右孩子并且右孩子比左孩子大，则选择右孩子
        if(child + 1 < data_vec.size() && data_vec[child + 1] > data_vec[child]) {
            child++;
        }
        //如果父结点大于孩子的值，则无需调整
        if(data_vec[parent] >= data_vec[child]) {
            break;
        }
        //否则，交换父节点和子节点
        std::swap(data_vec[parent], data_vec[child]);
        //继续向下调整
        parent = child;
        child = 2 * parent + 1;
    }
}

void MaxHeap::heapify_up(size_t child) {
    size_t parent = (child - 1) / 2;  //计算得到父节点的索引
    //如果子节点比父节点大，则交换它们并继续向上调整
    while(child > 0 && data_vec[child] > data_vec[parent]) {
        std::swap(data_vec[parent], data_vec[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

size_t MaxHeap::size() const {
    return data_vec.size();
}

bool MaxHeap::empty() const {
    return data_vec.empty();
}

void MaxHeap::push(int value) {
    data_vec.push_back(value);  //将它放入到堆的末尾
    heapify_up(data_vec.size() - 1);  //向上调整堆以满足最大堆性质
}

int MaxHeap::pop() {
    if(empty()) {
        throw std::runtime_error("Heap is empty, connot pop.");
    }
    int root = data_vec[0];  //取出堆顶元素
    data_vec[0] = data_vec.back();  //将数组的最后一个元素复制到堆顶位置
    data_vec.pop_back();  //删除数组的最后一个元素
    heapify_down(0);  //从根节点开始向下调整堆来恢复性质
    return root;  //返回被删除的元素值(原来的堆顶元素)
}

int MaxHeap::top() const {
    if(empty()) {
        throw std::runtime_error("Heap is empty.");
    }
    return data_vec[0];
}

int main()
{
    MaxHeap heap;
    heap.push(5);
    heap.push(2);
    heap.push(9);
    heap.push(10);
    heap.push(23);
    heap.push(3);
    int size = heap.size();
    for(int i = 0; i < size; i++) {
        int top = heap.top();
        heap.pop();
        printf("%d ", top);
    }
    printf("\n");
}
