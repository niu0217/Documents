# graph

## 1. 问题

## 2. 外部资料

b站视频：

https://www.bilibili.com/video/BV1km4y1b7zr/?spm_id_from=333.337.search-card.all.click&vd_source=c6838f09fbfc9766e04f0c65ca196c42

文章：

https://www.freecodecamp.org/chinese/news/dijkstras-shortest-path-algorithm-visual-introduction/

https://zq99299.github.io/dsalg-tutorial/dsalg-java-hsp/13/02.html#%E9%82%BB%E6%8E%A5%E7%9F%A9%E9%98%B5

## 3. 基础知识

### 3.1 引入

图论是数学的一个分支，它以图为研究对象。图论中的图是由若干给定的点及连接两点的线所构成的图形，这种图形通常用来描述某些事物之间的某种特定关系，用点代表事物，用连接两点的线表示相应两个事物间具有这种关系。下面是一些图的基本知识：

1. 图的定义：图G由顶点集V和边集E组成，记为G = (V, E)，其中V(G)表示图G中顶点的有限非空集；E(G)表示图G中顶点之间的关系（边）集合。若V={v1,v2,…,vn}，则用|V|表示图G中顶点的个数，也称图G的阶，E={(u,v)|u∈V,v∈V}，用|E|表示图G中边的条数。
2. 有向图：若E是有向边（也称弧）的有限集合时，则图G为有向图。弧是顶点的有序对，记为<v,w>，其中v、w是顶点，v称为弧尾，w称为弧头，<v,w>称为从顶点v到顶点w的弧，也称v邻接到w，或w邻接自v。
3. 无向图：若E是无向边（简称边）的有限集合时，则图G为无向图。边是顶点的无序对，记为(v,w)或(w,v)，因为(v,w)=(w,v)，其中v、w是顶点。可以说顶点v和顶点w互为邻接点。边(v,w)依附于顶点v和w，或者说边(v,w)与顶点v、w相关联。
4. 完全图：每一对不同的顶点都有一条边相连的简单图称为完全图。n个顶点的完全图记为Kn。
5. 子图：设有两个图G=(V,E)和G'=(V',E')，若V'是V的子集，且E'是E的子集，则称G'是G的子图。
6. 路径：在图G=(V,E)中，若从顶点vi出发，沿一些边经过一些顶点vp1,vp2,…,vpn-1，到达顶点vj，则称顶点序列(vi,vp1,vp2,…,vpn-1,vj)为从顶点vi到vj的路径。
7. 连通性：在无向图中，如果从顶点vi到顶点vj有路径，则称vi和vj是连通的。如果图中任意两个顶点之间都是连通的，则称图是连通图。
8. 图的表示：图的表示方法有多种，常用的有邻接矩阵和邻接表两种。邻接矩阵是一个二维数组，表示图中各顶点之间的关系；邻接表则是由链表组成的表结构，每个链表对应一个顶点，链表中的元素表示与该顶点相邻接的顶点。

### 3.2 图的表示方式

https://zq99299.github.io/dsalg-tutorial/dsalg-java-hsp/13/02.html#%E9%82%BB%E6%8E%A5%E7%9F%A9%E9%98%B5

### 3.3 图的遍历

https://www.cxyxiaowu.com/9854.html

#### 3.3.1 深度优先

深度优先遍历是一种用于遍历或搜索树或图的算法。这个算法会尽可能深地搜索图的分支。当节点v的所在边都已被探寻过，搜索将回溯到发现节点v的那条边的起始节点。这一过程一直进行到已发现从源节点可达的所有节点为止。如果还存在未被发现的节点，则选择其中一个作为源节点并重复以上过程，整个进程反复进行直到所有节点都被访问为止。

深度优先遍历的特点：

+ 深度优先遍历可能会访问到图的深处，然后再回溯访问其他分支。 

* 它使用栈（Stack）数据结构来保存需要回溯的节点。
*  在非连通图中，深度优先遍历可以访问到所有可达的节点。

