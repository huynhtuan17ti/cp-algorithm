#include "gauss.h"

random_device device;
mt19937 generator(device());

int myIntRand(int lo, int hi) {
    uniform_int_distribution<int> rd(lo, hi);
    return rd(generator);
}

int main(){
    int T = 100;
    for(int iTest = 1; iTest <= T; iTest++){
        cerr << "Checking test " << iTest << " ... ";
        int n = myIntRand(5, 10);
        int m = myIntRand(5, 10);
        vector <vector <double>> coeff(n, vector <double>(m));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                coeff[i][j] = myIntRand(-10, 10);
        vector <double> ans;
        int p = gauss(coeff, ans);
        if(p > 0){
            for(int i = 0; i < n; i++){
                double sum = 0;
                for(int j = 0; j < m-1; j++)
                    sum += ans[j] * coeff[i][j];
                if(abs(sum - coeff[i][m-1]) > eps){
                    cerr << "Wrong!" << '\n';
                    return 0;
                }
            }
        }
        cerr << "Passed!" << '\n';
    }
}
