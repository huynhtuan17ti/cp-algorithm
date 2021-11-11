#include <bits/stdc++.h>

using namespace std;

void countingSort(vector <int> &a, int exp){
    int n = a.size();
    vector <int> out(n);
    vector <int> count(10);
    for(int i = 0; i < n; i++)
        count[(a[i]/exp)%10]++;
    for(int i = 1; i < 10; i++)
        count[i] += count[i-1];
    
    for(int i = n - 1; i >= 0; i--){
        out[count[(a[i]/exp)%10] - 1] = a[i];
        count[(a[i]/exp)%10]--;
    }
    for(int i = 0; i < n; i++)
        a[i] = out[i];
}

void radixSort(vector <int> &a){
    int n = a.size(), maxVal = a[0];
    for(int i = 0; i < n; i++)
        maxVal = max(maxVal, a[i]);
    for(int exp = 1; maxVal/exp > 0; exp *= 10){
        countingSort(a, exp);
    }
}

int main(){
    vector <int> a = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(a);
    for(int u: a)
        cout << u << ' ';
    cout << '\n';
}