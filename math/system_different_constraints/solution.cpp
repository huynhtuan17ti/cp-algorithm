/* http://poj.org/problem?id=2983 */
#include <vector>
#include <iostream>
typedef long long ll;
using namespace std;

struct edge{
    int u, v, c;
};

/*
    check if negative cycle
*/
bool bellman_ford(int n, vector <edge> edges){
    int m = (int)edges.size();
    vector <ll> dist(n+1);
    for(int i = 1; i < n; i++)
        for(int j = 0; j < m; j++){
            int u = edges[j].u;
            int v = edges[j].v;
            int c = edges[j].c;
            if(dist[v] > dist[u] + c)
                dist[v] = dist[u] + c;
        }
    
    for(int j = 0; j < m; j++){
        int u = edges[j].u;
        int v = edges[j].v;
        int c = edges[j].c;
        if(dist[v] > dist[u] + c)
            return true;
    }
    return false;
}

void solve(int n, int m){
    vector <edge> edges;
    while(m--){
        char t;
        cin >> t;
        if(t == 'P'){
            int u, v, c;
            cin >> u >> v >> c;
            edges.push_back({u, v, c});
            edges.push_back({v, u, -c});
        }else{
            int u, v; cin >> u >> v;
            edges.push_back({v, u, -1});
        }
    }
    if(bellman_ford(n, edges))
        cout << "Unreliable" << '\n';
    else cout << "Reliable" << '\n';
}

int main(){
    int n, m; 
    while(cin >> n >> m){
        solve(n, m);
    }
    
}