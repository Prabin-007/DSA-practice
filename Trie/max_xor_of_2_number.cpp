// BIT TRIE

class Solution {
public:
    struct trieNode {
        trieNode* left;  // 0
        trieNode* right; // 1
    } ;
    trieNode* root;

    trieNode* getNode() {
        trieNode* newNode = new trieNode();
        newNode->left  = NULL;
        newNode->right = NULL;
        return newNode;
    }

    void generate(int num) {
        trieNode* crawl = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1; // if bit is set or not
            if (bit == 0) {
                if (crawl->left == NULL) {
                    crawl->left = getNode();
                }
                crawl = crawl->left;
            } else {
                if (crawl->right == NULL) {
                    crawl->right = getNode();
                }
                crawl = crawl->right;
            }
        }
    }

    int findMaximumXOR(vector<int>& nums) {
        int ans = 0;
        root = getNode();

        for (int num : nums) {
            generate(num);
        }

        for(int num : nums){
            int curr_xor=0;
            trieNode* crawler=root;
            for(int i=31;i>=0;i--){
                int bit=(num>>i)&1;
                //we go opposite side if we have one
                if(bit==0){
                    if(crawler->right!=NULL){
                        crawler=crawler->right;
                        curr_xor+=1<<i;
                    }
                    else{
                        //we have to go along the dir (left)
                        crawler=crawler->left;
                    }
                }
                else{//bit is 1
                    if(crawler->left!=NULL){
                        crawler=crawler->left;
                        curr_xor+=1<<i;
                    }
                    else{
                        //we have to go along the dir (right)
                        crawler=crawler->right;
                    }
                }
            }
            ans=max(ans,curr_xor);
        }
        return ans;
    }
};