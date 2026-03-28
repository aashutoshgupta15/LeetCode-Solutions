class Solution {
public:
    int m, n;

    /**
     * Helper: Standard DFS to sink connected land.
     * ------------------------------------------
     * This turns all reachable land (1) into water (0).
     */
    void dfs(vector<vector<int>> &grid, int r, int c) {
        // Boundary check and water check
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0)
            return;

        // "Sink" the land to prevent re-visiting
        grid[r][c] = 0;

        // Spread in 4 directions
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
    }

    /**
     * Approach: Boundary Sinking (Two-Pass)
     * ------------------------------------
     * 1. Traverse all land cells on the four boundaries.
     * 2. For each boundary land cell, trigger DFS to sink the entire 
     * connected island. These are NOT enclaves because they touch the edge.
     * 3. Count the remaining land cells. These are the "enclaves."
     *
     * Time Complexity: O(M * N)
     * Space Complexity: O(M * N) for the recursion stack.
     */
    int numEnclaves(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // Pass 1: Handle Left and Right boundaries
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 1) {
                dfs(grid, i, 0);
            }
            if (grid[i][n - 1] == 1) {
                dfs(grid, i, n - 1);
            }
        }

        // Pass 1 (continued): Handle Top and Bottom boundaries
        for (int i = 0; i < n; ++i) {
            if (grid[0][i] == 1) {
                dfs(grid, 0, i);
            }
            if (grid[m - 1][i] == 1) {
                dfs(grid, m - 1, i);
            }
        }

        // Pass 2: Count the survivors (land that couldn't reach the boundary)
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    count += 1;
                }
            }
        }

        return count;
    }
};
