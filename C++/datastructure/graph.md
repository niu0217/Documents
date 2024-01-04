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

## 4. 代码

### 4.1 Dijkstra

https://www.cnblogs.com/skywang12345/p/3711514.html

邻接矩阵：

[dijkstra_matrix.cpp](https://github.com/niu0217/Documents/blob/main/C%2B%2B/datastructure/code/dijkstra_matrix.cpp)

邻接表：

