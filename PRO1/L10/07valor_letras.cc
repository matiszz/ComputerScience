#include <iostream>
#include <vector>
using namespace std;

struct abc{
	int v;
	char l;
};

typedef vector<abc> ab;

void declarar() {
	ab(26);
	char c = 'a';
	
	for (int i = 0; i < 26; ++i) {
		ab[i].l = char(c + i);
		if (c + i == 'a' or c + i == 'e') ab[i].v = 1;
		else if (c + i == 'o' or c + i == 's') ab[i].v = 2;
		else if (c + i == 'd' or c + i == 'i' or c + i == 'n' or c + i == 'r') ab[i].v = 3;
		else if (c + i == 'c' or c + i == 'l' or c + i == 't' or c + i == 'u') ab[i].v = 4;
		else if (c + i == 'm' or c + i == 'p') ab[i].v = 5;
		else if (c + i == 'k' or c + i == 'w') ab[i].v = 7;
		else ab[i].v = 6;
		
	}
}

int main() {
	declarar();
	char c;
	while (cin >> c) {
		
	}
}
