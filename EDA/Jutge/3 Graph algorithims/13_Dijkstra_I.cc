/*
 * Created by Matias Szarfer - 2016
 * 
 * Cada caso consiste en n (vertices), m (arcos),
 * seguido de m trios u,v,c, uv es la arista, y c el coste.
 * Finalmente nos dan x e y.
 * 
 * Indicar coste de ir de x a y.
 */

#include <iostream>
#include <utility>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

typedef pair<double, int> ArcP;
typedef vector< vector<ArcP> > GrafP;
typedef vector<int> VecInt;

int const infinito = numeric_limits<int>::max();

void leer(GrafP& G, int n, int m, int& x, int& y) {
    
    int u, v, c;
    ArcP arco;
    
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c;
        arco.second = v;
        arco.first = c;
        G[u].push_back(arco);
    }
    
    cin >> x >> y;
}

int dijkstra(const GrafP& G, int s, int ll, vector<int>& d, vector<int>& p) {
    
    int dist = -1;
    int n = G.size();
    
    d = vector<int>(n, infinito); d[s] = 0;
    p = vector<int>(n, -1);
    
    vector<bool> S(n, false); // Vector de cerrados
    
    priority_queue<ArcP, vector<ArcP>, greater<ArcP> > Q;
    Q.push(ArcP(0, s)); // Ponemos el nodo de salida.
    
    while (not Q.empty()) {
        
        int u = Q.top().second;
        Q.pop();
        
        if (not S[u]) {
            
            S[u] = true;
            if (u == ll) return d[u];
            
            for (int i = 0; i < G[u].size(); ++i) {
                
                int v = G[u][i].second;
                int c = G[u][i].first;
                
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    p[v] = u;
                    Q.push(ArcP(d[v], v));
                }
            }
        }
    }
    return dist;
}

int main() {
	
	int n, m, x, y;
    while (cin >> n >> m) {
        
        GrafP G(n);
        leer(G, n, m, x, y);
        
        VecInt d, p;
        int distancia = dijkstra(G, x, y, d, p);
        
        if (distancia == -1) cout << "no path from " << x << " to " << y << endl;
        else cout << distancia << endl;;
    }
}
