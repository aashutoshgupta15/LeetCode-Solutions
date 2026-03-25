class Solution {
public:
    /**
     * Approach: One-pass Greedy Swap
     * ----------------------------
     * We iterate through the array once. At each index, we check if the 
     * current "wiggle" condition (up or down) is met. If not, we swap 
     * the current element with the next one.
     *
     * Time Complexity: O(n) 
     * We traverse the array of size 'n' exactly once.
     *
     * Space Complexity: O(1)
     * The sorting is done in-place without using any extra data structures.
     */
    void wiggleSort(vector<int> &nums) {
        int n = nums.size();

        for(int i = 0; i < n - 1; i++) {
            // At even indices (0, 2, 4...), we want nums[i] <= nums[i+1]
            if(i % 2 == 0) {
                // If current is larger than next, swap to fix the "valley"
                if(nums[i] > nums[i+1])
                    swap(nums[i], nums[i+1]);
            } 
            // At odd indices (1, 3, 5...), we want nums[i] >= nums[i+1]
            else {
                // If current is smaller than next, swap to fix the "peak"
                if(nums[i] < nums[i+1])
                    swap(nums[i], nums[i+1]);
            }
        }
    }
};
