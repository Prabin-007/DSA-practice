// LC-3505
// first my code , it uses simple quick select and calulate cost of each subarray and then use dp to find the answer
//TLE -O(n*n*k) SC: O(n*k)
class Solution
{

public:
    typedef long long ll;

    int x, n;

    vector<vector<ll>> dp;

    vector<int> temp;

    int quickSelect(int l, int r, int k)
    {

        int pivot = temp[r];

        int i = l;

        for (int j = l; j < r; j++)
        {

            if (temp[j] <= pivot)
            {

                swap(temp[i], temp[j]);

                i++;
            }
        }

        swap(temp[i], temp[r]);

        if (i == k)

            return temp[i];

        if (i > k)

            return quickSelect(l, i - 1, k);

        return quickSelect(i + 1, r, k);
    }

    ll ops(vector<int> &nums, int l, int r)
    {

        temp.assign(nums.begin() + l, nums.begin() + r + 1);

        int mid = (r - l) / 2;

        int median = quickSelect(0, r - l, mid);

        ll tot = 0;

        for (int i = l; i <= r; i++)
        {

            tot += abs((ll)nums[i] - median);
        }

        return tot;
    }

    ll solve(vector<int> &nums, int idx, int k)
    {

        if (k <= 0)

            return 0;

        if (idx + x * k > n)

            return LLONG_MAX;

        if (dp[k][idx] != -1)

            return dp[k][idx];

        ll skip = solve(nums, idx + 1, k);

        ll next = solve(nums, idx + x, k - 1);

        ll take = LLONG_MAX;

        if (next != LLONG_MAX)
        {

            take = ops(nums, idx, idx + x - 1) + next;
        }

        return dp[k][idx] = min(skip, take);
    }

    long long minOperations(vector<int> &nums, int x, int k)
    {

        this->x = x;

        n = nums.size();

        dp.assign(k + 1, vector<ll>(n + 1, -1));

        return solve(nums, 0, k);
    }
};



// second code uses multiset to find median in log(n) time and then use dp to find the answer
// TC: O(nlogn + n*k) SC: O(n+k)
#define ll long long
class Solution
{
public:
    multiset<int> left, right;
    ll leftSum;
    ll rightSum;

    void insert(int val)
    {
        if (left.size() == 0 && right.size() == 0)
        {
            leftSum += val;
            left.insert(val);
        }
        else
        {
            if (left.size() >= right.size())
            {
                auto it = left.rbegin();

                if (*it <= val)
                {
                    rightSum += val;
                    right.insert(val);
                }
                else
                {
                    int ele = *it;
                    left.erase(prev(left.end()));
                    right.insert(ele);
                    left.insert(val);
                    leftSum -= ele;
                    rightSum += ele;
                    leftSum += val;
                }
            }
            else
            {
                auto it = right.begin();
                if (val <= *it)
                {
                    left.insert(val);
                    leftSum += val;
                }
                else
                {
                    int ele = *it;
                    right.erase(it);
                    left.insert(ele);
                    right.insert(val);
                    rightSum -= ele;
                    leftSum += ele;
                    rightSum += val;
                }
            }
        }
    }

    void eras(int val)
    {
        auto it1 = left.find(val);
        auto it2 = right.find(val);
        if (it1 != left.end())
        {
            if (left.size() >= right.size())
            {
                leftSum -= *it1;
                left.erase(it1);
            }
            else
            {
                int it3 = *right.begin();
                rightSum -= it3;
                leftSum -= *it1;
                leftSum += it3;
                right.erase(right.begin());
                left.erase(it1);
                left.insert(it3);
            }
        }
        else
        {
            if (left.size() <= right.size())
            {
                rightSum -= *it2;
                right.erase(it2);
            }
            else
            {

                int it3 = *left.rbegin();
                leftSum -= it3;
                rightSum += it3;
                rightSum -= *it2;
                left.erase(prev(left.end()));
                right.insert(it3);
                right.erase(it2);
            }
        }
    }
    int m;
    ll dp[100005][20];
    ll f(vector<ll> &ans, int x, int k, int i)
    {
        if (k == 0)
            return 0;
        if (m <= i)
            return LLONG_MAX / 10;
        if (dp[i][k] != -1)
            return dp[i][k];
        ll res = LLONG_MAX / 10;

        res = min(res, ans[i] + f(ans, x, k - 1, i + x)); // take
        res = min(res, f(ans, x, k, i + 1));              // skip

        return dp[i][k] = res;
    }

    long long minOperations(vector<int> &nums, int x, int k)
    {
        int n = nums.size();

        vector<ll> ans;
        leftSum = 0;
        rightSum = 0;
        for (int i = 0; i < x; i++)
        {
            insert(nums[i]);
        }

        int i = 0;
        int j = x - 1;

        while (j < n)
        {
            ll a;
            if (left.size() >= right.size())
            {
                a = *left.rbegin();
            }
            else if (left.size() < right.size())
            {
                a = *right.begin();
            }

            ll tot =
                (a * left.size()) - leftSum + rightSum - (a * right.size());
            ans.push_back(tot);

            eras(nums[i]);

            i++;
            j++;
            if (j < n)
            {
                insert(nums[j]);
            }
        }
        m = ans.size();
        memset(dp, -1, sizeof(dp));
        return f(ans, x, k, 0);
    }
};