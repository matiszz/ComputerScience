
int freq(const T& x) {
	return freq_imm(primer_node, x);
}

int freq_imm(node_arbreGen* n, const T& x) {
	int num = 0;
	if (n == NULL) return 0;
	else {
		if (n->info == x) ++num;
		for (int i = 0; i < n->seg.size(); ++i)
			num += freq_imm(n->seg[i], x);
	}
	return num;
}
