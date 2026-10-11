LC-2472
Maximum Number of Non-overlapping Palindrome Substrings


TC: O(n^3)  nested loop plus one for palindrome check 
SC:O(n^2)


class Solution {
public:
    int n;
    vector<vector<int>>dp;

    bool isPalindrome(string & s, int i,int j){
        while(i<j){
            if(s[i]!=s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
    int solve(string & s,int i, int j, int k){
        if(i >=n || j>=n)
            return 0;

        if(dp[i][j]!=-1)
            return dp[i][j];

        int ans=0;
        if(isPalindrome(s,i,j)){
            int take = 1 + solve(s,j+1,j+k,k);
            int slide =solve(s,i,j+1,k);
            int move=solve(s,i+1,j+1,k);

            ans=max({take,slide,move});
        }
        //else if not palindrome
        int slide=solve(s,i,j+1,k);
        int move=solve(s,i+1,j+1,k);
        ans=max({ans,slide,move});


        return dp[i][j]=ans;
    }
    int maxPalindromes(string s, int k) {
        n = s.length();
        if(k==1)
            return n;

        dp.assign(n+1,vector<int>(n+1,-1));
        return solve(s,0,k-1,k);
    }
};


//bottom up
class Solution {
public:
    bool isPalindrome(string & s, int i,int j){
        while(i<j){
            if(s[i]!=s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
    int maxPalindromes(string s, int k) {
        int n=s.length();
        if(k==1)
            return n;

        vector<vector<int>>dp(n+1,vector<int>(n+1,0));

        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=i;j--){
                if(isPalindrome(s,i,j)){
                     int growWindow  = dp[i][j + 1];
                    int takeIt      = 1 + (j + k <= n ? dp[j + 1][j + k] : 0);
                    int slideWindow = dp[i + 1][j + 1];

                    dp[i][j] = max({growWindow, takeIt, slideWindow});
                }
                //else

                int slideWindow = dp[i + 1][j + 1];
                int growWindow  = dp[i][j + 1];
                dp[i][j] = max({dp[i][j], slideWindow, growWindow});
            }
        }
        return dp[0][k - 1];
    }
};



we can optimize the palindrome check by precomputing for (i,j) is it a palindrome or not 
so TC can be reduced to O(n^2) + O(n^2)  ~ O(n^2)


class Solution {
public:
    bool isPalindrome(string & s, int i,int j){
        while(i<j){
            if(s[i]!=s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
    int maxPalindromes(string s, int k) {
        int n=s.length();
        if(k==1)
            return n;

        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        //Palindromic substring Blueprint
        for(int L = 1; L <= n; L++) {
            for(int i = 0; i+L <= n; i++) {
                int j = i + L - 1;

                if(i == j) {
                    isPalindrome[i][i] = true; //Single characters are palindrome
                } else if(i+1 == j) {
                    isPalindrome[i][j] = (s[i] == s[j]); //Strings of 2 Length
                } else {
                    isPalindrome[i][j] = ((s[i] == s[j]) && isPalindrome[i+1][j-1] == true);
                }
            }
        }


        vector<vector<int>>dp(n+1,vector<int>(n+1,0));

        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=i;j--){
                if(isPalindrome[i][j]){
                     int growWindow  = dp[i][j + 1];
                    int takeIt      = 1 + (j + k <= n ? dp[j + 1][j + k] : 0);
                    int slideWindow = dp[i + 1][j + 1];

                    dp[i][j] = max({growWindow, takeIt, slideWindow});
                }
                //else

                int slideWindow = dp[i + 1][j + 1];
                int growWindow  = dp[i][j + 1];
                dp[i][j] = max({dp[i][j], slideWindow, growWindow});
            }
        }
        return dp[0][k - 1];
    }
};

//Approach-5 (using different recursion style + Using BluePrint for solving palindromic DP problems as above for O(1) isPalindrome)
//T.C : O(n^2)
//S.C : O(n^2)
class Solution {
public:
    vector<vector<bool>> isPalindrome;
    vector<int> t;

    int solve(int n, int k) {
        if (n < k) return 0;

        if (t[n] != -1) 
            return t[n];

        int result = solve(n - 1, k); //ignore the current character s[n-1]

        int j = n - 1;
        //end the current palindrome at the current character s[n-1]
        for (int i = 0; j-i+1>=k; i++) {
            if (isPalindrome[i][j]) {
                result = max(result, 1 + solve(i, k));
            }
        }

        return t[n] = result;
    }

    int maxPalindromes(string s, int k) {
        int n = s.length();
        isPalindrome.assign(n, vector<bool>(n, false));

        for (int L = 1; L <= n; L++) {
            for (int i = 0; i + L <= n; i++) {
                int j = i + L - 1;

                if (i == j) {
                    isPalindrome[i][i] = true;
                } else if (i + 1 == j) {
                    isPalindrome[i][j] = (s[i] == s[j]);
                } else {
                    isPalindrome[i][j] = ((s[i] == s[j]) && isPalindrome[i+1][j-1] == true);
                }
            }
        }

        t.assign(n + 1, -1);
        return solve(n, k);
    }
};


//Approach-6 (Bottom-up version of Approach-5 above)
//T.C : O(n^2)
//S.C : O(n^2)
class Solution {
public:
    vector<vector<bool>> isPalindrome;
    vector<int> t;

    int maxPalindromes(string s, int k) {
        int n = s.length();
        isPalindrome.assign(n, vector<bool>(n, false));

        for (int L = 1; L <= n; L++) {
            for (int i = 0; i + L <= n; i++) {
                int j = i + L - 1;

                if (i == j) {
                    isPalindrome[i][i] = true;
                } else if (i + 1 == j) {
                    isPalindrome[i][j] = (s[i] == s[j]);
                } else {
                    isPalindrome[i][j] = ((s[i] == s[j]) && isPalindrome[i+1][j-1] == true);
                }
            }
        }

        t.assign(n + 1, -1);
        //base case
        for(int len = 0; len < k; len++) {
            t[len] = 0; // if (n < k) return 0;
        }

        for (int len = k; len <= n; len++) {

            int result = t[len - 1];      // int result = solve(n - 1, k);

            int j = len - 1;
            for (int i = 0; j-i+1 >= k; i++) {
                if (isPalindrome[i][j]) {
                    result = max(result, 1 + t[i]);   // result = max(result, 1 + solve(i, k));
                }
            }

            t[len] = result;              // return t[n] = result;
        }

        return t[n];                      // return solve(n, k);
    }
};


//greedy 
if k is not valid substring check for k+1

