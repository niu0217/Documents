/* ************************************************************************
> File Name:     LeetCode200.cpp
> Author:        niu0217
> Created Time:  三  3/13 21:49:21 2024
 ************************************************************************/

//深度优先
class Solution {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        visited[x][y] = true;
        for(int i = 0; i < 4; i++) {
            int nextX = x + dir[i][0];
            int nextY = y + dir[i][1];
            if(nextX < 0 || nextX >= grid.size() || nextY < 0 || nextY >= grid[0].size()) {
                continue;
            }
            if(!visited[nextX][nextY] && grid[nextX][nextY] == '1') {
                visited[nextX][nextY] = true;
                dfs(grid, visited, nextX, nextY);
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    result++;
                    dfs(grid, visited, i, j);
                }
            }
        }
        return result;
    }
};

//广度优先
class Solution {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true;
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            //当前节点的坐标
            int curX = cur.first;
            int curY = cur.second;
            //遍历上下左右的节点
            for(int i = 0; i < 4; i++) {
                int nextX = curX + dir[i][0];
                int nextY = curY + dir[i][1];
                //下表越界处理
                if(nextX < 0 || nextX >= grid.size() || nextY < 0 || nextY >= grid[0].size()) {
                    continue;
                }
                if(!visited[nextX][nextY] && grid[nextX][nextY] == '1') {
                    visited[nextX][nextY] = true;
                    que.push({nextX, nextY});
                }
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    result++;
                    bfs(grid, visited, i, j);
                }
            }
        }
        return result;
    }
};
