#include<iostream>
#include<vector>
#include<string>

using namespace std;

#define INF (~(0x1<<31))  //用来代表无穷大

//边的结构体
struct EdgeData {
    char start;  //边的起点
    char end;   //边的终点
    int weight; //边的权重
    EdgeData() { }
    EdgeData(char s, char e, int w)
        :start(s), end(e), weight(w) { }
};

//邻接表
class ListUDG {
public:
    //构造和析构函数
    ListUDG() { }
    ListUDG(vector<char>& vexs, vector<EdgeData*>& edges);

    //算法
    void dijkstra(int vex, vector<int>& prev, vector<int>& dist); //dijkstra算法

private:
    //邻接表中的顶点对应的边结点
    class EdgeNode {
        int vex_position; //该边所指向的顶点的位置
        int weight; //该边的权
        EdgeNode* next_edge; //指向下一条弧的指针
        friend class ListUDG;
    };
    //邻接表中的顶点
    class VexNode {
        char data; //顶点信息
        EdgeNode* first_edge; //指向第一条依附该顶点的弧
        friend class ListUDG;
    };
private:
    //辅助函数
    int get_position(char ch);  //取得ch在m_vexs中的位置
    void link_last(EdgeNode* list, EdgeNode* node);  //将结点node链接到list的最后
    int get_weight(int start, int end); //获取边的权重
private:
    int m_vexs_num;  //顶点数
    int m_edge_num = 0; //边数
    vector<VexNode> m_vexs;  //保存邻接表中的所有顶点
};

//构造函数：根据现有的数据来构造图
//参数说明：
//  vexs: 保存所有的顶点
//  edges: 保存所有的边
ListUDG::ListUDG(vector<char>& vexs, vector<EdgeData*>& edges) {
    //保存顶点和权重，比如有一条边为A到B，权重为20，则
    //用vex_begin保存A，用vex_end保存B，用weight保存20
    char vex_begin;
    char vex_end;
    int weight;
    //保存顶点的位置，比如一条A到B的边，其中顶点A，B在数组中的
    //位置分别为3和7，则用position_begin保存3，用position_end保存7
    int position_begin;
    int position_end;
    //保存边结点，比如一条A到B的边，顶点A，B的位置分别为3和7，
    //用node_plus来表示顶点A后面的一个到达B的结点
    //用node_sub来表示顶点B后面的一个到达A的结点
    EdgeNode* node_plus;
    EdgeNode* node_sub;
    //初始化顶点数和边数
    m_vexs_num = vexs.size();
    m_edge_num = edges.size();
    //初始化邻接表的顶点
    for(int i = 0; i < m_vexs_num; i++) {
        VexNode vex;
        vex.data = vexs[i];
        vex.first_edge = nullptr;
        m_vexs.push_back(vex);
    }
    //初始化邻接表的边
    for(int i = 0; i < m_edge_num; i++) {
        //读取边的起始顶点和结束顶点，以及这条边的权重
        vex_begin = edges[i]->start;
        vex_end = edges[i]->end;
        weight = edges[i]->weight;
        //读取这条边的两个顶点在顶点数组m_vexs中的位置
        position_begin = get_position(vex_begin);
        position_end = get_position(vex_end);
        //初始化node_plus
        node_plus = new EdgeNode();
        node_plus->vex_position = position_end;
        node_plus->weight = weight;
        //将node_plus链接到顶点vex_begin开头的链表的末尾
        if(m_vexs[position_begin].first_edge == nullptr) {
            m_vexs[position_begin].first_edge = node_plus;
        }
        else {
            link_last(m_vexs[position_begin].first_edge, node_plus);
        }
        //初始化node_sub
        node_sub = new EdgeNode();
        node_sub->vex_position = position_begin;
        node_sub->weight = weight;
        //将node_sub链接到顶点vex_end开头的链表的末尾
        if(m_vexs[position_end].first_edge == nullptr) {
            m_vexs[position_end].first_edge = node_sub;
        }
        else {
            link_last(m_vexs[position_end].first_edge, node_sub);
        }
    }
}


