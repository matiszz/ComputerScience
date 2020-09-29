
node_llista* copia_node_llista_it (node_llista* m, node_llista* oact, node_llista* &u, node_llista* &a) {
	node_llista* n;
	a = NULL;
    if (m==NULL) {
		n = u = NULL;
		return NULL;
	} else {
		n = new node_llista;
		node_llista* aux;
		aux = n;
		n->info = m->info;
		n->ant = m->ant;
		m = m->seg;
		while (m != NULL) {
			node_llista* p;
			p = new node_llista;
			p->info = m->info;
			p->ant = aux;
			aux->seg = p;
			if (oact == m) a = aux;
			m = m->seg;
			aux = aux->seg;
		}
		aux->seg = NULL;
		u = aux;
	}
	return n;
}

Llista& operator=(const Llista& original) {
	if (this != &original) {
		longitud = original.longitud;
		esborra_node_llista(primer_node);
		primer_node = copia_node_llista_it(original.primer_node, original.act, ultim_node, act);
    }
    return *this;
}
