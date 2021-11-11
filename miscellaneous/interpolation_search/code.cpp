#include <bits/stdc++.h>

using namespace std;

int interpolationSearch(int a[], int n, int x){
    int l = 0, r = n-1;
    while(l <= r && a[l] <= x && x <= a[r]){
        if(l == r){
            if(a[l] == x)
                return l;
            return -1;
        }
        int pos = l + (double)(r - l)/(a[r] - a[l])*(x - a[l]);
        if(a[pos] == x)
            return pos;
        if(a[pos] < x)
            l = pos + 1;
        else r = pos - 1;
    }
    return -1;
}

int main(){
    int a[] = {1, 4, 5, 8, 9, 13};
    assert(interpolationSearch(a, 6, 4) == 1);
    assert(interpolationSearch(a, 6, 1) == 0);
    assert(interpolationSearch(a, 6, 9) == 4);
    assert(interpolationSearch(a, 6, 13) == 5);
    assert(interpolationSearch(a, 6, 7) == -1);
}