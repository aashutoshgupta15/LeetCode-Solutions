/**
 * Global directions array to simplify 4-directional movement.
 * {0, 1} -> Right, {0, -1} -> Left, {1, 0} -> Down, {-1, 0} -> Up.
 */
static const vector<vector<int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
public:
    int m = 0; // Number of rows
    int n = 0; // Number of columns

    /**
     * Approach: DFS with Memoization (Top-Down DP)
     * -------------------------------------------
     * We treat the matrix as a Directed Acyclic Graph (DAG). An edge exists 
     * from cell A to cell B if B is adjacent to A and B > A.
     *
     * Time Complexity: O(M * N)
     * Each cell is visited once and its result is stored in 'store'.
     *
     * Space Complexity: O(M * N)
     * Used for the 'store' matrix and the recursion stack.
     */
    int solve(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& store) {
        
        // Memoization Check: If we already calculated the path starting 
        // from (i, j), return the cached value.
        if(store[i][j] != 0)
            return store[i][j];
        
        // Every cell is a path of at least length 1.
        int maxL = 1;

        // Explore all 4 neighbors
        for(const vector<int>& dir : directions) {
            int _i = i + dir[0];
            int _j = j + dir[1];
            
            // Validation:
            // 1. Stay within matrix boundaries.
            // 2. Only move if the next cell is STRICTLY GREATER than the current.
            if(_i < 0 || _j < 0 || _i >= m || _j >= n || matrix[i][j] >= matrix[_i][_j])
                continue;
            
            // Recursive Call: The path starting at (i,j) is 1 + the longest 
            // path starting from the neighbor (_i, _j).
            int len = 1 + solve(_i, _j, matrix, store);
            maxL = max(maxL, len);
        }
        
        // Store the calculated result in the cache before returning.
        return store[i][j] = maxL;
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        
        m = matrix.size();
        n = matrix[0].size();
        
        // store[i][j] caches the longest increasing path length starting at (i, j).
        vector<vector<int>> store(m, vector<int>(n, 0));
        
        int result = 0;
        
        // We must attempt a DFS from every single cell because any cell 
        // could be the start of the globally longest path.
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int len = solve(i, j, matrix, store);
                result = max(result, len);
            }
        }
        
        return result;
    }
};
