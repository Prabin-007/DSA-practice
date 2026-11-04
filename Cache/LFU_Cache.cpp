class LFUCache {
public:
    int cap;
    int size;
    unordered_map<int,list<vector<int>>::iterator>mp;//key->adress
    map<int,list<vector<int>>>freq;   //counter {key,value,count}
    //ordered_map to get least count element easily

    LFUCache(int capacity) {
        size=0;
        cap=capacity;    
    }
    void makeMostFreqUsed(int key){
        auto &vec=(*(mp[key]));
        int val=vec[1];
        int f  =vec[2];
        freq[f].erase(mp[key]);// uss adress ko dll se erase kardo
        if(freq[f].empty())
            freq.erase(f); //empty hogaya toh remove kardo
        f++;
        freq[f].push_front({key,val,f});
        mp[key]=freq[f].begin();
    }
    int get(int key) {
        if(mp.find(key)==mp.end())
            return -1;
        
        makeMostFreqUsed(key);
        auto vec=(*(mp[key]));
        return vec[1];
    }
    
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            auto & vec=(*mp[key]);
            int f=vec[2];
            vec[1]=value;

            makeMostFreqUsed(key);
        }
        else if 
            (cap>size){
                freq[1].push_front({key,value,1});
                size++;
                mp[key]=freq[1].begin();
            }
            else{//time to delete LRU
                auto & konsa_list=freq.begin()->second;
                int key_to_delete=(konsa_list.back())[0];
                
                konsa_list.pop_back();
                if(konsa_list.empty()){
                    freq.erase(freq.begin()->first);
                }
                freq[1].push_front({key,value,1});

                mp.erase(key_to_delete);
                mp[key]=freq[1].begin();
            }

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */