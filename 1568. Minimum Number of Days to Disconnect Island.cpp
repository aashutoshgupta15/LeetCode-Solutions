class Solution {
public:
    // 4-directional movement: Up, Down, Left, Right
    vector<vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m;
    int n;

    /**
     * Helper: Standard DFS to traverse a connected component (island).
     */
    void DFS(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited) {
        if(i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] == 0)
            return;
        
        visited[i][j] = true; // Mark current land cell as visited

        for(auto& dir : directions) {
            DFS(grid, i + dir[0], j + dir[1], visited);
        }
    }

    /**
     * Helper: Counts the number of distinct islands in the current grid state.
     */
    int numberOfIslandsDFS(vector<vector<int>>& grid) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int islands = 0;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // If we find unvisited land, it's the start of a new island
                if(!visited[i][j] && grid[i][j] == 1) {
                    DFS(grid, i, j, visited);
                    islands += 1;
                }
            }
        }
        return islands;
    } 

    /**
     * Approach: Case-by-Case Check (0, 1, or 2 days)
     * ---------------------------------------------
     * 1. If the grid is already disconnected (islands != 1), return 0.
     * 2. Try removing every single land cell one by one. If any removal 
     * disconnects the island, return 1.
     * 3. If neither works, it's mathematically proven that 2 removals 
     * will always suffice for a 2D grid.
     *
     * Time Complexity: O((M*N)^2) - We call DFS (O(M*N)) for every land cell.
     * Space Complexity: O(M*N) - For the visited matrix and recursion stack.
     */
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        // Initial check: is it already disconnected?
        int islands = numberOfIslandsDFS(grid);
        if (islands > 1 || islands == 0) {
            return 0;
        } 

        // Brute force: Try removing each land cell (i, j)
        for (int i = 0 ; i < m; i ++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0; // Temporarily remove land
                    
                    // Check if this single removal disconnected the island
                    islands = numberOfIslandsDFS(grid);
                    
                    grid[i][j] = 1; // Backtrack (restore land)
                    
                    if (islands > 1 || islands == 0)
                        return 1;
                }
            }
        }

        /** * If we couldn't disconnect it with 0 or 1 removal, the answer is 2.
         * Example: A corner cell has only two neighbors; removing them 
         * always isolates the corner.
         */
        return 2; 
    }
};
