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

//管理图的类
class MatrixUDG {
public:
    //构造和析构函数
    MatrixUDG() { }
    MatrixUDG(vector<char>& vexs, vector<vector<int>>& matrix);

    //算法
    void dijkstra(int vex, vector<int>& prev, vector<int>& dist); //dijkstra算法

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

//测试dijkstra算法
void test_dijkstra() {
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
    int vexs_len = vexs.size();  //顶点的数量
    vector<int> prev(vexs_len, 0);
    vector<int> dist(vexs_len, 0);  //保存最小距离
    MatrixUDG* p_grapth = new MatrixUDG(vexs, matrix);
    p_grapth->dijkstra(3, prev, dist);
}

int main()
{
    test_dijkstra();
}

