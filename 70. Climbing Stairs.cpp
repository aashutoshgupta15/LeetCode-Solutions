class Solution {
public:
    /**
     * Approach: Dynamic Programming (Space Optimized)
     * ---------------------------------------------
     * To reach step 'n', you could have come from step 'n-1' (1-step jump)
     * or step 'n-2' (2-step jump). Thus: f(n) = f(n-1) + f(n-2).
     *
     * This is identical to the Fibonacci sequence.
     *
     * Time Complexity: O(n)
     * We iterate from 2 to n once.
     *
     * Space Complexity: O(1)
     * We only store the ways to reach the previous two steps.
     */
    int climbStairs(int n) {
        // Base cases: 
        // 0 stairs = 1 way (staying put)
        // 1 stair = 1 way (one 1-step jump)
        if(n == 0 || n == 1) return 1;

        // prev2 represents f(i-2), prev represents f(i-1)
        int prev2 = 1;
        int prev = 1;

        for(int i = 2; i <= n; i++){ 
            // The number of ways to reach the current step
            int curr = prev2 + prev;
            
            // Shift the window forward for the next iteration
            prev2 = prev;
            prev = curr;
        }

        // After the loop, 'prev' holds the value for step 'n'
        return prev;
    }
};
