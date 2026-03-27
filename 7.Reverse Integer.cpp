class Solution {
public:
    /**
     * Approach: Digit Extraction and Overflow Prevention
     * --------------------------------------------------
     * We reverse the integer by repeatedly popping the last digit and 
     * pushing it to a new result variable. Since the reversed integer 
     * might exceed the 32-bit signed integer range, we check for 
     * overflow before performing the final multiplication and addition.
     *
     * Time Complexity: O(log(x)) 
     * The number of digits in x is roughly log10(x).
     *
     * Space Complexity: O(1)
     * Only a few integer variables are used regardless of input size.
     */
    int reverse(int x) {
        int result = 0;

        while (x != 0) {
            // Extract the last digit (e.g., if x = 123, digit = 3)
            int digit = x % 10;
            
            // Remove the last digit from x (e.g., x becomes 12)
            x /= 10;

            /**
             * Check for Positive Overflow:
             * 1. If result > INT_MAX/10, the next multiplication (result * 10) 
             * will definitely overflow.
             * 2. If result == INT_MAX/10, it only overflows if the next digit 
             * is greater than 7 (since INT_MAX ends in 7).
             */
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) return 0;
            
            /**
             * Check for Negative Overflow:
             * 1. If result < INT_MIN/10, the next multiplication will definitely overflow.
             * 2. If result == INT_MIN/10, it only overflows if the next digit 
             * is less than -8 (since INT_MIN ends in -8).
             */
            if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)) return 0;

            // Push the digit into the result: shift existing digits left and add the new one
            result = result * 10 + digit;
        }
        
        return result;
    }
};
