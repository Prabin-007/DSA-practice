class LRUCache {
public:
    vector<int>keys;
    vector<int>q;
    int sz;
    LRUCache(int capacity) {
        sz=capacity;
        keys.resize(10001,-1);
    }
    
    int get(int key) {
        if(keys[key]==-1)
            return -1;
        for(int i=0;i<q.size();i++){
            if(q[i]==key){
                q.erase(q.begin()+i);
                q.push_back(key);
                break;
            }
        }
        return keys[key];
    }
    
    void put(int key, int value) {

        for(int i=0;i<q.size();i++){
            if(q[i]==key){
                q.erase(q.begin()+i);
                q.push_back(key);
                keys[key]=value;
                return;
            }
        }
        //not found in queue
        if(q.size()<sz){
            q.push_back(key);
            keys[key]=value;
            return;
        }
        else{
        keys[q[0]]=-1;
        q.erase(q.begin());
        q.push_back(key);
        keys[key]=value;
        }
    }
};
//using array (O(n))



//using hash map + dll (O(1))
class LRUCache {
public:
    list<int>dll;
    int n;
    unordered_map<int,pair<list<int>::iterator,int>>mp;
    LRUCache(int capacity) {
        n=capacity;
    }
    void makeRecentlyUsed(int key){
        dll.erase(mp[key].first);

        dll.push_front(key);

        mp[key].first=dll.begin();
    }

    int get(int key) {
        if(mp.find(key)==mp.end()){
            return -1;
        }
        makeRecentlyUsed(key);
        return mp[key].second;

    }
    
    void put(int key, int value) {
     if(mp.find(key)!=mp.end()){
            mp[key].second=value;
            makeRecentlyUsed(key);
        }
        else{
            dll.push_front(key);
            mp[key]={dll.begin(),value};
            n--;
        }
        if(n<0){
            int key_to_del=dll.back();
            mp.erase(key_to_del);
            dll.pop_back();
            n++;
        }
    }
};