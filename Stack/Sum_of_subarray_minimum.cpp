
class Solution {
public:
    int M=1e9+7;
    typedef long long ll;
    int n;
    vector<int>getNSL(vector<int>& arr){
        vector<int>result(n);
        stack<int>st;

        for(int i=0;i<n;i++){
            if(st.empty()){
                result[i]=-1;
            }
            else{
                while(!st.empty() && arr[st.top()]>arr[i]){
                    st.pop();
                }

                result[i]=st.empty()? -1: st.top();
            }
            st.push(i);
        }

        return result;
    }
    vector<int>getNSR(vector<int>& arr){
        vector<int>result(n);
        stack<int>st;

        for(int i=n-1;i>=0;i--){
            if(st.empty()){
                result[i]=n;
            }
            else{
                while(!st.empty() && arr[st.top()]>=arr[i]){
                    st.pop();
                }

                result[i]=st.empty()? n: st.top();
            }
            st.push(i);
        }

        return result;
    }
    int sumSubarrayMins(vector<int>& arr) {
        n=arr.size();

        vector<int>NSL=getNSL(arr);
        vector<int>NSR=getNSR(arr);

        ll sum=0;

        for(int i=0;i<n;i++){
            ll d1 = i - NSL[i]; //distance to nearest smaller to left from i
            
            ll d2 = NSR[i] - i; //distance to nearest smaller to right from i
            
            /*
                we have d1 numbers in the left and d2 numbers in the right
                i.e. We have d1 options to start from the left of arr[i] 
                and d2 options to end in the right of arr[i]
                so the total options to start and end are d1*d2
            */
            sum=(sum+ (arr[i]*d1*d2)%M)%M;
        }
        return sum;
    }
};