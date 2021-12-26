#include "template.h"
#include <random>
#include <set> // testing with std::set

random_device device;
mt19937 generator(device());

int myIntRand(int lo, int hi) {
    uniform_int_distribution<int> rd(lo, hi);
    return rd(generator);
}

int main(){
    srand(time(NULL));

    TBST <int, TBSTNode<int>> bst;

    set <int> s;
    int n = myIntRand(10000, 100000);
    
    vector <int> a;
    for(int i = 1; i <= n; i++){
        int x = myIntRand(-1000, 1000);
        //cerr << "Insert operation: " << x << '\n';
        a.push_back(x);
        bst.Insert(x);
        s.insert(x);

        if(*(s.begin()) != bst.GetMin())
            return cout << "Wrong!", 0;
        
        if(*(s.rbegin()) != bst.GetMax())
            return cout << "Wrong!", 0;
    }

    for(int i = 1; i <= myIntRand(1, n); i++){
        int val = a[myIntRand(0, a.size()-1)];
        //cerr << "Erase operation: " << val << '\n';
        auto it1 = s.find(val);
        auto it2 = bst.Find(val);

        assert((it1 != s.end()) == (it2 != bst.nil));

        if(it1 != s.end())
            s.erase(it1);

        if(it2 != bst.nil)
            bst.Erase(it2);

        if(*(s.begin()) != bst.GetMin())
            return cout << "Wrong!", 0;

        if(*(s.rbegin()) != bst.GetMax())
            return cout << "Wrong!", 0;
    }

    cout << "Pass all!" << '\n';
}