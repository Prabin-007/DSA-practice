//--> Using Monotonic stack
//T.C : O(n) - We don't visit any element more than once
/*
    We are only storing one item in the stack, which is our ideal candidate for num2 (number that needs to be the largest). 
    If we find a number that is bigger than what we thought was our ideal candidate for num2; we pop out our stack 
    and store the value in num3 (mid value number), then we store the new ideal candidate for num2 in the stack. 
    On the next ith iteration, if nums[i] is actually less than s3, then we are done!
*/
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        //num1, num2, num3
        //num1 < num3 < num2
        int n  = nums.size();
        int num3 = INT_MIN;
        stack<int> st;
        
        for(int i = n-1; i >= 0; i--) {
            if(nums[i] < num3)
                return true;
            
            while(!st.empty() && nums[i] > st.top()) {
                num3 = st.top();
                st.pop();
            }
            st.push(nums[i]);
        }

        return false;
    }
};