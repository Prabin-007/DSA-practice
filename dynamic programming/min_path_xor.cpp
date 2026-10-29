// class Solution {
// public:
//     int n;
//     int m;
//     typedef vector<int>v;
//     typedef vector<v> vv;
//     typedef vector<vv> vvv;

//     vvv dp;
//     //vector<vector<vector<int>>>dp;
//     void solve(vector<vector<int>>& grid , int i,int j,int curr,int &ans){
//         if(i>=m || j>=n){
//             return;
//         }

//         if(i==m-1 && j==n-1){
//             curr= curr ^ grid[m-1][n-1];
//             ans=min(ans,curr);
//             return;
//         }
        
//         if(dp[i][j][curr]!=-1)
//             return ;

//         solve(grid,i,j+1,curr^grid[i][j],ans) ;
//         solve(grid,i+1,j,curr^grid[i][j],ans) ;
        
//         dp[i][j][curr]=curr;
//         //return dp[i][j]=min(right,down);
//     }

//     int minCost(vector<vector<int>>& grid) {
//         //note curr min xor may not give minimum value of xor later

//         m=grid.size();
//         n=grid[0].size();
//         //dp.assign(m,vector<vector<int>>(n,vector<int>(1024,-1)));
//         dp.assign(m, vv(n, v(1024, -1)));
//         int ans=1<<10;
//         solve(grid,0,0,0,ans);
//         return ans;
//     }
// };
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        typedef vector<int> v;
        typedef vector<v> vv;
        typedef vector<vv> vvv;

        vvv dp(m, vv(n, v(1024, 0)));

        dp[0][0][grid[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int curr = 0; curr < 1024; curr++) {
                    if (dp[i][j][curr] == 0)
                        continue;

                    if (j + 1 < n) {
                        dp[i][j + 1][curr ^ grid[i][j + 1]] = 1;
                    }

                    if (i + 1 < m) {
                        dp[i + 1][j][curr ^ grid[i + 1][j]] = 1;
                    }
                }
            }
        }

        for (int curr = 0; curr < 1024; curr++) {
            if (dp[m - 1][n - 1][curr])
                return curr;
        }

        return -1;
    }
};
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bitset<1024>>> dp(m, vector<bitset<1024>>(n));
        //m*n
        //dp[i][j] = it stores a bitset<1024> {0, 0, 1, 1, 0, .....}

        dp[0][0][grid[0][0]] = 1;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i == 0 && j == 0)
                    continue;

                bitset<1024> up; //[i-1][j]
                bitset<1024> left; //[i][j-1]

                if(i > 0) {
                    up = dp[i-1][j];
                }
                if(j > 0) {
                    left = dp[i][j-1];
                }

                bitset<1024> combined = up | left; //OR operation

                for(int xorVal = 0; xorVal < 1024; xorVal++) {
                    if(combined[xorVal]) {
                        int resultXorVal = xorVal ^ grid[i][j];
                        dp[i][j][resultXorVal] = 1;
                    }
                }
            }
        }

        //dp[m-1][n-1]
        for(int xorVal = 0; xorVal < 1024; xorVal++) {
            if(dp[m-1][n-1][xorVal]) {
                return xorVal;
            }
        }

        return -1;

        
    }
};
