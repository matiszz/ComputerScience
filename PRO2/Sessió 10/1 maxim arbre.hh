
T maxim() {
	T max = primer_node->info;
	node_arbreNari* n;
	n = primer_node;
	return maxim_imm(n, max);
}

T maxim_imm(node_arbreNari* n, T& max) {
	if (n != NULL) {
		for (int i = 0; i < N; ++i) {
			if (max < n->info) max = n->info;
			max = maxim_imm(n->seg[i], max);
		}
		return max;
	}
	return max;
}