#### 3.3.2 广度优先

广度优先遍历是另一种图遍历算法，它从图的某一顶点出发，首先访问它的所有相邻节点，然后再从这些相邻节点出发，依次访问它们的未被访问过的相邻节点。这个过程会逐层向外扩展，直到访问了所有可达的节点。

广度优先遍历的特点：

+ 广度优先遍历会逐层访问图的节点，先访问离源节点近的节点，再访问离源节点远的节点。

* 它使用队列（Queue）数据结构来保存待访问的节点。
* 在非连通图中，广度优先遍历只能访问到从源节点开始可达的节点，需要多次遍历才能访问到所有节点。

#### 3.3.3 总结

这两种遍历方法在不同的应用场景中有各自的优势。例如，深度优先遍历在寻找图的桥（Bridge）和关节点（Articulation Point）等问题中表现出色，而广度优先遍历在求解最短路径（无权图）和Dijkstra算法等问题中更为实用。

## 4. 最小生成树算法

https://www.cnblogs.com/biyeymyhjob/archive/2012/07/30/2615542.html

最小生成树（Minimum Spanning Tree, MST）算法是一种在图论中常见的算法，它用于在一个加权连通图中找出一个部分图，该部分图是一个包含图中所有顶点的树，并且树上所有边的权值之和最小。这样的树被称为图的最小生成树。

最小生成树算法常用于网络设计、电路设计、数据压缩等领域，因为它可以帮助我们以最小的成本连接所有的节点。

有两种著名的最小生成树算法：

1. **普里姆算法（Prim's Algorithm）**
   普里姆算法从一个顶点开始，每次加入与当前生成树中顶点集合有最小权值连接的顶点，直到所有顶点都被加入。

   步骤：

   - 初始化：选择图中的任一顶点加入生成树集合，将其余顶点视为未访问。
   - 迭代：在未访问的顶点中找出与生成树中任一顶点权值最小的边，将该边的另一个顶点加入生成树集合。
   - 终止：当所有顶点都被访问，或者没有更多的边可以加入生成树时算法结束。

2. **克鲁斯卡尔算法（Kruskal's Algorithm）**
   克鲁斯卡尔算法则按照边的权值大小顺序选择边，每次选择一条连接两个未连接顶点的最小权值边，直到所有顶点都被连接。

   步骤：

   - 初始化：将图中的所有边按照权值大小排序。
   - 迭代：从权值最小的边开始，依次检查每条边。如果该边的两个顶点没有被连接（即不会形成环），则添加这条边到生成树中，并将这两个顶点连接。
   - 终止：当生成树中包含所有顶点时，算法结束。

两种算法的正确性都基于图的性质，特别是切分定理和环的性质。在实际应用中，选择哪种算法取决于具体问题的特点和需求，例如图的稀疏性或稠密性，以及是否需要容易实现或者更高效的算法。

在实际编码时，通常需要使用一些辅助数据结构来提高算法的效率，例如优先队列（用于Prim算法）或并查集（用于Kruskal算法）。

## 5. 代码

### 5.1 Dijkstra

https://www.cnblogs.com/skywang12345/p/3711514.html

邻接矩阵：

[dijkstra_matrix.cpp](https://github.com/niu0217/Documents/blob/main/C%2B%2B/datastructure/code/dijkstra_matrix.cpp)

邻接表：

[dijkstra_list.cpp](https://github.com/niu0217/Documents/blob/main/C%2B%2B/datastructure/code/dijkstra_list.cpp)

![IMG_2197](graph.assets/IMG_2197.jpg) 

### 5.2 图的其他算法和遍历

邻接矩阵实现：

[grapth_matrix.cpp](https://github.com/niu0217/Documents/blob/main/C%2B%2B/datastructure/code/grapth_matrix.cpp)

邻接表实现：

[grapth_list.cpp](https://github.com/niu0217/Documents/blob/main/C%2B%2B/datastructure/code/grapth_list.cpp)













 

