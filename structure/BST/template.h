#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

template <typename TKey>
struct TBSTNode{
    TKey key;
    TBSTNode* P;
    TBSTNode* L;
    TBSTNode* R;
};

template <typename PNode>
inline void SetL(PNode parent, PNode child){
    child->P = parent;
    parent->L = child;
}
 
template <typename PNode>
inline void SetR(PNode parent, PNode child){
    child->P = parent;
    parent->R = child;
}
 
template <typename PNode>
inline void SetLink(PNode parent, PNode child, bool InRight){
    if (InRight) SetR(parent, child);
    else SetL(parent, child);
}

template <typename TKey, typename TNode> // TKey must have strict weak ordering "<", a == b means !(a < b) && !(b < a)
class TBST{
public:
    using PNode = TNode*;
    PNode nil;
    PNode EndNode;
 
    TBST(){
        nil = new TNode;
        EndNode = new TNode;
        EndNode->L = nil;
        EndNode->R = nil;
    }
 
    inline PNode& Root(){
        return EndNode->L;
    }
 
    ~TBST(){
        //Do not make recursion, stack overflow!!!
        vector<PNode> Q;
        if (Root() != nil) Q.push_back(Root());
        while (!Q.empty())
        {
            PNode x = Q.back(); Q.pop_back();
            if (x->L != nil) Q.push_back(x->L);
            if (x->R != nil) Q.push_back(x->R);
            delete x;
        }
        delete EndNode;
        delete nil;
    }
 
    //Print all keys in increasing order (for debugging)
    void Print() {
        function<void(PNode)> Visit = [&](PNode x){
            if (x == nil) return;
            Visit(x->L);
            cout << x->key << ' ';
            Visit(x->R);
        };
        Visit(Root());
        cout << endl;
    }
 
    void CalcHeightDepth(int& Height, ld& Depth){
        //Do not make recursion, stack overflow!!!
        int cnt = 0;
        long long TotalDepth = 0LL;
        Height = 0;
        vector<pair<PNode, int>> Q;
        if (Root() != nil)
            Q.emplace_back(Root(), 0);
        while (!Q.empty()){
            pair<PNode, int> p = Q.back(); Q.pop_back();
            ++cnt;
            TotalDepth += p.second;
            PNode x = p.first;
            if (Height < p.second)
                Height = p.second;
            if (x->L != nil) Q.emplace_back(x->L, p.second + 1);
            if (x->R != nil) Q.emplace_back(x->R, p.second + 1);
        }
        if (cnt != 0)
            Depth = (ld)TotalDepth / cnt;
        else
            Depth = 0.0L;
    }

    int GetMin(){
        //Do not make recursion, stack overflow!!!
        TKey minValue = INT_MAX;
        vector<PNode> Q;
        if (Root() != nil) Q.push_back(Root());
        while (!Q.empty())
        {
            PNode x = Q.back(); Q.pop_back();
            minValue = min(minValue, x->key);
            if (x->L != nil) Q.push_back(x->L);
            if (x->R != nil) Q.push_back(x->R);
        }
        return minValue;
    }

    int GetMax(){
        //Do not make recursion, stack overflow!!!
        TKey maxValue = INT_MIN;
        vector<PNode> Q;
        if (Root() != nil) Q.push_back(Root());
        while (!Q.empty())
        {
            PNode x = Q.back(); Q.pop_back();
            maxValue = max(maxValue, x->key);
            if (x->L != nil) Q.push_back(x->L);
            if (x->R != nil) Q.push_back(x->R);
        }
        return maxValue;
    }

    //Find a key, return nil if not exists
    virtual PNode Find(const TKey& k) {
        PNode x = Root();
        while (x != nil)
            if (k < x->key) x = x->L;
            else
                if (k > x->key) x = x->R;
                else break;
        return x;
    }

 
    virtual pair<PNode, bool> Insert(const TKey& k){
        pair<PNode, bool> res;
        PNode& x = res.first;
        PNode y = EndNode;
        x = Root();
        bool ToRight = false;
        while (x != nil){
            y = x;
            if (k == x->key) return res.second = false, res;
            ToRight = x->key < k;
            x = ToRight ? x->R : x->L;
        }
        x = new TNode;
        x->key = k;
        x->L = x->R = nil;
        SetLink(y, x, ToRight);
        return res.second = true, res;
    }
 
    /*
        Cách trong sách vở rất dở, xóa 1 nút lại chuyển key và xóa nút khác, làm hỏng
    iterator không mong muốn. Có lẽ vì đằng nào BST không tự cân bằng cũng vô dụng!
    Ở đây dùng cách xóa đúng nút cần xóa
    */
    virtual void Erase(PNode x){
        // Node y is the largest value < x.
        PNode y;
        if (x->L != nil && x->R != nil){
            y = x->L;
            while (y->R != nil) y = y->R;
        }
        else
            y = x;

        // Cut y from the tree
        PNode z = y->L != nil ? y->L : y->R;
        SetLink(y->P, z, y->P->R == y);

        // If y != x, replace x by y
        if (y != x){
            SetL(y, x->L);
            SetR(y, x->R);
            SetLink(x->P, y, x->P->R == x);
        }
        delete x;
    }
};


