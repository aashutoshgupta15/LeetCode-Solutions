class Solution {
public:
    // Directions for DFS: Right, Left, Up, Down
    vector<vector<int>> directions{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    /**
     * Helper: Standard DFS to visit all connected '0' cells.
     * ---------------------------------------------------
     * Once a region of 0s is visited, we mark it as 1 to "sink" it.
     */
    void numberOfIslandsDFS(vector<vector<int>>& matrix, int i, int j) {
        if(i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j] == 1)
            return;
        
        matrix[i][j] = 1; // Mark as visited

        for(const auto& dir : directions) {
            int new_i = i + dir[0];
            int new_j = j + dir[1];
            numberOfIslandsDFS(matrix, new_i, new_j);
        }
    }

    /**
     * Approach: Grid Upscaling (3x3 Expansion)
     * ----------------------------------------
     * We convert each character cell into a 3x3 sub-grid:
     * '/'  -> Top-right to bottom-left diagonal of 1s.
     * '\'  -> Top-left to bottom-right diagonal of 1s.
     * ' '  -> All 0s.
     *
     * Time Complexity: O(N^2) - Where N is the side of the original grid. 
     * The expanded matrix is (3N * 3N), which is still O(N^2).
     *
     * Space Complexity: O(N^2) - To store the expanded 3N x 3N matrix.
     */
    int regionsBySlashes(vector<string>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int regions = 0;

        // Create an expanded matrix of size 3*rows x 3*cols
        vector<vector<int>> matrix(rows * 3, vector<int>(cols * 3, 0));

        // Populate the matrix based on slashes
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] == '/') {
                    // Mapping for forward slash '/'
                    matrix[i * 3][j * 3 + 2] = 1;
                    matrix[i * 3 + 1][j * 3 + 1] = 1;
                    matrix[i * 3 + 2][j * 3] = 1;
                } else if(grid[i][j] == '\\') {
                    // Mapping for backslash '\'
                    matrix[i * 3][j * 3] = 1;
                    matrix[i * 3 + 1][j * 3 + 1] = 1;
                    matrix[i * 3 + 2][j * 3 + 2] = 1;
                }
            }
        }

        // Apply "Number of Islands" logic on the empty spaces (0s)
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                if(matrix[i][j] == 0) {
                    // Every time we find a 0, it's a new separate region
                    numberOfIslandsDFS(matrix, i, j);
                    regions += 1;
                }
            }
        }

        return regions;
    }
};
