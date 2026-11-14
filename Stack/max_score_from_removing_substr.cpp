class Solution {
public:
    string removeSubstr(string & s, string & matchStr){
        stack<char> st;

        for (char &ch : s) {
            if (ch == matchStr[1] && !st.empty() && st.top() == matchStr[0]) {
                st.pop();
            } else {
                st.push(ch);
            }
        }

        string remainStr;
        while (!st.empty()) {
            remainStr.push_back(st.top());
            st.pop();
        }
        reverse(remainStr.begin(), remainStr.end());
        return remainStr;
    }
    int maximumGain(string s, int x, int y) {
        int n=s.length();
        int score=0;

        string maxStr= (x>y) ? "ab" : "ba";
        string minStr= (maxStr=="ab") ? "ba" : "ab";

        string temp1=removeSubstr(s,maxStr);
        int removedPairsCount=(n-temp1.length())/2;
        score+=removedPairsCount*max(x,y);

        string temp2=removeSubstr(temp1,minStr);
        removedPairsCount=(temp1.length()-temp2.length())/2;
        score+= removedPairsCount*min(x,y);

        return score;
    }
};