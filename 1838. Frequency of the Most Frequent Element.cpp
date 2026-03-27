class Solution {
public:
    /**
     * Approach: Sorting + Sliding Window
     * ----------------------------------
     * After sorting, for any window [l, r], we try to make all elements 
     * in that window equal to nums[r] (the largest value in the window).
     *
     * The cost to do this is: (nums[r] * window_length) - sum_of_window_elements.
     * If this cost > k, the window is invalid, and we shrink it from the left.
     *
     * Time Complexity: O(n log n) due to sorting. The sliding window is O(n).
     * Space Complexity: O(1) or O(log n) depending on the sort implementation.
     */
    int maxFrequency(vector<int>& nums, int k) {
        int ans = 0;
        long sum = 0; // Use long to prevent overflow during summation

        // Sort to ensure we only try to increase smaller numbers to larger ones
        ranges::sort(nums);

        // 'l' is the left pointer, 'r' is the right pointer of our window
        for (int l = 0, r = 0; r < nums.size(); ++r) {
            sum += nums[r];

            /**
             * Condition Check:
             * The target sum for the window to be valid is: nums[r] * (r - l + 1)
             * Our current sum is: sum + k (actual sum plus available operations)
             * If (sum + k) is less than the target, we must shrink the window.
             */
            while (sum + k < static_cast<long>(nums[r]) * (r - l + 1)) {
                sum -= nums[l++];
            }

            // The length of the valid window is (r - l + 1)
            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};
