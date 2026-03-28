class Solution {
public:
    // Standard 4-directional movement
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    /**
     * Approach: Reverse DFS (Flowing Uphill)
     * -------------------------------------
     * We start from the ocean boundaries and traverse "uphill."
     * If the next cell is taller than or equal to the current cell, 
     * water from that tall cell could eventually flow down to this ocean.
     *
     * Time Complexity: O(M * N)
     * Each cell is visited at most twice (once for Pacific, once for Atlantic).
     *
     * Space Complexity: O(M * N)
     * Used for the two visited matrices and the recursion stack.
     */
    void DFS(vector<vector<int>>& heights, int i, int j, int prevCellVal, vector<vector<bool>>& visited) {
        // 1. Boundary check
        if(i < 0 || i >= heights.size() || j < 0 || j >= heights[0].size()) {
            return;
        }

        /**
         * 2. Uphill Check: If the current cell is SHORTER than the previous one, 
         * water cannot flow from here to the ocean.
         * 3. Cycle Check: If already visited, stop.
         */
        if(heights[i][j] < prevCellVal || visited[i][j])
            return;

        // Mark as reachable by the current ocean
        visited[i][j] = true;

        for(auto &dir : directions) {
            int i_ = i + dir[0];
            int j_ = j + dir[1];
            // Pass the current cell's height as the 'previous' value for the next call
            DFS(heights, i_, j_, heights[i][j], visited);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty()) return {};
        
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int>> result;

        // Tracks cells that can reach the Pacific (Top and Left edges)
        vector<vector<bool>> pacificVisited(m, vector<bool>(n, false));
        // Tracks cells that can reach the Atlantic (Bottom and Right edges)
        vector<vector<bool>> atlanticVisited(m, vector<bool>(n, false));

        /**
         * Step 1: Start DFS from the Horizontal Boundaries
         * - Top row (Pacific)
         * - Bottom row (Atlantic)
         */
        for(int j = 0; j < n; j++) {
            DFS(heights, 0, j, INT_MIN, pacificVisited);
            DFS(heights, m - 1, j, INT_MIN, atlanticVisited);
        }

        /**
         * Step 2: Start DFS from the Vertical Boundaries
         * - Left column (Pacific)
         * - Right column (Atlantic)
         */
        for(int i = 0; i < m; i++) {
            DFS(heights, i, 0, INT_MIN, pacificVisited);
            DFS(heights, i, n - 1, INT_MIN, atlanticVisited);
        }

        /**
         * Step 3: Intersection
         * If a cell is marked in both matrices, water can flow to both oceans.
         */
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(pacificVisited[i][j] && atlanticVisited[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};
