    void buildAncestorTable() {
        //fill column 0 by parent array 
        for(int j = 1; j < cols; j++) {
            for(int node = 0; node < n; node++) {
                if(ancestorTable[node][j-1] != -1)
                    ancestorTable[node][j] = ancestorTable[ ancestorTable[node][j-1] ][j-1];
            }
        }
    }

    int findLCA(int u, int v) {
        if(depth[u] < depth[v])
            swap(u, v);
        
        int k = depth[u] - depth[v];

        for(int j = 0; j < cols; j++) {
            if(k & (1 << j)) {
                u = ancestorTable[u][j];
            }
        }

        if(u == v) { //both were on the same path
            return u; //LCA
        }

        for(int j = cols-1; j >= 0; j--) {
            if(ancestorTable[u][j] == -1) {
                continue;
            }

            if(ancestorTable[u][j] != ancestorTable[v][j]) { //still different, then keep jumping
                u = ancestorTable[u][j];
                v = ancestorTable[v][j];
            }
        }

        return ancestorTable[u][0]; //LCA
    }