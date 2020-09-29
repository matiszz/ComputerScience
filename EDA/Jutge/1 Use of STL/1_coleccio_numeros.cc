#include <queue>
#include <iostream>
using namespace std;

int main() {
	priority_queue<int> Q;
	char c;
	int x;
	
	while (cin >> c) {
		if (c == 'S') {
			cin >> x;
			Q.push(x);
		}
		if (c == 'A') {
			if (not Q.empty()) cout << Q.top() << endl;
			else cout << "error!" << endl;
		}
		if (c == 'R') {
			if (not Q.empty()) Q.pop();
			else cout << "error!" << endl;
		}
		if (c == 'I') {
			if (not Q.empty()) {
				cin >> x;
				x = Q.top() + x;
				Q.pop();
				Q.push(x);
			} else cout << "error!" << endl;
		}
		if (c == 'D') {
			if (not Q.empty()) {
				cin >> x;
				x = Q.top() - x;
				Q.pop();
				Q.push(x);
			} else cout << "error!" << endl;
		}
	}
}
