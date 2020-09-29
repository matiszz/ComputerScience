#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector< vector<int> > Graf;

// dfs iteratiu
void recorregut_aux(Graf& G, int i, vector<bool>& vist) {
	
	stack<int> S;
	S.push(i);
	vist[i] = true;
	
	while(not S.empty()) {
		int v = S.top();
		S.pop();
		for (int u = 0; u < G[v].size(); ++u) {
			if (not vist[G[v][u]]) {
				vist[G[v][u]] = true;
				S.push(G[v][u]);
			}
		}
	}
}

int comp_connex(Graf & G) {
	
	int n = G.size();
	int cc = 0;
	vector<bool> vist(n, false);
	
	for (int i = 0; i < n; ++i) {
		if (not vist[i]) {
			++cc;
			recorregut_aux(G, i, vist);
		}
	}
	
	return cc;
}

int main() {
	int n, m;
	
	while (cin >> n >> m) {
		Graf G(n);
		
		for (int i = 0; i < m; ++i) {
			int j, k;
			cin >> j >> k;
			G[j].push_back(k);
			G[k].push_back(j);
		}
		int cc = comp_connex(G);
		
		if (n - cc == m) cout << cc << endl;
		else cout << "no" << endl;
	}
}


