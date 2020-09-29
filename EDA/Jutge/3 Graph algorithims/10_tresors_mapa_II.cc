/*
 * Created by Matias Szarfer - 2016
 * 
 * Donat n files, m columnes, el Mapa on
 *                                      t = tresor;
 *                                      X = obstacle;
 *                                      . = buit;
 * f i c que indiquen posició inicial.
 * Escriure la distància mínima per arribar desde f,c a un tresor t.
 */

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

typedef vector< vector<int> > MD;
typedef vector< vector<bool> > MB;
typedef vector< vector<char> > Mapa;
typedef queue< pair<int,int> > Cola;
typedef pair<int,int> Pair;

void leer (Mapa& M, int n, int m, int& f, int& c) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> M[i][j];
	}
	cin >> f >> c;
}

int bfs (Mapa& M, int f, int c) {
    
    int n = M.size();
    int m = M[0].size();
    
    MD D(n, vector<int>(m, -1));
    Cola Q;
    
    D[f][c] = 0;
    Q.push(make_pair(f,c));
    
    while (not Q.empty()) {
        Pair p = Q.front();
        Q.pop();
        
        int x = p.first; int y = p.second;
        
        if (M[x][y] == 't') return D[x][y];
        else {
            
            if (D[x+1][y] == -1 and M[x+1][y] != 'X') {
                Q.push(make_pair(x+1,y));
                D[x+1][y] = D[x][y]+1;
            }
            
            if (D[x-1][y] == -1 and M[x-1][y] != 'X') {
                Q.push(make_pair(x-1,y));
                D[x-1][y] = D[x][y]+1;
            }
            
            if (D[x][y+1] == -1 and M[x][y+1] != 'X') {
                Q.push(make_pair(x,y+1));
                D[x][y+1] = D[x][y]+1;
            }
            
            if (D[x][y-1] == -1 and M[x][y-1] != 'X') {
                Q.push(make_pair(x,y-1));
                D[x][y-1] = D[x][y]+1;
            }
        }
    }
    return -1;
}

int main() {
	
	int n, m, f, c;
    cin >> n >> m;
    
    Mapa M(n+2, vector<char>(m+2, 'X'));
    
    leer(M, n, m, f, c);
    
    int min_dist = bfs(M, f, c);
    
    if (min_dist == -1) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia minima: " << min_dist << endl;
}

