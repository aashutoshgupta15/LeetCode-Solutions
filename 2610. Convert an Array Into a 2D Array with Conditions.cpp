class Solution {
public:
    /**
     * Approach: Frequency-Based Row Assignment
     * ----------------------------------------
     * We need to distribute numbers into as few rows as possible, 
     * where each row contains unique elements.
     *
     * The row index for any number is determined by how many times 
     * we've already seen that number. 
     * - First time seeing 'x'? Put it in result[0].
     * - Second time seeing 'x'? Put it in result[1].
     *
     * Time Complexity: O(n)
     * We iterate through the input array 'nums' exactly once.
     *
     * Space Complexity: O(n) 
     * To store the frequency map (vector 'mp') and the result matrix.
     */
    vector<vector<int>> findMatrix(vector<int>& nums) {
        int n = nums.size();
        
        // Use a vector as a frequency map since 1 <= nums[i] <= n.
        // Index represents the number, value represents its current count.
        vector<int> mp(n + 1, 0);
        
        vector<vector<int>> result;

        for(int &num : nums) {
            int freq = mp[num];
            
            /**
             * If the current frequency of 'num' is equal to the number of 
             * rows we currently have, it means all existing rows already 
             * contain this number. We need to create a new row.
             */
            if(freq == result.size()) {
                result.push_back({});
            }
            
            // Place the number in the row corresponding to its current frequency
            result[freq].push_back(num);
            
            // Increment the frequency so the next occurrence goes to the next row
            mp[num]++;
        }
        
        return result;
    }
};
