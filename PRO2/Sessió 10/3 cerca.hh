
bool buscar(const T& x) const {
	return buscar_i(x, primer_node);
}

static bool buscar_i(const T& x, node_arbreGen*& m) {
	if (m == NULL) return false;
	else {
		if (m->info == x) return true;
		else {
			for (int i = 0; i < m->seg.size(); ++i) {
				if (buscar_i(x, m->seg[i]) == true) return true;
			}
		}
	}
	return false;
}
