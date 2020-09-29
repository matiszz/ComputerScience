/*
 * Created by Matias Szarfer - 2016
 * 
 * Cada caso consiste en n (vertices), m (arcos),
 * seguido de m trios u,v,c, uv es la arista, y c el coste.
 * Finalmente nos dan x e y.
 * 
 * Indicar el camino de x a y.
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

bool dijkstra(const GrafP& G, int s, int ll, VecInt& d, VecInt& p, VecInt& camino) {
    
    bool llegado = false;
    int dist;
    int n = G.size();
    
    d = VecInt(n, infinito); d[s] = 0;
    p = VecInt(n, -1);
    
    vector<bool> S(n, false); // Si S[i] está fijado.
    priority_queue<ArcP, vector<ArcP>, greater<ArcP> > Q;
    Q.push(ArcP(0, s));
    
    while (not Q.empty() and not llegado) {
        int u = Q.top().second;
        Q.pop();
        
        if (not S[u]) {
            
            S[u] = true;
            
            if (u == ll) llegado = true;
            else {
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
    }
    if (llegado) {
        while (ll != s) {
            camino.push_back(ll);
            ll = p[ll];
        }
        camino.push_back(ll);
        return true;
    }
    else return false;
}

int main() {
	
	int n, m, x, y;
    while (cin >> n >> m) {
        
        GrafP G(n);
        leer(G, n, m, x, y);
        
        VecInt d, p, camino;
        bool posible = dijkstra(G, x, y, d, p, camino);
        
        if (not posible) cout << "no path from " << x << " to " << y << endl;
        else {
            bool primero = true;
            for (int i = camino.size()-1; i >= 0; --i) {
                if (primero) {
                    cout << camino[i];
                    primero = false;
                } else
                    cout << ' ' << camino[i];
            }
            cout << endl;
        }
    }
}
