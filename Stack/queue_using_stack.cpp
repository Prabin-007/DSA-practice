class MyQueue {
public:
    stack<int>in;
    stack<int>out;
    int peekEl;
    MyQueue() {
        peekEl=-1;
    }
    
    void push(int x) {
        if(in.empty()){
            peekEl=x;
        }
        
        in.push(x);//everytime
    }
    //amortized O(1)
    int pop() {
        if(out.empty()){ //O(N)
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
        }
        //else O(1)
        int val = out.top();
        out.pop();
        return val;
    }
    
    int peek() {
        if(out.empty()){
            return peekEl;
        }
        return out.top();
    }
    
    bool empty() {
        return (in.empty() && out.empty());
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */