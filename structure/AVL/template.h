#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename TKey>
struct TAVLNode
{
    TKey key;
    TAVLNode* P;
    TAVLNode* L;
    TAVLNode* R;
    int Height;
    inline int Balance(){
        return L->Height > R->Height ? L->Height - R->Height : R->Height - L->Height;
    }
};

template <typename PNode>
inline void SetL(PNode parent, PNode child)
{
    child->P = parent;
    parent->L = child;
}
 
template <typename PNode>
inline void SetR(PNode parent, PNode child)
{
    child->P = parent;
    parent->R = child;
}
 
template <typename PNode>
inline void SetLink(PNode parent, PNode child, bool InRight)
{
    if (InRight) SetR(parent, child);
    else SetL(parent, child);
}
 
template <typename PNode>
inline void UpTree(PNode x) //Rotate Left/Right around x->P
{
    PNode y = x->P;
    PNode z = y->P;
    if (x == y->L){
        SetL(y, x->R);
        SetR(x, y);
    }
    else{
        SetR(y, x->L);
        SetL(x, y);
    }
    SetLink(z, x, z->R == y);
}


template <typename TKey, typename TNode>
class TAVLTree{
public:
    using PNode = TNode*;
    PNode nil;
    PNode EndNode;

    TAVLTree(){
        nil = new TNode;
        EndNode = new TNode;
        EndNode->L = nil;
        EndNode->R = nil;
        nil->Height = 0;
    }

private:
    inline bool UpdateHeight(PNode x){
        int NewCal = max(x->L->Height, x->R->Height) + 1;
        if (NewCal != x->Height){
            x->Height = NewCal;
            return true;
        }
        else
            return false;
    }
 
    inline void UpTreeUdt(PNode x){
        PNode y = x->P;
        UpTree(x);
        UpdateHeight(y);
        UpdateHeight(x);
    }
 
    void FixBalance(PNode x){
        PNode y, z;
        if (x->L->Height > x->R->Height){
            y = x->L;
            z = y->L->Height >= y->R->Height ? y->L : y->R;
        }
        else{
            y = x->R;
            z = y->R->Height >= y->L->Height ? y->R : y->L;
        }
        if ((y == x->L) == (z == y->L))
            UpTreeUdt(y);
        else{
            UpTreeUdt(z);
            UpTreeUdt(z);
        }
    }
 
    //Đi từ x lên gốc, cập nhật độ cao và chữa hệ số cân bằng
    inline void MakePathBalance(PNode x) {
        while (x != EndNode){
            PNode y = x->P;
            if (x->Balance() > 1)
                FixBalance(x); //x->Height is also updated
            else
                if (!UpdateHeight(x)) break;
            x = y;
        }
    }
 
public:
    inline PNode& Root(){
        return EndNode->L;
    }

    ~TAVLTree(){
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

    void Update(PNode x){
        UpdateHeight(x);
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
    PNode Find(const TKey& k) {
        PNode x = Root();
        while (x != nil)
            if (k < x->key) x = x->L;
            else
                if (k > x->key) x = x->R;
                else break;
        return x;
    }
 
    pair<PNode, bool> Insert(const TKey& k){
        pair<PNode, bool> res;
        PNode& x = res.first;
        PNode y = EndNode;
        x = Root();
        bool ToRight = false;
        while (x != nil){
            y = x;
            if (k == x->key) 
                return res.second = false, res;
            ToRight = x->key < k;
            x = ToRight ? x->R : x->L;
        }
        x = new TNode;
        x->key = k;
        x->L = x->R = nil;
        SetLink(y, x, ToRight);

        x = res.first;
        x->Height = 1;
        MakePathBalance(x->P);
        res.second = true;
        return res;
    }
 
    void Erase(PNode x){
        PNode y;
        if (x->L != nil && x->R != nil){
            y = x->L;
            while (y->R != nil) y = y->R;
        }
        else
            y = x;
        //Cut y from the tree
        PNode z = y->L != nil ? y->L : y->R;
        SetLink(y->P, z, y->P->R == y);
        MakePathBalance(y->P);
        if (y != x)
        {
            SetL(y, x->L);
            SetR(y, x->R);
            SetLink(x->P, y, x->P->R == x);
            y->Height = x->Height;
        }
        delete x;
    }
};