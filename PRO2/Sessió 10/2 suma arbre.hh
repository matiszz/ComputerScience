
void arbsuma(ArbreNari& asum) {
	int s;
	suma_imm(primer_node, asum.primer_node, s);
}

void suma_imm(node_arbreNari* m, node_arbreNari*& n, int& s) {
	if (m == NULL) { s = 0; n = NULL; }
	else {
		n = new node_arbreNari;
		n->seg = vector<node_arbreNari*>(N);
		vector<int> sum (N);
		for (int i = 0; i < n->seg.size(); ++i) suma_imm(m->seg[i], n->seg[i], sum[i]);
		for (int j = 0; j < n->seg.size(); ++j) s = m->info + sum[j] + s;
		n->info = s;
	}
}
