class Solution {
public:
    vector<string>wordsContainer;

    struct trieNode{
        int idx; //lowest index of that suffix
        trieNode* children[26];
        ~trieNode() { //destructor to free memory after use
            for (int i = 0; i < 26; i++) {
                delete children[i];
            }
        }
    }; 
    //take care of the empty string one
    //set its idx value to the smallest strings index
    trieNode* root;

    trieNode* generate(){
        trieNode* newNode=new trieNode();
        newNode->idx=INT_MAX;//origianlly max
        for(int i=0;i<26;i++){
            newNode->children[i]=NULL;
        }
        return newNode;
    }
    void insert(string & word,int index){
        trieNode* crawler=root;
        for(int i=0;i<word.size();i++){
            char ch=word[i];
            if(crawler->children[ch-'a'] == NULL){
                crawler->children[ch-'a']=generate();
            }
            crawler=crawler->children[ch-'a'];
            // int updated_idx=min(crawler->idx,index);
            // crawler->idx=updated_idx;
            //this updates if we get other word whose position was less , but not on basis of length of word
            if(crawler->idx!=INT_MAX){
                //check kya prev stored idx se curr wala chota hai kya
                if(wordsContainer[index].length()<wordsContainer[crawler->idx].length()){
                    crawler->idx=index;
                }
            }
            else{
                crawler->idx=index;
            }
        }
        // crawler->idx=index; no need
    }

    int search(string & word){
        trieNode* crawler=root;
        for(int i=0;i<word.length();i++){
            int ch=word[i]-'a';
            if(crawler->children[ch]==NULL){
                return crawler->idx;//we cannot find more letters matching 
            }
            crawler=crawler->children[ch];
        }
        return crawler->idx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        root=generate();

        for(string & word: wordsContainer){
            reverse(word.begin(),word.end());
        }
        this->wordsContainer=wordsContainer;
        //we will find the prefix of reverse
        for(string & word:wordsQuery){
            reverse(word.begin(),word.end());
        }
        int minL=INT_MAX;
        for(int i=0;i<wordsContainer.size();i++){
            int word_size=wordsContainer[i].length();
            if(minL>word_size){
                minL=word_size;
                root->idx=i;
            }
            insert(wordsContainer[i],i);
        }

        //search
        vector<int>result(wordsQuery.size());
        for(int i=0;i<wordsQuery.size();i++){
            int idx=search(wordsQuery[i]);
            result[i]=idx;
        }
        delete(root);
        return result;
    }
};