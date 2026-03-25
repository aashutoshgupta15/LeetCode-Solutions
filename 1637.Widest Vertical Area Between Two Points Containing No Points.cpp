class Solution {
public:
    /**
     * Approach: Sorting x-coordinates
     * ------------------------------
     * A "vertical area" is bounded by two x-coordinates. To find the widest area 
     * with no points inside, we simply need to find the largest distance between 
     * two adjacent points when sorted by their x-coordinates.
     *
     * Time Complexity: O(n log n) 
     * The sorting step dominates the time complexity.
     *
     * Space Complexity: O(1) or O(log n) 
     * Depending on the implementation of std::sort (in-place vs stack space).
     */
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int n = points.size();
        
        // Sort the points based on their x-coordinates (points[i][0]).
        // By default, sort() on a vector of vectors sorts by the first element.
        sort(begin(points), end(points));
        
        int maxVal = 0;
        
        // Iterate through the sorted points and calculate the gap between
        // consecutive x-coordinates.
        for(int i = 1; i < n; i++) {
            // points[i][0] is the x-coordinate of the current point
            // points[i-1][0] is the x-coordinate of the previous point
            int currentWidth = points[i][0] - points[i-1][0];
            
            // Keep track of the maximum width found so far
            maxVal = max(maxVal, currentWidth);
        }
        
        return maxVal;
    }
};
