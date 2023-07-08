In my view, the most essential things of dynamic programming are:

- Determine the meaning of `dp[i][j]`(each cell of dynamic programming matrix)
- Determine the formula to progressively build up the dynamic programming matrix

[LeetCode 174 Dungeon Game](https://leetcode.com/problems/dungeon-game/description/)

In this case, if I determine `dp[i][j]` to be the least initial hp needed to travel from `dungeon[0][0]` to `dungeon[i][j]`, with deduction from the upper left corner to the lower right corner, I cannot take important information into account. For example, if `dungeon[i][j]` is a positive number, it cannot be reflected in `dp[i][j]` as the knight has to overcome all monsters preceding this orb. However, if I determine that `dp[i][j]` states for the least initial hp needed to travel from `dungeon[i][j]` to `dungeon[m][n]`, with deduction from the lower right corner to the upper left corner, then the issue no longer exists, as the knight gets orbs before encountering monsters, meaning that the knight can be more relax, make the use of orbs to overcome monsters. 

```c++
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // dp[i][j] states for the least initial hp needed to travel from dungeon[i][j] to dungeon[m][n]

        dp[m-1][n-1] = dungeon[m-1][n-1]<0 ? 1-dungeon[m-1][n-1]:1;
        if(n>1) {
            for(int i=n-2;i>=0;i--){
                dp[m-1][i] = max(dp[m-1][i+1]-dungeon[m-1][i], 1);
            }
        } 
        if(m>1) {
            for(int i=m-2;i>=0;i--){
                dp[i][n-1] = max(dp[i+1][n-1]-dungeon[i][n-1], 1);
            }
        }

        if(m>1 && n>1) {
            for(int i=m-2;i>=0;i--){
                for(int j=n-2;j>=0;j--){
                    dp[i][j] = max(min(dp[i+1][j], dp[i][j+1])-dungeon[i][j], 1);
                }
            }
        }

        return dp[0][0];
    }
        
};
```

