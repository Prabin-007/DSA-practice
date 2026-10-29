class Solution { 
public: 
    int dp[101][201][101]; 
    int Mod=1e9+7; 

    vector<vector<int>> floydWarshall(int n, vector<vector<int>> &dist) { 

        for (int k = 0; k < n; k++) { 
            for (int i = 0; i < n; i++) { 
                for (int j = 0; j < n; j++) { 
                    if (dist[i][k] != 1e9 && 
                        dist[k][j] != 1e9) { 
                        dist[i][j] = min( 
                            dist[i][j], 
                            dist[i][k] + dist[k][j] 
                        ); 
                    } 
                } 
            } 
        } 
        return dist; 
    } 

    int solve(int u, int fuel_left, vector<int>& locations, int finish, vector<vector<int>>& dist) {
        if (fuel_left < 0)
            return 0;

        if (dp[u][fuel_left][finish] != -1)
            return dp[u][fuel_left][finish];

        int ways = (u == finish) ? 1 : 0;
        int n = locations.size();

        for (int i = 0; i < n; i++) {
            if (i == u)
                continue;

            if (dist[u][i] > fuel_left)
                continue;

            ways = (ways + solve(i, fuel_left - dist[u][i], locations, finish, dist)) % Mod;
        }

        return dp[u][fuel_left][finish] = ways;
    }

    int countRoutes(vector<int>& locations, int start, int finish, int fuel) { 
        //we dont need minimum fuel cost, 
        //we need total possible routes 

        int n=locations.size(); 
        //2d matrix to store dist among each cities 
        //get minimum dist to reach that city from which other city 

        //i think this goes to dp on graph 
        //start dfs from each node and check how many paths possible 
        //state = {node,fuel_left} 
        //weights = dist bw nodes/cities 

        //maybe floyd warshall  
        //shortest path bw all nodes 
        //we have undirected edge 
        vector<vector<int>>dist(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j)continue;
                dist[i][j]=abs(locations[i]-locations[j]);
            }
        } 
        dist=floydWarshall(n,dist);

        //now we can see on the dist array 
        
        //to store how much ways we can reach  
        memset(dp,-1,sizeof(dp)); 

        //here will be the function call
        return solve(start, fuel, locations, finish, dist);
    }
};