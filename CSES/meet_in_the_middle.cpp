#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,x;
    cin>>n>>x;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }

    int n1=n/2;
    int n2=n-n1;
    vector<ll>left(1<<n1),right(1<<n2);

    // left half
    for(int i=0;i<(1<<n1);i++){
        ll sum=0;
        for(int j=0;j<n1;j++){
            if(i&(1<<j)){
                sum+=nums[j];
            }
        }
        left[i]=sum;
    }

    // right half
    for(int i=0;i<(1<<n2);i++){
        ll sum=0;
        for(int j=0;j<n2;j++){
            if(i&(1<<j)){
                sum+=nums[n1+j];
            }
        }
        right[i]=sum;
    }

    sort(right.begin(),right.end());
    ll count=0;
    for(int i=0;i<left.size();i++){
        int up = upper_bound(right.begin(),right.end(),x-left[i]) - right.begin();
        int lo = lower_bound(right.begin(),right.end(),x-left[i]) - right.begin();
        count += up - lo;
    }
    cout<<count;
    return 0;
}