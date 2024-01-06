#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<iomanip>

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

    //图的遍历
    void dfs(); //深度遍历
    void dfs_traversal(int vex_index, vector<int>& visited); //辅助dfs函数
    void bfs(); //广度优先遍历图

    //算法
    //dijkstra算法
    void dijkstra(int vex, vector<int>& prev, vector<int>& dist);
    void prim(int vex_index); //prim最小生成树
    void kruskal(); //kruskal算法

    //其余函数
    void print();  //打印图
    EdgeData* get_edges(); //获取图中的所有边
    void sort_edges(EdgeData* edges); //对边按照权值大小进行排序
    int get_end(vector<int>& vends, int i); //获取下标为i的顶点的终点

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

//深度遍历图
void ListUDG::dfs() {
    vector<int> visited(m_vexs_num, 0);
    cout<<"DFS: ";
    //深度遍历图，将访问过的顶点在visited中置1
    for(int vex_index = 0; vex_index < m_vexs_num; vex_index++) {
        if(!visited[vex_index]) {
            dfs_traversal(vex_index, visited);
        }
    }
    cout<<endl;
}

//辅助函数：递归遍历图，从顶点vex开始
void ListUDG::dfs_traversal(int vex_index, vector<int>& visited) {
    EdgeNode* node;
    visited[vex_index] = 1; //将顶点vex标记为已经访问过了
    cout<<m_vexs[vex_index].data;
    //node保存的是顶点vex的第一个邻接顶点
    node = m_vexs[vex_index].first_edge;
    //如果邻接顶点没有被访问，则以邻接顶点开始进行递归遍历
    //否则，访问邻接顶点的第一个邻接顶点
    while(node != nullptr) {
        if(!visited[node->vex_position]) {
            dfs_traversal(node->vex_position, visited);
        }
        node = node->next_edge;
    }
}

//广度优先遍历图，使用队列实现
void ListUDG::bfs() {
    queue<int> que_vex_index; //用于保存顶点下标的队列
    vector<int> visited(m_vexs_num, 0); //顶点访问标记
    EdgeNode* node = nullptr;
    cout<<"BFS: ";
    //先将一个顶点入队
    que_vex_index.push(0);
    //遍历队列
    while(!que_vex_index.empty()) {
        int size = que_vex_index.size();
        for(int i = 0; i < size; i++) {
            int vex_index = que_vex_index.front();
            que_vex_index.pop();
            //顶点vex没有被访问
            if(!visited[vex_index]) {
                visited[vex_index] = 1; //将顶点vex标记为已经访问过了
                cout<<m_vexs[vex_index].data<<" ";
            }
            //用node保存顶点vex的第一个邻接顶点
            node = m_vexs[vex_index].first_edge;
            //依次访问顶点vex的邻接顶点
            while(node != nullptr) {
                //邻接顶点的索引
                int adjvex_index = node->vex_position;
                //如果邻接顶点没有被访问，标记为已经访问过了
                //并将它入队
                if(!visited[adjvex_index]) {
                    visited[adjvex_index] = 1;
                    cout<<m_vexs[adjvex_index].data<<" ";
                    que_vex_index.push(adjvex_index);
                }
                node = node->next_edge;
            }
        }
    }
    cout<<endl;
}


