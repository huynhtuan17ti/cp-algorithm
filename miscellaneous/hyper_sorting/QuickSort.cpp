#include <bits/stdc++.h>

using namespace std;

int partition(vector <int> &a, int l, int r){
    int pivot = a[(l+r)/2]; 
    while(l <= r){
        while(a[l] < pivot)
            l++;
        while(a[r] > pivot)
            r--;
        if(l <= r){
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }
    return l;
}

void quickSort(vector <int> &a, int l, int r){
    if (l < r){
        int pi = partition(a, l, r);
        quickSort(a, l, pi - 1);
        quickSort(a, pi, r);
    }
}

int main(){
    vector <int> a = {3, 4, 6, 7, 1};
    quickSort(a, 0, a.size()-1);
    for(int u: a)
        cout << u << ' ';
    cout << '\n';
}