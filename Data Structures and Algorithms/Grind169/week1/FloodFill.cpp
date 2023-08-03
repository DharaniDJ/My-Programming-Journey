
// Problem link: https://leetcode.com/problems/flood-fill/

// DFS - O(n+m) time and O(n+m) space complexity
class Solution {
public:
    void solve(vector<vector<int>>& image, int sr, int sc, int color, int newColor){
        if(color==image[sr][sc]){
            image[sr][sc]=newColor;
            if(sr>=1) solve(image,sr-1,sc,color,newColor);
            if(sc>=1) solve(image,sr,sc-1,color,newColor);
            if(sr+1<image.size()) solve(image,sr+1,sc,color,newColor);
            if(sc+1<image[0].size()) solve(image,sr,sc+1,color,newColor);
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int color = image[sr][sc];
        if(color!=newColor) solve(image,sr,sc,color,newColor);
        return image;
    }
};
