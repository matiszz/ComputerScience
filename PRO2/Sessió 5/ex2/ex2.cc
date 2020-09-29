#include <iostream>
#include <stack>
using namespace std;

int main() {
	stack<char> p;
	char c;
	bool error = false;
	
	cin >> c;
	while (c != '.' and not error) {
		if (c == '(' or c == '[') p.push(c);
		else if (p.empty()) error = true;
		else if (c == ')') {
			if (p.top() == '(') p.pop();
			else if (p.top() == '[') error = true;
		} else if (c == ']') {
			if (p.top() == '[') p.pop();
			else if (p.top() == ')') error = true;
		}
		cin >> c;
	}
	
	if (error) cout << "Incorrecte" << endl;
	else cout << "Correcte" << endl;
}
