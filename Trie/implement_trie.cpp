class Trie {
public:
    struct trieNode{
        bool isEndOfWord;
        trieNode* children[26];
    };

    trieNode* getNode(){
        trieNode* newNode=new trieNode();
        newNode->isEndOfWord=false;
        for(int i=0;i<26;i++){
            newNode->children[i]=NULL;
        }
        return newNode;
    }

    
    trieNode* root;
    Trie() {
        root=getNode();
    }
    
    void insert(string word){
        trieNode* crawler=root;

        for(int i=0;i<word.size();i++){
            char ch=word[i];

            if(crawler->children[ch-'a']==NULL){
                crawler->children[ch-'a']=getNode();
            }
            crawler=crawler->children[ch-'a'];
        }
        crawler->isEndOfWord=true;
    }
    
    bool search(string word) {
        trieNode* crawler=root;

        for(int i=0;i<word.size();i++){
            char ch=word[i];

            if(crawler->children[ch-'a']==NULL){
                return false;
            }
            crawler=crawler->children[ch-'a'];
        }
        return crawler->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        string temp="";

        trieNode* crawler=root;

        for(int i=0;i<prefix.size();i++){
            char ch=prefix[i];

            if(crawler->children[ch-'a']==NULL){
                return false;
            }
            crawler=crawler->children[ch-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */