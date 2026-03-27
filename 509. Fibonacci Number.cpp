class Solution {
public:
    /**
     * Approach: Iterative DP with Space Optimization (Sliding Window)
     * ------------------------------------------------------------
     * The Fibonacci sequence follows: F(n) = F(n-1) + F(n-2).
     * Since we only ever need the two previous numbers to calculate the next,
     * we can use a small fixed-size vector to shift values forward.
     *
     * Time Complexity: O(n)
     * We iterate from 2 up to n exactly once.
     *
     * Space Complexity: O(1)
     * We use a vector of constant size (3), regardless of how large n is.
     */
    int fib(int n) {
        // Base cases: F(0) = 0, F(1) = 1
        if (n < 2)
            return n;

        /**
         * Initializing our sliding window:
         * dp[0] represents F(i-2)
         * dp[1] represents F(i-1)
         * dp[2] represents F(i)
         */
        vector<int> dp{0, 0, 1}; // Note: dp[1] and dp[2] start as F(0) and F(1) logic

        for (int i = 2; i <= n; i++) {
            // Shift values: Move the previous 'current' to the 'old' position
            dp[0] = dp[1]; // Old F(i-1) becomes F(i-2)
            dp[1] = dp[2]; // Old F(i) becomes F(i-1)
            
            // Calculate the new current Fibonacci number
            dp[2] = dp[1] + dp[0]; 
        }

        // The last element in our vector is the result for F(n)
        return dp.back();
    }
};
