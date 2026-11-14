class TreeAncestor {
    vector<vector<int>>ancestorTable;
    int rows;
    int cols;
public:
    TreeAncestor(int n, vector<int>& parent) {
         rows=n;
         cols=log2(n)+1;
        ancestorTable.resize(rows,vector<int>(cols,-1));
        for(int i=0;i<n;i++){ //column 0
            ancestorTable[i][0]=parent[i];
        }
        for(int col=1;col<cols;col++){
            for(int node =0 ;node<n;node++){
                if(ancestorTable[node][col-1]!=-1){
                ancestorTable[node][col]=ancestorTable[ancestorTable[node][col-1]][col-1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int j=0;j<cols;j++){
            if(k & (1<<j)){
                node=ancestorTable[node][j];
                if(node==-1) return -1;
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */