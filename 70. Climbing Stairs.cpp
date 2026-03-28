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





class Solution {
public:
    /**
     * Approach: Dynamic Programming (Tabulation)
     * -----------------------------------------
     * We use a vector 't' to store the number of ways to reach each step.
     * This "bottom-up" approach builds the solution for 'n' by solving
     * all sub-problems from 1 to n-1 first.
     *
     * Time Complexity: O(n)
     * We fill the table exactly once in a single linear pass.
     *
     * Space Complexity: O(n)
     * We allocate a vector of size n+1 to store the intermediate results.
     */
    int climbStairs(int n) {
        // Handle small inputs directly to avoid out-of-bounds errors 
        // when initializing the vector.
        if (n == 1 || n == 2)
            return n;
        
        // t[i] will represent the total ways to climb to the i-th stair.
        vector<int> t(n + 1);
        
        /**
         * Base Cases:
         * t[1]: Only one way (1 step).
         * t[2]: Two ways (1+1 or 2).
         * Note: t[0] is mathematically 0 here as we start counting from step 1.
         */
        t[0] = 0; 
        t[1] = 1;
        t[2] = 2;
        
        /**
         * State Transition:
         * To reach step 'i', you must have come from step 'i-1' or 'i-2'.
         */
        for (int i = 3; i <= n; i++) {
            t[i] = t[i - 1] + t[i - 2];
        }
        
        // The last element in our table is the answer for 'n' stairs.
        return t[n];
    }
};





class Solution {
public:
    /**
     * Approach: Three-Variable State Tracking
     * --------------------------------------
     * Instead of an array, we use three variables (a, b, c) to represent 
     * the steps. 'a' and 'b' are the two previous steps, and 'c' is the 
     * current step being calculated.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int climbStairs(int n) {
        // Base cases for small n
        if(n == 1 || n == 2 || n == 3)
            return n;
        
        // Initializing the first three steps of the sequence
        int a = 1; // Ways to reach step 1
        int b = 2; // Ways to reach step 2
        int c = 3; // Ways to reach step 3
        
        /**
         * The loop starts from 3. Note that in the first iteration (i=3), 
         * c is recalculated as 1 + 2 = 3. 
         * In the next iteration (i=4), c becomes 2 + 3 = 5, and so on.
         */
        for(int i = 3; i <= n; i++) {
            // Calculate the current step based on the previous two
            c = a + b;
            
            // Move the window forward manually:
            // The old 'b' becomes the new 'a' (two steps back)
            // The new 'c' becomes the new 'b' (one step back)
            int temp_b = b;
            b = c;
            a = temp_b;
        }
        
        // After the loop, c represents the total ways for step n
        return c;
    }
};
