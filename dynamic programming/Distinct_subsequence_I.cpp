class Solution {
public:
    // int dp[1001][1001];
    // int solve(string &s,string &t,int i,int j){
    //     if(i==s.length() || j==t.length()){
    //         return j == t.length() ? 1 : 0;
    //     }
    //     if(dp[i][j]!=-1)
    //         return dp[i][j];
    //     int cnt=0;
    //     if(s[i]==t[j]){
    //         cnt+=solve(s,t,i+1,j+1); //take 
    //         cnt+=solve(s,t,i+1,j);     //skip and search in rest if can find
    //     }   
    //     else{
    //         cnt+=solve(s,t,i+1,j);
    //     }

    //     return dp[i][j]=cnt;
    // }
    int numDistinct(string s, string t) {

        int m=s.length();
        int n=t.length();
        vector<vector<long long>>dp(m+1,vector<long long>(n+1,0));

        for(int i=0;i<=m;i++){
            dp[i][n]=1;//if j==n then found 
        }
        //base case done 

        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                int cnt=0;
                if(s[i]==t[j]){
                    cnt+=dp[i+1][j+1];
                    cnt+=dp[i+1][j];
                }
                else{
                    cnt+=dp[i+1][j];
                }
                dp[i][j]=cnt;
            }
        }
        return dp[0][0];
    }
};