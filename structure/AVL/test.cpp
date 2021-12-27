#include "template.h"
#include <random>
#include <chrono>
#include <set> // testing with std::set

random_device device;
mt19937 generator(device());

int myIntRand(int lo, int hi) {
    uniform_int_distribution<int> rd(lo, hi);
    return rd(generator);
}

int main(){
    srand(time(NULL));

    auto start = std::chrono::high_resolution_clock::now();
    TAVLTree <int, TAVLNode<int>> avl;

    set <int> s;
    int n = myIntRand(10000, 10000);
    
    vector <int> a;
    for(int i = 1; i <= n; i++){
        int x = myIntRand(-1000, 1000);
        //cerr << "Insert operation: " << x << '\n';
        a.push_back(x);
        avl.Insert(x);
        s.insert(x);

        if(*(s.begin()) != avl.GetMin())
            return cout << "Wrong!", 0;
        
        if(*(s.rbegin()) != avl.GetMax())
            return cout << "Wrong!", 0;
    }

    for(int i = 1; i <= myIntRand(1, n); i++){
        int val = a[myIntRand(0, a.size()-1)];
        //cerr << "Erase operation: " << val << '\n';
        auto it1 = s.find(val);
        auto it2 = avl.Find(val);

        assert((it1 != s.end()) == (it2 != avl.nil));

        if(it1 != s.end())
            s.erase(it1);

        if(it2 != avl.nil)
            avl.Erase(it2);

        if(*(s.begin()) != avl.GetMin())
            return cout << "Wrong!", 0;

        if(*(s.rbegin()) != avl.GetMax())
            return cout << "Wrong!", 0;
    }

    cout << "Pass all!" << '\n';
    auto finish = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    cout << "Running in " << duration.count() << " microseconds" << '\n';
}