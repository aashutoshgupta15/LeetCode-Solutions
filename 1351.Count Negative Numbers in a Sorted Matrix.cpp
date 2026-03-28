class Solution {
public:
    /**
     * Approach: Brute Force (Linear Scan)
     * ----------------------------------
     * We iterate through every row and every column of the matrix, 
     * checking each element to see if it is negative.
     *
     * Time Complexity: O(m * n)
     * Where m is the number of rows and n is the number of columns.
     *
     * Space Complexity: O(1)
     * We only use a single integer to store the count.
     */
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int result = 0;
        
        // Loop through each row
        for(int i = 0; i < m; i++) {
            // Loop through each column in the current row
            for(int j = 0; j < n; j++) {
                
                // If the number is negative, increment the counter
                if(grid[i][j] < 0)
                    result++;
            }
        }
        
        return result;
    }
};





class Solution {
public:
    /**
     * Approach: Binary Search (Row-by-Row)
     * ------------------------------------
     * Since each row is sorted in descending order, we can use binary search
     * to find the "transition point" where numbers change from non-negative to negative.
     *
     * Time Complexity: O(m * log n)
     * We perform a binary search (log n) for each of the 'm' rows.
     *
     * Space Complexity: O(1)
     * We only use a few integer variables.
     */
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int result = 0;
        
        // Iterate through each row (vector) in the grid
        for(auto &vec : grid) {
            
            /**
             * upper_bound with greater<int>():
             * --------------------------------
             * In a descending array, this finds the first element strictly 
             * smaller than the value '0'. 
             * 'idx' becomes the index of the first negative number.
             */
            int idx = upper_bound(begin(vec), end(vec), 0, greater<int>()) - begin(vec);
            
            /**
             * If 'idx' is the start of negative numbers, then all elements
             * from 'idx' to the end of the row (index 'n-1') are negative.
             * Total count = n - idx.
             */
            result += (n - idx);
        }
        
        return result;
    }
};





class Solution {
public:
    /**
     * Approach: Staircase Search (Optimal)
     * -----------------------------------
     * We start from the bottom-left corner (m-1, 0).
     * 1. If grid[row][col] is negative, then all elements to its right 
     * in the same row MUST be negative (since rows are non-increasing).
     * 2. If grid[row][col] is non-negative, then all elements above it 
     * in the same column MUST be non-negative (since columns are non-increasing).
     *
     * Time Complexity: O(m + n)
     * We only move up or right. At most, we take m + n steps.
     *
     * Space Complexity: O(1)
     * No extra data structures are used.
     */
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Start at the bottom-left corner
        int row = m - 1;
        int col = 0;
        int result = 0;
        
        while(row >= 0 && col < n) {
            
            if(grid[row][col] < 0) {
                /**
                 * If the current element is negative, every element from 
                 * this 'col' to the end of the row 'n-1' is also negative.
                 * So we add (n - col) to our result.
                 */
                result += (n - col);
                
                // Move up to the next row to check for more negatives
                row--;
            } else {
                /**
                 * If the current element is positive or zero, we haven't
                 * reached the negative section of this row yet.
                 * Move right to find the first negative.
                 */
                col++;
            }
        }
        
        return result;
    }
};
