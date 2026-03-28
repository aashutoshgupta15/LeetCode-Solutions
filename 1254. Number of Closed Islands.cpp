class Solution {
public:
    int m, n;

    /**
     * Approach: Boundary-Aware DFS
     * ---------------------------
     * A closed island is a group of 0s (land) completely surrounded by 1s (water).
     * If an island's land touches the edge of the grid, it is NOT closed.
     *
     * Time Complexity: O(M * N) - Each cell is visited at most once.
     * Space Complexity: O(M * N) - Due to the recursive call stack in the worst case.
     */
    bool dfs(vector<vector<int>> &grid, int r, int c) {
        
        // If we go out of bounds, this island is NOT closed.
        if (r < 0 || r >= m || c < 0 || c >= n)
            return false;
        
        // If we hit water (1), it acts as a valid boundary for a closed island.
        if (grid[r][c] == 1)
            return true;
        
        // Mark the land as visited by turning it into water (1).
        // This prevents infinite loops and ensures we don't count it again.
        grid[r][c] = 1;
        
        // Explore all four directions.
        // We MUST call all four before returning to ensure the whole island is marked.
        bool left  = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);
        bool up    = dfs(grid, r - 1, c);
        bool down  = dfs(grid, r + 1, c);
        
        // An island is closed ONLY if all directions are bounded by water (1)
        // and none of them leaked out of the grid boundaries.
        return left && right && up && down;
    }
    
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // When we find land (0), start a DFS to see if it's closed.
                if (grid[i][j] == 0) {
                    // If dfs returns true, it's a closed island.
                    if (dfs(grid, i, j)) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};
