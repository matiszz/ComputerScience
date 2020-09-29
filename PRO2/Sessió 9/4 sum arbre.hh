
void arb_sumes(Arbre<int> &asum) {
	int s;
	asi(primer_node, asum.primer_node, s);
}

void asi(node_arbre* m, node_arbre*& n, int& s) {
	if (m == NULL) { n = NULL; s = 0; }
	else {
		n = new node_arbre;
		int se, sd;
		asi(m->segE, n->segE, se);
		asi(m->segD, n->segD, sd);
		s = m->info + sd + se;
		n->info = s;
	}
}
