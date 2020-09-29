/*
 * Created by Matias Szarfer - 2016
 * Donat un mapa amb tresors, dir distancia del tresor mes llunya.
 */

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

typedef vector< char > Row;
typedef vector< Row > Mapa;
typedef vector< vector<int> > MapaDist;
typedef pair<int, int> Pos;

Mapa M;
int n, m, f, c;

void leer() {
    
    cin >> n >> m;
    M = Mapa(n+2, Row(m+2, 'X'));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> M[i][j];
        }
    }
    cin >> f >> c;
}

int bfs() {
    
    MapaDist D(n+2, vector<int>(m+2, -1));
    queue<Pos> Q;
    
    D[f][c] = 0;
    Q.push(make_pair(f,c));
    
    int maxDist = 0;
    bool encontrado = false;
    
    while(not Q.empty()) {
        Pos p = Q.front();
        Q.pop();
        
        int x = p.first; int y = p.second; int xx, yy;
        
        if (M[x][y] == 't') {
            if(D[x][y] > maxDist) {
                maxDist = D[x][y];
                encontrado = true;
            }
        }
        // No queremos que sea un else, queremos que siga buscando.
        xx = x+1; yy = y;
        if (D[xx][yy] == -1 and M[xx][yy] != 'X') {
            Q.push(make_pair(xx,yy));
            D[xx][yy] = D[x][y] + 1;
        }
        
        xx = x-1; yy = y;
        if (D[xx][yy] == -1 and M[xx][yy] != 'X') {
            Q.push(make_pair(xx,yy));
            D[xx][yy] = D[x][y] + 1;
        }
        
        xx = x; yy = y+1;
        if (D[xx][yy] == -1 and M[xx][yy] != 'X') {
            Q.push(make_pair(xx,yy));
            D[xx][yy] = D[x][y] + 1;
        }
        
        xx = x; yy = y-1;
        if (D[xx][yy] == -1 and M[xx][yy] != 'X') {
            Q.push(make_pair(xx,yy));
            D[xx][yy] = D[x][y] + 1;
        }
    }
    if (encontrado) return maxDist;
    else return -1;
}

int main() {
    leer();
    
    int dist = bfs();
    
    if (dist == -1) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia maxima: " << dist << endl;
}
