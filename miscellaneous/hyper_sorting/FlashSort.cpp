#include <bits/stdc++.h>

using namespace std;

vector <int> insertionSort(vector <int> a, int n){
	for (int i = 1; i < n; i++){
		int k = i - 1;
		int key = a[i];
		while (a[k] > key && k >= 0)
		{
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}
    return a;
}

vector <int> flashSort(vector <int> a, int n){
    int m = int(0.45*n); // number of partitions
    vector <int> l(m);
    int minVal = a[0], maxIndex = 0;
    for(int i = 0; i < n; i++){
        minVal = min(minVal, a[i]);
        if(a[maxIndex] < a[i])
            maxIndex = i;
    }
    if(a[maxIndex] == minVal)
        return a;
    
    double c = (double)(m - 1)/(a[maxIndex] - minVal);
    for(int i = 0; i < n; i++){
        int cls = int(c*(a[i] - minVal));
        l[cls]++;
    }
    for(int i = 1; i < m; i++)
        l[i] += l[i-1];

    swap(a[maxIndex], a[0]);

    int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < n - 1){
		while (j > l[k] - 1){
			j++;
			k = int(c*(a[j] - minVal));
		}
		flash = a[j];
		if (k < 0) break;
		while (j != l[k]){
			k = int(c*(flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
    return insertionSort(a, n);
}

int main(){
    vector <int> a = {5, 3, 3, 4, 5, 1, 4};
    a = flashSort(a, a.size());
    for(int u: a)
        cout << u << ' ';
    cout << '\n';
}