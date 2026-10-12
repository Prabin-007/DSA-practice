//  bhai naya cheez jaane ko mila bass ek dir se &dir karne mai code fail se work karne laga , analyze kyu

// That single & is one of the most famous performance traps in C++.

// When you wrote for(auto dir : directions), you were passing by value. This means C++ was dynamically allocating memory and creating a brand-new copy of your vector<int> for every single direction checked.

// In a DFS exploring a grid, you might make hundreds of thousands of recursive calls. Without the &, you were forcing the computer to create, copy, and destroy hundreds of thousands of temporary vectors in a fraction of a second. Memory allocation is incredibly slow compared to basic logic.

// By changing it to for(auto& dir : directions), you changed it to pass by reference:

// C++ immediately stopped copying.

// Instead of building new vectors, it just looked at the exact memory address of your existing directions array.

// You eliminated massive overhead instantly, allowing the DFS to run at full speed.

class Solution {
public:
    vector<string>result;
    int m;
    int n;

    struct trieNode{
        bool endOfWord;
        string word;
        trieNode* children[26];
    };

    trieNode* getNode(){
        trieNode * newNode= new trieNode();
        newNode->endOfWord=false;
        newNode->word="";
        
        for(int i=0;i<26;i++){
            newNode->children[i]=NULL;
        }
        return newNode;
    }
    vector<vector<int>>directions={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0}
    };

    void insert(trieNode* root,string& word){
        trieNode* crawler=root;

        //check for each character of word
        for(int i=0;i<word.length();i++){
            char ch=word[i];
            if(crawler->children[ch-'a']==NULL){
                crawler->children[ch-'a']=getNode();
            }
            crawler=crawler->children[ch-'a'];
        }
        crawler->endOfWord=true;
        crawler->word=word;
    }
    void findTrieWords(vector<vector<char>>& board,int i,int j,trieNode* root){
        if(i>=m || j>=n || i<0 || j<0){
            return;
        }
        if(board[i][j]=='$' || root->children[board[i][j]-'a']==NULL){
            return ;
        }

        root=root->children[board[i][j]-'a'];

        if(root->endOfWord==true){
            result.push_back(root->word);
            root->endOfWord=false;
        }

        char temp=board[i][j];
        board[i][j]='$'; //mark as visited

        for(auto& dir:directions){
            int nr=i+dir[0];
            int nc=j+dir[1];
            findTrieWords(board,nr,nc,root);
        }
        board[i][j]=temp;

    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        result.clear();
        m=board.size();
        n=board[0].size();

        trieNode* root= getNode();

        for(string& word:words){
            insert(root,word);
        }

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                char ch=board[i][j];

                findTrieWords(board,i,j,root);
            }
        }
        return result;
    }
};


// TLE 
// class Solution {
// public:
//     int m;
//     int n;
    
//     vector<vector<int>>vis;

//     int dr[4]={0,1,0,-1};
//     int dc[4]={-1,0,1,0};

//     bool dfs(int i,int j,int idx,vector<vector<char>>& board,string w){
//         if(idx==w.length()) return true;
//         if(i>=m || i<0 || j>=n || j<0 ) {
//             return false;
//         }

//         if(w[idx]!=board[i][j] || vis[i][j]==1){
//             return false;
//         }
//         //mark as visited
//         vis[i][j]=1;
//         bool ans=false;
//         if(board[i][j]==w[idx]){
//             for(int k=0;k<4;k++){
//                 ans=ans||dfs(i+dr[k],j+dc[k],idx+1,board,w);
//             }
//         }
//         vis[i][j]=-1;

//         return ans;
//     }

//     bool exist(vector<vector<char>>& board, string word) {
        
//         m=board.size();
//         n=board[0].size();
//         vis.resize(m,vector<int>(n,-1));

//         for(int i=0;i<m;i++){
//             for(int j=0;j<n;j++){
//                 if(dfs(i,j,0,board,word))return true;
//             }
//         }
//         return false;
//     }
//     vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
//         vector<string>ans;

//         for(string w:words){
//             if(exist(board,w)){
//                 ans.push_back(w);
//             }
//         }
//         return ans;
//     }
// };