/*
 * Dijkstra最短路径。
 * 即，统计图中"顶点vex"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *      vex -- 起始顶点(start vertex)。即计算"顶点vex"到其它顶点的最短路径。
 *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vex"到"顶点i"的最短路径
 *             所经历的全部顶点中，位于"顶点i"之前的那个顶点。
 *     dist -- 长度数组。即，dist[i]是"顶点vex"到"顶点i"的最短路径的长度。
 */
void ListUDG::dijkstra(int vex, vector<int>& prev, vector<int>& dist) {
    int min_value;
    int temp;
    int k = 0;
    //flags[i]=1表示“顶点vex"到"顶点i"的最短路径已经成功获取
    vector<int> flags(m_vexs_num, 0);
    //初始化dist
    for(int i = 0; i < m_vexs_num; i++) {
        dist[i] = get_weight(vex, i);  //顶点i的最短路径为"顶点vex"到"顶点i"的权
    }
    //初始化顶点vex
    flags[vex] = 1;
    dist[vex] = 0;
    //遍历m_vexs_num - 1次，每次找出一个顶点的最短路径
    for(int i = 1; i < m_vexs_num; i++) {
        //寻找当前最小的路径：
        //即，在未获取最短路径的顶点中，找到离vex最近的顶点(k)
        min_value = INF;
        for(int j = 0; j < m_vexs_num; j++) {
            if(flags[j] == 0 && dist[j] < min_value) {
                min_value = dist[j];  //保存顶点vex到顶点k的最小距离
                k = j;
            }
        }
        //标记"顶点k"为已经获取到最短路径
        flags[k] = 1;
        //修正当前最短路径和前驱顶点
        //即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"
        for(int j = 0; j < m_vexs_num; j++) {
            temp = get_weight(k, j);
            temp = (temp == INF ? INF : (min_value + temp));
            if(flags[j] == 0 && (temp < dist[j])) {
                dist[j] = temp;
                prev[j] = k;
            }
        }
    }
    //打印dijkstra最短路径的结果
    cout<<"dijkstra("<<m_vexs[vex].data<<"):  "<<endl;
    for(int i = 0; i < m_vexs_num; i++) {
        cout<<"  shortest("<<m_vexs[vex].data<<", "<<m_vexs[i].data<<")="<<dist[i]<<endl;
    }
}

//取得ch在顶点数组m_vexs中的位置
//不存在则返回-1
int ListUDG::get_position(char ch) {
    for(int i = 0; i < m_vexs_num; i++) {
        if(m_vexs[i].data == ch) {
            return i;
        }
    }
    return -1;
}

//将结点node链接到list的最后
void ListUDG::link_last(EdgeNode* list, EdgeNode* node) {
    EdgeNode* cur = list;
    while(cur->next_edge != nullptr) {
        cur = cur->next_edge;
    }
    cur->next_edge = node;
}

//获取边start到end的权重，如果不可达，返回INF
int ListUDG::get_weight(int start, int end) {
    EdgeNode* node;
    if(start == end) {
        return 0;
    }
    node = m_vexs[start].first_edge;
    while(node != nullptr) {
        if(end == node->vex_position) {
            return node->weight;
        }
        node = node->next_edge;
    }
    return INF;
}


//测试dijkstra算法
void test_dijkstra() {
    //顶点
    vector<char> vexs = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G'
    };
    //边
    vector<EdgeData*> edges = {
               // 起点 终点 权
        new EdgeData('A', 'B', 12),
        new EdgeData('A', 'F', 16),
        new EdgeData('A', 'G', 14),
        new EdgeData('B', 'C', 10),
        new EdgeData('B', 'F',  7),
        new EdgeData('C', 'D',  3),
        new EdgeData('C', 'E',  5),
        new EdgeData('C', 'F',  6),
        new EdgeData('D', 'E',  4),
        new EdgeData('E', 'F',  2),
        new EdgeData('E', 'G',  8),
        new EdgeData('F', 'G',  9)
    };
    int vexs_len = vexs.size();  //顶点的数量
    vector<int> prev(vexs_len, 0);
    vector<int> dist(vexs_len, 0);  //保存最小距离
    ListUDG* p_grapth = new ListUDG(vexs, edges);
    p_grapth->dijkstra(3, prev, dist);
}

int main()
{
    test_dijkstra();
}

