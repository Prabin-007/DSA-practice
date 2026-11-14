class Solution {
public:
    typedef long long ll;
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n=nums.size();
        vector<ll>cumSum(n,0);
        cumSum[0]=nums[0];
        for(int i=1;i<n;i++){
            cumSum[i]=cumSum[i-1]+nums[i];
        }

        auto rangeSum = [&](int i,int j) -> long long {
            if(i>j)
                return 0;
            
            return cumSum[j]- ( (i>0) ? cumSum[i-1] : 0);
        };

        vector<int>NGR(n,n);
        stack<int>st;
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] < nums[i]){
                NGR[st.top()]=i;
                st.pop();
            }
            st.push(i);
        }    

        vector<ll>Operations(n+1,0);
        for(int i=n-1;i>=0;i--){
            int m=NGR[i];

            //i to m-1 tak nums[i] hi max hai lift them 
            ll segmentOps= 1LL*nums[i]*(m-i)- rangeSum(i,m-1) ;
            Operations[i]= segmentOps + Operations[m];
        }

        //now comes sliding window
        deque<int>dq;
        ll result=0;
        int i=0,j=0;
        while(j<n){

            while(!dq.empty() && nums[dq.back()]<nums[j]){ // decreaasing
                dq.pop_back();
            }

            dq.push_back(j);

            //shrink if required
            while(i<=j){
                int m = dq.front(); // monotonic decreasing order so first is max wala ka idx
                ll ops=(Operations[i]- Operations[m])+ (1LL*nums[m]*(j-m+1))- rangeSum(m,j);

                if(ops <=k)
                    break;
                
                i++;

                if(dq.front() < i){
                    dq.pop_front();
                }
            }

            result+= (j-i+1);
            j++;
        }
        return result;
    }
};