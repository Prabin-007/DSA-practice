class Solution {
  public:
    void DFS(vector<vector<int>>& adj,vector<int>&vis,
        stack<int>& st,int u){
            vis[u]=1;
            
            //first push children then parent
            for(auto & v:adj[u]){
                if(!vis[v]){
                    // st.push(v);
                    DFS(adj,vis,st,v);
                }
            }
            st.push(u);
        };
    vector<int> topoSort(vector<vector<int>>& adj) {
        // code here
        
        int n=adj.size();
        stack<int>st;
        vector<int>vis(n,0);
        
      
        for(int i=0;i<n;i++){
            if(!vis[i]){
                DFS(adj,vis,st,i);
            }
        }
        
        vector<int>res;
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }
};