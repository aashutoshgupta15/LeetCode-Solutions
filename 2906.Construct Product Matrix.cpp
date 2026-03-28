class Solution {
public:
    /**
     * Approach: Two-Pass Prefix & Suffix Products
     * ------------------------------------------
     * To find the product of all elements except grid[i][j], we calculate:
     * (Product of all elements before it) * (Product of all elements after it)
     *
     * We treat the 2D grid as a flattened 1D array during our traversal.
     * * Time Complexity: O(n * m)
     * We traverse the grid twice (once for suffix, once for prefix).
     *
     * Space Complexity: O(1) 
     * Excluding the output matrix, we only use a few long long variables.
     */
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int MOD = 12345;
        int n = grid.size();
        int m = grid[0].size();

        // p will temporarily store suffix products, then the final result
        vector<vector<int>> p(n, vector<int>(m)); 

        /**
         * Pass 1: Suffix Products (Backward Pass)
         * We traverse from the bottom-right to the top-left.
         * p[i][j] stores the product of all elements that come AFTER grid[i][j].
         */
        long long suffix = 1;
        for(int i = n - 1; i >= 0; i--) {
            for(int j = m - 1; j >= 0; j--) {
                p[i][j] = suffix;
                // Update suffix for the next (previous) element
                suffix = (suffix * grid[i][j]) % MOD;
            }
        }

        /**
         * Pass 2: Prefix Products (Forward Pass)
         * We traverse from top-left to bottom-right.
         * We multiply the existing suffix product by the product of all 
         * elements that came BEFORE grid[i][j].
         */
        long long prefix = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // Final result = (prefix product) * (suffix product)
                p[i][j] = (prefix * p[i][j]) % MOD;
                // Update prefix for the next element
                prefix = (prefix * grid[i][j]) % MOD;
            }
        }

        return p;
    }
};
