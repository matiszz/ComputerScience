#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Matias Szarfer Barenblit
// PRE: Nombre n, seguit de n paraules.
// POST: Retornar paraules ordenades amb el nombre de cops que apareixen. 10 "-" entre llista i llista
 
struct Item { string word; int num; };

typedef vector<Item> Things;

bool criteria(const Item& a,const Item& b) {
	if (a.num > b.num) return true;
	if (a.num < b.num) return false;
	return (a.word < b.word);
}

int main() {
	int n;
	while (cin >> n) {
		
		
		vector<string> vec1(n);
		
		for(int i = 0; i < n; ++i) cin >> vec1[i]; //Construir vec1
		sort(vec1.begin(), vec1.end()); //Ordenar vec1
		
		Things vec2(n);
		
		vec2[0].word = vec1[0]; //Paraula 0
		
		int r = 0;
		
		for (int i = 0; i < n; ++i) {
			if (vec2[r].word != vec1[i]) {
				r = r + 1;
				vec2[r].word = vec1[i];
				vec2[r].num = 1;
			}
			else vec2[r].num = vec2[r].num + 1;
		}
		
		Things vec3(r + 1);
		
		for (int i = 0; i < r + 1; ++i) {
			vec3[i].word = vec2[i].word;
			vec3[i].num = vec2[i].num;
		}
		
		sort(vec3.begin(), vec3.end(), criteria);
		for(int i = 0; i < r+1; ++i) {
			cout << vec3[i].num << " " << vec3[i].word << endl;
		}
		cout << "----------" << endl;	
	}
}
