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

//管理图的类
class MatrixUDG {
public:
    //构造和析构函数
    MatrixUDG() { }
    MatrixUDG(vector<char>& vexs, vector<vector<int>>& matrix);

    //遍历图
    void dfs();  //深度优先遍历图
    void bfs(); //广度优先遍历图
    void dfs_traversal(int vex_index, vector<int>& visited);  //辅助函数：深度优先遍历图(递归)
    int first_adjacent_vex(int vex_index);  //辅助函数：返回顶点vex的第一个邻接顶点的索引
    //辅助函数：返回顶点vex从adjvex_index + 1开始的第一个邻接顶点的索引
    int next_adjacent_vex(int vex_index, int adjvex_index);

    //算法
    void dijkstra(int vex, vector<int>& prev, vector<int>& dist); //dijkstra算法
    void prim(int vex_index);  //prim算法
    void kruskal(); //kruskal算法

    //其余操作
    void print(); //打印矩阵图
    int get_position(char vex); //返回vex在m_vexs中的位置
    EdgeData* get_edges(); //获取图中的所有边
    void sort_edges(EdgeData* p_edges); //对边按照权值大小进行排序
    int get_end(vector<int>& vends, int index); //获取index的终点

private:
    vector<char> m_vexs;  //顶点集合
    int m_vexs_num;  //顶点数
    int m_edge_num = 0; //边数
    vector<vector<int>> m_matrix;  //邻接矩阵
};

//构造函数: 创建图(用已提供的矩阵)
//参数说明:
//  vexs: 图的顶点
//  matrix: 图的邻接矩阵
MatrixUDG::MatrixUDG(vector<char>& vexs, vector<vector<int>>& matrix) {
    m_vexs_num = vexs.size();  //初始化顶点数
    m_vexs = vexs;  //初始化顶点
    m_matrix = matrix;  //初始化边
    for(int i = 0; i < m_vexs_num; i++) {
        for(int j = 0; j < m_vexs_num; j++) {
            if(i != j && m_matrix[i][j] != INF) {
                m_edge_num++;
            }
        }
    }
    m_edge_num /= 2;  //初始化边数
}

//深度优先遍历图
void MatrixUDG::dfs() {
    vector<int> visited(m_vexs_num, 0);
    cout<<"DFS: ";
    for(int i = 0; i < m_vexs_num; i++) {
        //如果这个顶点没有被访问，则递归遍历并访问
        if(!visited[i]) {
            dfs_traversal(i, visited);
        }
    }
    cout<<endl;
}

//广度优先遍历图
void MatrixUDG::bfs() {
    queue<int> que_vex_index; //用于保存顶点下标的队列
    vector<int> visited(m_vexs_num, 0); //顶点访问标记
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
                visited[vex_index] = 1;
                cout<<m_vexs[vex_index]<<" ";
            }
            //顶点vex的第一个邻接顶点的索引
            int adjvex_index = first_adjacent_vex(vex_index);
            //依次访问顶点vex的邻接顶点
            for(; adjvex_index >= 0; adjvex_index = next_adjacent_vex(vex_index, adjvex_index)) {
                //邻接顶点adjvex_index没有被访问
                if(!visited[adjvex_index]) {
                    visited[adjvex_index] = 1;
                    cout<<m_vexs[adjvex_index]<<" ";
                    que_vex_index.push(adjvex_index);
                }
            }
        }
    }
    cout<<endl;
}


//辅助函数：从顶点vex开始，深度遍历图
//          并将遍历过的顶点标记为1保存在visited中
//参数说明：
//  vex_index: 需要遍历的顶点vex的下标
//  visited: 保存哪些顶点已经被访问过了
void MatrixUDG::dfs_traversal(int vex_index, vector<int>& visited) {
    int adjvex_index; //保存顶点vex的邻接顶点索引
    visited[vex_index] = 1; //标记顶点vex已经访问过了
    cout<<m_vexs[vex_index]<<" ";
    //遍历顶点vex的所有邻接顶点，如果没有访问过，那么继续
    adjvex_index = first_adjacent_vex(vex_index);
    for(; adjvex_index >= 0; adjvex_index = next_adjacent_vex(vex_index, adjvex_index)) {
        if(!visited[adjvex_index]) {
            dfs_traversal(adjvex_index, visited);
        }
    }
}

//辅助函数：返回顶点vex的第一个邻接顶点的索引
//          不存在则返回-1
int MatrixUDG::first_adjacent_vex(int vex_index) {
    //检查下标的合理性
    if(vex_index < 0 || vex_index > (m_vexs_num - 1)) {
        return -1;
    }
    //开始遍历
    for(int i = 0; i < m_vexs_num; i++) {
        if(m_matrix[vex_index][i] != 0 && m_matrix[vex_index][i] != INF) {
            return i;
        }
    }
    return -1;
}

