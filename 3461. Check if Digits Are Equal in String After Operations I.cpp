class Solution {
public:
    /**
     * Approach: Iterative Simulation (In-place Reduction)
     * --------------------------------------------------
     * We repeatedly transform the string by replacing each digit with the 
     * sum of itself and the next digit (mod 10). Each pass reduces the 
     * string length by 1 until only two digits remain.
     *
     * Time Complexity: O(n^2)
     * We perform (n-2) passes, and each pass iterates through the current 
     * length of the string.
     *
     * Space Complexity: O(1) 
     * We modify the input string 's' in-place, using only the first 'n' 
     * characters of the original buffer.
     */
    bool hasSameDigits(string s) {
        int n = s.length();

        // Continue the reduction until only 2 digits are left
        while (n > 2) {

            // Perform one pass of the adjacent summation
            for (int i = 0; i < n - 1; i++) {
                /**
                 * Calculation:
                 * 1. (s[i] - '0') converts char digit to integer.
                 * 2. Add adjacent digits and take % 10.
                 * 3. + '0' converts the resulting integer back to a char.
                 */
                int sum = (s[i] - '0') + (s[i + 1] - '0');
                s[i] = (sum % 10) + '0';
            }

            // Effectively "shrink" the string by ignoring the last character 
            // of the previous pass.
            n--;
        }

        // Check if the final two remaining digits are identical
        return s[0] == s[1];
    }
};