/*
 * Dijkstra最短路径。
 * 即，统计图中"顶点vex"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *      vex -- 起始顶点(start vertex)。即计算"顶点vex"到其它顶点的最短路径
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
        //顶点i的最短路径为"顶点vex"到"顶点i"的权
        dist[i] = get_weight(vex, i);
    }
    //初始化顶点vex
    flags[vex] = 1;
    dist[vex] = 0;
    //遍历m_vexs_num - 1次，每次找出一个顶点的最短路径
    for(int i = 1; i < m_vexs_num; i++) {
        //寻找当前最小的路径：
        //在未获取最短路径的顶点中，找到离vex最近的顶点(k)
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
        //即，当已经"顶点k的最短路径"之后，
        //更新"未获取最短路径的顶点的最短路径和前驱顶点"
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
        cout<<"  shortest("<<m_vexs[vex].data<<", "
            <<m_vexs[i].data<<")="<<dist[i]<<endl;
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

//prim最小生成树
//参数说明：
//  vex_index: 从图中的顶点vex开始，生成最小树，vex_index表示
//             顶点vex的下标
void ListUDG::prim(int vex_index) {
    int min_value;
    int sum = 0; //保存最小生成树的权值和
    int index = 0; //保存prim最小树的索引，即prims数组的索引
    vector<char> prims(m_vexs_num, 0); //prim最小树的结果数组
    vector<int> weights(m_vexs_num, 0); //顶点间边的权值
    //prim最小生成树中第一个数就是起点
    prims[index++] = m_vexs[vex_index].data;
    //初始化顶点的权值数组
    //将每个顶点的权值初始化为顶点vex到该顶点的权值
    for(int i = 0; i < m_vexs_num; i++) {
        weights[i] = get_weight(vex_index, i);
    }
    for(int i = 0; i < m_vexs_num; i++) {
        //不处理vex_index,因为就是从它开始的
        if(i == vex_index) {
            continue;
        }
        int j = 0;
        int k = 0;
        min_value = INF;
        //找到未加入到最小生成树中的顶点中，权值最小的顶点，并
        //用k标记起来
        while(j < m_vexs_num) {
            //如果weights[j]=0,表示第j个结点已经加入到最小生成树中了
            if(weights[j] != 0 && weights[j] < min_value) {
                min_value = weights[j];
                k = j;
            }
            j++;
        }
        //经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点
        //是第k个顶点，将第k个顶点加入到最小生成树的结果数组中
        prims[index++] = m_vexs[k].data;
        //将第k个顶点的权值标记为0，表示已经加入了最小树结果中
        weights[k] = 0;
        //当第k个顶点被加入到最小生成树的结果数组中之后，更新
        //其他顶点的权值
        for(j = 0; j < m_vexs_num; j++) {
            //获取第k个顶点到第j个顶点的权值
            int temp = get_weight(k, j);
            //当第j个结点没有被处理，并且需要更新时才被更新
            if(weights[j] != 0 && temp < weights[j]) {
                weights[j] = temp;
            }
        }
    }
    //计算最小生成树的权值
    for(int i = 1; i < index; i++) {
        min_value = INF;
        //获取prims[i]在m_vexs中的位置
        int n = get_position(prims[i]);
        //在vexs[0~i-1]中，找出到i的权值最小的顶点，如果i == j的
        //话，就是自己到自己的距离，没有意义
        for(int j = 0; j < i; j++) {
            int m = get_position(prims[j]);
            int temp = get_weight(m, n);
            if(temp < min_value) {
                min_value = temp;
            }
        }
        sum += min_value;
    }
    //打印最小生成树
    cout<<"PRIM("<<m_vexs[vex_index].data<<")="<<sum<<": ";
    for(int i = 0; i < index; i ++) {
        cout<<prims[i]<<" ";
    }
    cout<<endl;
}


//打印图
void ListUDG::print() {
    EdgeNode* node;
    cout<<"List Graph: "<<endl;
    for(int i = 0; i < m_vexs_num; i++) {
        cout<<i<<"("<<m_vexs[i].data<<"): ";
        node = m_vexs[i].first_edge;
        while(node != nullptr) {
            cout<<node->vex_position<<"("<<
                m_vexs[node->vex_position].data<<
                "-->"<<node->weight<<") ";
            node = node->next_edge;
        }
        cout<<endl;
    }
    cout<<endl;
}

//获取图中的所有边
EdgeData* ListUDG::get_edges() {
    int index = 0;
    EdgeData* edges;
    EdgeNode* node;
    edges = new EdgeData[m_edge_num];
    //edges指向一块内存，其中保存了所有的边数据
    for(int i = 0; i < m_vexs_num; i++) {
        node = m_vexs[i].first_edge;
        while(node != nullptr) {
            //保证终点总是比起点大
            if(node->vex_position > i) {
                edges[index].start = m_vexs[i].data;
                edges[index].end = m_vexs[node->vex_position].data;
                edges[index].weight = node->weight;
                index++;
            }
            node = node->next_edge;
        }
    }
    return edges;
}

//克鲁斯卡尔算法
void ListUDG::kruskal() {
    int m;
    int n;
    int begin_index;
    int end_index;
    int index = 0; //vec_result数组的索引
    EdgeData* p_edges; //指向一块内存，保存了图中所有的边
    //保存已有最小生成树中每个顶点在该最小树中的终点
    vector<int> vends(m_vexs_num, 0);
    //结果数组，保存kruskal最小生成树的边
    vector<EdgeData> vec_result;
    //获取图中的所有边
    p_edges = get_edges();
    //将边按照权从小到大排序
    sort_edges(p_edges);
    for(int i = 0; i < m_edge_num; i++) {
        //获取第i条边的起点的序号
        begin_index = get_position(p_edges[i].start);
        //获取第i条边的终点的序号
        end_index = get_position(p_edges[i].end);
        //获取begin_index在已有的最小生成树中的终点
        m = get_end(vends, begin_index);
        //获取end_index在已有的最小生成树中的终点
        n = get_end(vends, end_index);
        //如果m!=n,意味着边i与已经添加到最小生成树中的顶点没有形成环路
        if(m != n) {
            //设置m在已有的最小生成树中的终点为n
            vends[m] = n;
            vec_result.push_back(p_edges[i]);
            index++;
        }
    }
    delete []p_edges; //释放之前动态申请的数组，防止内存泄漏
    //统计并打印kruskal最小生成树的信息
    int length = 0;
    for(int i = 0; i < index; i++) {
        length += vec_result[i].weight;
    }
    cout<<"Kruskal="<<length<<": ";
    for(int i = 0; i < index; i++) {
        cout<<"("<<vec_result[i].start<<", "<<vec_result[i].end<<") ";
    }
    cout<<endl;
}

//对边按照权值大小进行排序，从小到大，
//采用冒泡排序
void ListUDG::sort_edges(EdgeData* edges) {
    for(int i = 0; i < m_edge_num; i++) {
        for(int j = i + 1; j < m_edge_num; j++) {
            if(edges[i].weight > edges[j].weight) {
                swap(edges[i], edges[j]);
            }
        }
    }
}

//获取下标为i的顶点vex的终点
int ListUDG::get_end(vector<int>& vends, int i) {
    while(vends[i] != 0) {
        i = vends[i];
    }
    return i;
}

//测试dijkstra算法
void test_dijkstra(vector<char>& vexs, vector<EdgeData*>& edges) {
    int vexs_len = vexs.size();  //顶点的数量
    vector<int> prev(vexs_len, 0);
    vector<int> dist(vexs_len, 0);  //保存最小距离
    ListUDG* p_grapth = new ListUDG(vexs, edges);
    p_grapth->dijkstra(3, prev, dist);
}

//测试图的遍历
void test_traversal(vector<char>& vexs, vector<EdgeData*>& edges) {
    ListUDG* p_grapth = new ListUDG(vexs, edges);
    p_grapth->dfs();
    p_grapth->bfs();
    p_grapth->print();
}

//测试prim算法
void test_prim(vector<char>& vexs, vector<EdgeData*>& edges) {
    ListUDG* p_grapth = new ListUDG(vexs, edges);
    p_grapth->prim(0);
}

//测试kruskal算法
void test_kruskal(vector<char>& vexs, vector<EdgeData*>& edges) {
    ListUDG* p_grapth = new ListUDG(vexs, edges);
    p_grapth->kruskal();
}

int main()
{
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
    // test_dijkstra(vexs, edges);
    // test_traversal(vexs, edges);
    // test_prim(vexs, edges);
    test_kruskal(vexs, edges);
}

