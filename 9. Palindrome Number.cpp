class Solution {
public:
    /**
     * Approach: Reversing the Second Half
     * ----------------------------------
     * To check if a number is a palindrome, we can reverse the last half 
     * of the digits and compare it with the first half.
     *
     * Why half? 
     * 1. It avoids potential integer overflow when reversing long numbers.
     * 2. It's more efficient, requiring only half the iterations.
     *
     * Time Complexity: O(log n) - We process half the digits of x.
     * Space Complexity: O(1) - Constant space used.
     */
    bool isPalindrome(int x) {

        // Edge Cases:
        // 1. Negative numbers are not palindromes (e.g., -121 reversed is 121-).
        // 2. Numbers ending in 0 (but aren't 0 itself) are not palindromes 
        //    because the first digit cannot be 0.
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int reversedHalf = 0;

        /**
         * Reversing half of the number:
         * We stop when x <= reversedHalf. At this point, we've reached 
         * or passed the middle of the number.
         * Example: x = 1221
         * Step 1: x = 122, reversedHalf = 1
         * Step 2: x = 12,  reversedHalf = 12 -> STOP (x == reversedHalf)
         */
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        /**
         * Palindrome Check:
         * 1. If length is even, x should equal reversedHalf (e.g., 12 == 12).
         * 2. If length is odd, the middle digit is at the end of reversedHalf.
         * We discard it using /10 (e.g., x=1, reversedHalf=12 -> 1 == 12/10).
         */
        return (x == reversedHalf || x == reversedHalf / 10);
    }
};
