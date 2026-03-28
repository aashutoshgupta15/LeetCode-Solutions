class Solution {
public:
    /**
     * Helper: Boundary Check
     * ---------------------
     * Ensures we stay within the grid limits.
     */
    bool isvalid(int i, int j, int m, int n) {
        if (i == m || j == n || j < 0 || i < 0)
            return false;
        return true;
    }
    
    // 4-directional movement: Down, Right, Left, Up
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
    
    /**
     * Approach: Multi-Source Breadth-First Search (BFS)
     * ------------------------------------------------
     * 1. Initialize a 'dis' matrix with -1 (representing unvisited).
     * 2. Push all cells containing '0' into a queue and set their distance to 0.
     * 3. Perform BFS. Since all '0's start in the queue at level 0, the first 
     * time we reach a '1', we've found its shortest distance to a '0'.
     *
     * Time Complexity: O(M * N)
     * Each cell is pushed and popped from the queue exactly once.
     *
     * Space Complexity: O(M * N)
     * To store the 'dis' matrix and the BFS queue.
     */
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        queue<pair<int, int>> q;
        int m = matrix.size();
        int n = matrix[0].size();
        
        // 'dis[i][j]' stores the shortest distance to the nearest 0.
        // Initialized to -1 to track unvisited cells.
        vector<vector<int>> dis(m, vector<int>(n, -1));
        
        /**
         * Step 1: Add all sources (0s) to the queue.
         * We start the search from all zeros simultaneously.
         */
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) { 
                    q.push({i, j});
                    dis[i][j] = 0;
                }
            }
        }
        
        /**
         * Step 2: Level-order traversal.
         * Each neighbor of a cell in the queue is 1 unit further 
         * away from the nearest 0.
         */
        while(!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            
            for(auto& x : dir) {
                int a = curr.first + x[0];
                int b = curr.second + x[1];
                
                // If the neighbor is valid and hasn't been visited yet
                if(isvalid(a, b, m, n) && dis[a][b] == -1) {
                    // Update distance: current distance + 1
                    dis[a][b] = dis[curr.first][curr.second] + 1;
                    q.push({a, b});
                }
            }
        }
        
        return dis;
    }
};
