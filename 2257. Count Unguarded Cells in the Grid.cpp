class Solution {
public:
    /**
     * Approach: Grid Simulation (Directional Traversal)
     * ------------------------------------------------
     * 1. Create a 2D grid and mark positions of Guards (2) and Walls (3).
     * 2. For each Guard, traverse in four directions (Up, Down, Left, Right).
     * 3. Stop traversing in a direction if we hit a Wall (3) or another Guard (2).
     * 4. Mark cells in the line of sight as Guarded (1).
     * 5. Count the remaining '0' (Unguarded) cells.
     *
     * Time Complexity: O(m * n + G * (m + n)) 
     * Where G is the number of guards. In the worst case, it's O(m * n).
     *
     * Space Complexity: O(m * n) 
     * For the 2D grid storage.
     */

    void markGaurded(int row, int col, vector<vector<int>>& grid) {
        // UP: Iterate upwards until boundary or obstacle
        for(int i = row - 1; i >= 0; i--) {
            if(grid[i][col] == 2 || grid[i][col] == 3) break; 
            grid[i][col] = 1; // Mark as guarded
        }

        // DOWN: Iterate downwards
        for(int i = row + 1; i < grid.size(); i++) {
            if(grid[i][col] == 2 || grid[i][col] == 3) break;
            grid[i][col] = 1;
        }

        // LEFT: Iterate leftwards
        for(int j = col - 1; j >= 0; j--) {
            if(grid[row][j] == 2 || grid[row][j] == 3) break;
            grid[row][j] = 1;
        }

        // RIGHT: Iterate rightwards
        for(int j = col + 1; j < grid[0].size(); j++) {
            if(grid[row][j] == 2 || grid[row][j] == 3) break;
            grid[row][j] = 1;
        }
    }

    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        // grid[i][j]: 0=Empty, 1=Guarded, 2=Guard, 3=Wall
        vector<vector<int>> grid(m, vector<int>(n, 0));

        // Mark guards' fixed positions
        for(vector<int>& vec : guards) {
            grid[vec[0]][vec[1]] = 2;
        }

        // Mark walls' fixed positions
        for(vector<int>& vec : walls) {
            grid[vec[0]][vec[1]] = 3;
        }

        // For every guard, project their line of sight in 4 directions
        for(vector<int>& gaurd : guards) {
            markGaurded(gaurd[0], gaurd[1], grid);
        }

        int count = 0;
        // Count cells that remained 0 (not a guard, wall, or guarded)
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    count++;
                }
            }
        }

        return count;
    }
};





class Solution {
public:
    /**
     * Approach: Directional DFS (Recursive Simulation)
     * ----------------------------------------------
     * Instead of using nested loops for each direction, this approach uses 
     * recursion to "propagate" the guard's line of sight until it hits an 
     * obstacle (another guard or a wall).
     *
     * Time Complexity: O(m * n)
     * Even though we call DFS many times, each cell is only processed 
     * a constant number of times across all directions.
     *
     * Space Complexity: O(m * n) 
     * Due to the grid and the recursive call stack (which can go up to 
     * max(m, n) deep).
     */
    void dfs(vector<vector<int>>& grid, int row, int col, int rows, int cols, int direction) {
        // Boundary check: Stop if out of bounds.
        // Obstacle check: Stop if we hit a Guard (1) or a Wall (2).
        if (row < 0 || col < 0 || row >= rows || col >= cols || grid[row][col] == 1 || grid[row][col] == 2) {
            return;
        }

        // Note: We do NOT stop if grid[row][col] == 3 (already guarded). 
        // We continue so this guard's line of sight can potentially cover 
        // cells further down the line.

        // Mark the current cell as Guarded (3)
        grid[row][col] = 3;

        // Continue moving in the SAME direction
        if (direction == 1) {        // UP
            dfs(grid, row - 1, col, rows, cols, direction);
        } else if (direction == 2) { // DOWN
            dfs(grid, row + 1, col, rows, cols, direction);
        } else if (direction == 3) { // LEFT
            dfs(grid, row, col - 1, rows, cols, direction);
        } else {                     // RIGHT
            dfs(grid, row, col + 1, rows, cols, direction);
        }
    }

    int countUnguarded(int rows, int cols, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        // grid values: 0 = Empty, 1 = Guard, 2 = Wall, 3 = Guarded
        vector<vector<int>> grid(rows, vector<int>(cols, 0));

        // Place Guards
        for (const auto& guard : guards) {
            grid[guard[0]][guard[1]] = 1;
        }

        // Place Walls
        for (const auto& wall : walls) {
            grid[wall[0]][wall[1]] = 2;
        }

        // Trigger DFS from every guard position in all 4 cardinal directions
        for (const auto& guard : guards) {
            int guardRow = guard[0];
            int guardCol = guard[1];

            dfs(grid, guardRow - 1, guardCol, rows, cols, 1); // Start UP
            dfs(grid, guardRow + 1, guardCol, rows, cols, 2); // Start DOWN
            dfs(grid, guardRow, guardCol - 1, rows, cols, 3); // Start LEFT
            dfs(grid, guardRow, guardCol + 1, rows, cols, 4); // Start RIGHT
        }

        // Final tally: count cells that were never reached by DFS
        int unguardedCount = 0;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 0) {
                    ++unguardedCount;
                }
            }
        }

        return unguardedCount;
    }
};
