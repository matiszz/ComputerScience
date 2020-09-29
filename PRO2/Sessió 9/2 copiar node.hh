
node_pila* copia_node_pila_it(node_pila* m) {
	node_pila* n;
	if (m == NULL) n=NULL;
	else {
	n = new node_pila;
	node_pila* aux;
	aux = n;
	n->info = m->info;
	m = m->seguent;
	while (m != NULL) {
			node_pila* p;
			p = new node_pila;
			p->info = m->info;
			aux->seguent = p;
			m = m->seguent;
			aux = aux->seguent;
		}
		aux->seguent = NULL;
	}
	return n;
}

Pila& operator=(const Pila& original) {
	if (this != &original) {
		altura = original.altura;
		esborra_node_pila(primer_node);
		primer_node = copia_node_pila_it(original.primer_node);
    }
	return *this;
}