//辅助函数：返回顶点vex从adjvex_index + 1开始的第一个邻接顶点的索引
//          失败返回-1
int MatrixUDG::next_adjacent_vex(int vex_index, int adjvex_index) {
    //检查下标的合理性
    if(vex_index < 0 || vex_index > (m_vexs_num - 1) ||
        adjvex_index < 0 || adjvex_index > (m_vexs_num - 1)) {
        return -1;
    }
    //开始遍历
    for(int i = adjvex_index + 1; i < m_vexs_num; i++) {
        if(m_matrix[vex_index][i] != 0 && m_matrix[vex_index][i] != INF) {
            return i;
        }
    }
    return -1;
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
void MatrixUDG::dijkstra(int vex, vector<int>& prev, vector<int>& dist) {
    int min_value;
    int temp;
    int k;
    //flags[i]=1表示“顶点vex"到"顶点i"的最短路径已经成功获取
    vector<int> flags(m_vexs_num, 0);
    //初始化dist
    for(int i = 0; i < m_vexs_num; i++) {
        dist[i] = m_matrix[vex][i];  //顶点i的最短路径为"顶点vex"到"顶点i"的权
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
            temp = (m_matrix[k][j] == INF ? INF : (min_value + m_matrix[k][j]));
            if(flags[j] == 0 && (temp < dist[j])) {
                dist[j] = temp;
                prev[j] = k;
            }
        }
    }
    //打印dijkstra最短路径的结果
    cout<<"dijkstra("<<m_vexs[vex]<<"):  "<<endl;
    for(int i = 0; i < m_vexs_num; i++) {
        cout<<"  shortest("<<m_vexs[vex]<<", "<<m_vexs[i]<<")="<<dist[i]<<endl;
    }
}

//prim最小生成树
//参数说明：
//  vex_index: 从图中的顶点vex开始，生成最小树，vex_index表示
//             顶点vex的下标
void MatrixUDG::prim(int vex_index) {
    int min_value;
    int sum = 0; //保存最小生成树的权值和
    int index = 0; //保存prim最小树的索引，即prims数组的索引
    vector<char> prims(m_vexs_num + 1, 0); //prim最小树的结果数组
    vector<int> weights(m_vexs_num, 0);  //顶点间边的权值
    //prim最小生成树中第一个数就是起点
    prims[index++] = m_vexs[vex_index];
    //初始化顶点的权值数组
    //将每个顶点的权值初始化为顶点vex到该顶点的权值
    for(int i = 0; i < m_vexs_num; i++) {
        weights[i] = m_matrix[vex_index][i];
    }
    //将顶点vex的权值设置为0，表示vex到自身的距离为0
    weights[vex_index] = 0; //其实它本来就是0，为了理解所以单独写出来
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
            //如果weights[j] = 0,表示第j个结点已经加入到最小生成树中了
            if(weights[j] != 0 && weights[j] < min_value) {
                min_value = weights[j];
                k = j;
            }
            j++;
        }
        //经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的
        //顶点是第k个顶点。将第k个顶点加入到最小生成树的结果数组中
        prims[index++] = m_vexs[k];
        //将第k个顶点的权值标记为0，表示已经加入了最小树结果中
        weights[k] = 0;
        //当第k个顶点被加入到最小生成树的结果数组中之后，更新
        //其他顶点的权值
        for(j = 0; j < m_vexs_num; j++) {
            //当第j个节点没有被处理，并且需要更新时才被更新
            if(weights[j] != 0 && m_matrix[k][j] < weights[j]) {
                weights[j] = m_matrix[k][j];
            }
        }
    }
    //计算最小生成树的权值
    for(int i = 1; i < index; i++) {
        min_value = INF;
        //获取prims[i]在m_matrix中的位置
        int n = get_position(prims[i]);
        //在vexs[0~i-1]中，找出到i的权值最小的顶点，如果i == j的
        //话，就是自己到自己的距离，没有意义
        for(int j = 0; j < i; j++) {
            int m = get_position(prims[j]);
            if(m_matrix[m][n] < min_value) {
                min_value = m_matrix[m][n];
            }
        }
        sum += min_value;
    }
    //打印最小生成树
    cout<<"PRIM("<<m_vexs[vex_index]<<")="<<sum<<": ";
    for(int i = 0; i < index; i++) {
        cout<<prims[i]<<" ";
    }
    cout<<endl;
}

