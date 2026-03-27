class Solution {
public:
    /**
     * Approach: Two-Pointer Technique
     * ------------------------------
     * We use two pointers, 'left' starting at the beginning and 'right' 
     * at the end of the string. We move them toward the center, 
     * skipping any non-alphanumeric characters along the way.
     *
     * Time Complexity: O(n)
     * Each character in the string is visited at most once.
     *
     * Space Complexity: O(1)
     * We are checking the string in-place without creating a filtered copy.
     */
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;

        while (left < right) {
            /**
             * Skip characters from the left that are not letters or numbers.
             * The 'left < right' check ensures we don't go out of bounds.
             */
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            
            /**
             * Skip characters from the right that are not letters or numbers.
             */
            while (left < right && !isalnum(s[right])) {
                right--;
            }

            /**
             * Compare the two characters after converting both to lowercase.
             * If they don't match, the string is not a palindrome.
             */
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }

            // Move both pointers inward after a successful match
            left++;
            right--;
        }

        // If pointers meet or cross, all valid characters matched
        return true;
    }
};
