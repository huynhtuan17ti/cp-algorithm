#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
const int MOD = 1e9 + 7;
long long F[MAXN];

int powMod(int x, int y){
    if(y == 0)
        return 1;
    if(y == 1)
        return x;
    int t = powMod(x, y/2);
    t = (1LL*t*t)%MOD;
    if(y % 2 == 1)
        t = (t*x)%MOD;
    return t;
}

int nCk(int n, int k){
    if(k < 0)
        return 0;
    if(k == 0)
        return 1;
    return F[n]*powMod(F[k]*F[n-k]%MOD, MOD-2)%MOD;
}

int get_bit(int val, int id){
    return (val >> id)&1;
}

int main(){
    int n, m;
    cin >> n >> m;
    //initialize factorial
    F[0] = 1;
    for(int i = 1; i <= n; i++)
        F[i] = (F[i-1]*i)%MOD;
    vector <int> b(m);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        // normalize
        n -= x; 
        y -= x;
        b[i] = y;
    }
    int res = 0;
    int maxState = (1<<m);
    for(int state = 0; state < maxState; state++){
        int sum = 0, cnt = 0;
        for(int bit = 0; bit < m; bit++)
            if(get_bit(state, bit)){
                cnt++;
                sum -= (b[bit] + 1);
            }
        if(cnt%2 == 0)
            res = (res + nCk(sum, sum + m - 1))%MOD;
        else
            res = (res - nCk(sum, sum + m - 1) + MOD)%MOD;
    }
    cout << res << '\n';
}