//克鲁斯卡尔(Kruskal)最小生成树
void MatrixUDG::kruskal() {
    int m;
    int n;
    int begin_index;
    int end_index;
    int index = 0; //vec_result数组的索引
    vector<int> vends(m_vexs_num, 0); //保存已有最小生成树中每个顶点在该最小树中的终点
    vector<EdgeData> vec_result;  //结果数组，保存kruskal最小生成树的边
    EdgeData* p_edges;  //图对应的所有边
    //获取图中所有的边
    p_edges = get_edges();
    //将边按照权从小到大排序
    sort_edges(p_edges);
    for(int i = 0; i < m_edge_num; i++) {
        begin_index = get_position(p_edges[i].start); //获取第i条边的起点的序号
        end_index = get_position(p_edges[i].end); //获取第i条边的终点的序号
        m = get_end(vends, begin_index);  //获取begin_index在已有的最小生成树中的终点
        n = get_end(vends, end_index); //获取end_index在已有的最小生成树中的终点
        //如果m!=n,意味着边i与已经添加到最小生成树中的顶点没有形成环路
        if(m != n) {
            vends[m] = n; //设置m在已有的最小生成树中的终点为n
            vec_result.push_back(p_edges[i]); //保存结果
            index++;
        }
    }
    delete []p_edges; //释放之前动态申请的数组，防止内存泄漏
    //统计并打印kruskal最小生成树的信息
    int length = 0;
    for(int i = 0; i < index; i++) {
        length += vec_result[i].weight;
    }
    cout<<"Kruskal="<<length<<":";
    for(int i = 0; i < index; i++) {
        cout<<"("<<vec_result[i].start<<","<<vec_result[i].end<<") ";
    }
    cout<<endl;
}


void MatrixUDG::print() {
    cout<<"Matrix Grapth: "<<endl;
    for(int i = 0; i < m_vexs_num; i++) {
        for(int j = 0; j < m_vexs_num; j++) {
            cout<<setw(12)<<m_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

//返回顶点vex在数组m_vexs中的位置，不存在则返回-1
int MatrixUDG::get_position(char vex) {
    for(int i = 0; i < m_vexs_num; i++) {
        if(m_vexs[i] == vex) {
            return i;
        }
    }
    return -1;
}

//获取图中的所有边
EdgeData* MatrixUDG::get_edges() {
    int index = 0;
    EdgeData* p_edges;
    p_edges = new EdgeData[m_edge_num];
    //用p_edges保存所有的边
    for(int i = 0; i < m_vexs_num; i++) {
        for(int j = i + 1; j < m_vexs_num; j++) {
            if(m_matrix[i][j] != INF) {
                p_edges[index].start = m_vexs[i];
                p_edges[index].end = m_vexs[j];
                p_edges[index].weight = m_matrix[i][j];
                index++;
            }
        }
    }
    return p_edges;
}

//对边按照权值大小进行排序，从小到大，使用冒泡排序
void MatrixUDG::sort_edges(EdgeData* p_edges) {
    for(int i = 0; i < m_edge_num; i++) {
        for(int j = i + 1; j < m_edge_num; j++) {
            if(p_edges[i].weight > p_edges[j].weight) {
                swap(p_edges[i], p_edges[j]);
            }
        }
    }
}

//获取index的终点
int MatrixUDG::get_end(vector<int>& vends, int index) {
    while(vends[index] != 0) {
        index = vends[index];
    }
    return index;
}

//测试dijkstra算法
void test_dijkstra(vector<char>& vexs, vector<vector<int>>& matrix) {
    int vexs_len = vexs.size();  //顶点的数量
    vector<int> prev(vexs_len, 0);
    vector<int> dist(vexs_len, 0);  //保存最小距离
    MatrixUDG* p_grapth = new MatrixUDG(vexs, matrix);
    p_grapth->dijkstra(3, prev, dist);
}

//测试图的遍历
void test_traversal(vector<char>& vexs, vector<vector<int>>& matrix) {
    MatrixUDG* p_grapth = new MatrixUDG(vexs, matrix);
    p_grapth->print();
    p_grapth->dfs();
    p_grapth->bfs();
}

//测试prim算法
void test_prim(vector<char>& vexs, vector<vector<int>>& matrix) {
    MatrixUDG* p_grapth = new MatrixUDG(vexs, matrix);
    p_grapth->prim(0);
}

//测试Kruskal算法
void test_kruskal(vector<char>& vexs, vector<vector<int>>& matrix) {
    MatrixUDG* p_grapth = new MatrixUDG(vexs, matrix);
    p_grapth->kruskal();
}

int main()
{
    //图的顶点
    vector<char> vexs = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G'
    };
    //图的邻接矩阵
    vector<vector<int>> matrix = {
             /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
      /*A*/ {   0,  12, INF, INF, INF,  16,  14},
      /*B*/ {  12,   0,  10, INF, INF,   7, INF},
      /*C*/ { INF,  10,   0,   3,   5,   6, INF},
      /*D*/ { INF, INF,   3,   0,   4, INF, INF},
      /*E*/ { INF, INF,   5,   4,   0,   2,   8},
      /*F*/ {  16,   7,   6, INF,   2,   0,   9},
      /*G*/ {  14, INF, INF, INF,   8,   9,   0}
    };
    // test_dijkstra(vexs, matrix);
    // test_traversal(vexs, matrix);
    // test_prim(vexs, matrix);
    test_kruskal(vexs, matrix);
}

