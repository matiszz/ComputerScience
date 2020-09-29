  void concat(Cua &c)
  /* Pre: c=C */
  /* Post: el p.i. passa a ser la concatenació de C al paràmetre implícit, c és buida */
  {
	  if (c.longitud > 0 and longitud > 0) {
		  longitud += c.longitud;
		  ultim_node->seguent = c.primer_node;
		  ultim_node = c.ultim_node;
		  c.primer_node = NULL;
		  c.ultim_node = NULL;
		  c.longitud = 0;
	  }
	  if (longitud == 0) {
		  longitud = c.longitud;
		  primer_node = c.primer_node;
		  ultim_node = c.ultim_node;
		  c.primer_node = NULL;
		  c.ultim_node = NULL;
		  c.longitud = 0;
	  }
  }
