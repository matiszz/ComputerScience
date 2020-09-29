/*
 * Created by Matias Szarfer - 2016
 * 
 * n vertices, m aristas, m parejas de aristas xy
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector< vector<int> > Grafo;

bool coloreable(Grafo& G) {
    
    vector<int> pintado(G.size(), -1);
    queue<int> S;
    
    for (int i = 0; i < G.size(); ++i) {
        if (pintado[i] < 0) {
            pintado[i] = 1;
            S.push(i);
            
            while(not S.empty()) {
                
                int x = S.front();
                S.pop();
                
                for (int y = 0; y < G[x].size(); ++y) {
                    if (pintado[G[x][y]] < 0) {
                        S.push(G[x][y]);
                        pintado[G[x][y]] = 1 - pintado[x];
                    }
                    else if (pintado[G[x][y]] == pintado[x]) return false;
                }
            }
        }
    }
    return true;
}

int main() {
	
	int n, m;
    while (cin >> n >> m) {
        
        Grafo G(n);
        
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        
        if(coloreable(G)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
