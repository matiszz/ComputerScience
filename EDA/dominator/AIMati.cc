#include "Player.hh"
#define PLAYER_NAME Mati

struct PLAYER_NAME : public Player {
    
    /* ::: factory() devuelve una nueva instancia de esta clase. No modificar ::: */
    static Player* factory () { return new PLAYER_NAME; }

    /* ::: Definir aqui los types y atributos ::: */
    typedef vector<int> VI;
    typedef vector<Dir> VD;
    typedef vector<Pos> VP;
    typedef vector< vector<int> > MI;
    typedef vector< vector<bool> > MB;
    typedef vector< vector<Cell> > MC;
    typedef queue< pair <Pos,Dir> > CP;
    
    int MARGEN = 4;
    int RANGO_W = 2;
    int MARGEN_W = 3;
    int bruja1 = -1;
    int bruja2 = -2;
    
    bool llegao = true;
    
    /* ::: Mis funciones aquí ::: */
    bool estoyDentro(int x, int y) {
        return (x >= 0 && x < 37 && y >= 0 && y < 37);
    }
    
    // Número de tropas en un Ã¡rea delimitada por RANGO_W de una Cell.
    int num_tropas(int x, int y) {
        int t = 0;
        for (int i = x-RANGO_W; i < x+RANGO_W; ++i) {
            for (int j = y-RANGO_W; j < y+RANGO_W; ++j) {
                if (estoyDentro(i,j) && cell(i,j).id != -1 && unit(cell(i,j).id).player != 0) ++t;
            }
        }
        return t;
    }
    
    bool tropasCerca(int x, int y) {
        for (int i = x-MARGEN; i < x+MARGEN; ++i) {
            for (int j = y-MARGEN; j < y+MARGEN; ++j) {
                if (estoyDentro(i,j) && cell(i,j).id != -1 && unit(cell(i,j).id).player == 0) return true;
            }
        }
        return false;
    }

    Dir goTo(int x, int y, int l, int s, MC& Mapa) {
        MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first;
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            
            if (a == l && b == s) return dir_aux;
            else {
				// TOP
				Pos paux = p + Top;
				Cell caux = Mapa[paux.i][paux.j];
				int xx = a - 1;
				int yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall) {
					if (primero) dir_aux = Top;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// LEFT
				paux = p + Left;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall) {
					if (primero) dir_aux = Left;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// BOTTOM
				paux = p + Bottom;
				caux = Mapa[paux.i][paux.j];
				xx = a + 1;
				yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall) {
					if (primero) dir_aux = Bottom;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// RIGHT
				paux = p + Right;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall) {
					if (primero) dir_aux = Right;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				primero = false;
			}
        }
        return None;
    }

    Dir farmear(int x, int y, MC& Mapa) {
		
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias.
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first; // p es la pos de la primera que estaba en la cola.
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
            
            if (c.id == -1 && c.owner != 0) return dir_aux; // Si esta ya es buena, devuelve como llegar.
            else {
				// BOTTOM
				Pos paux = p + Bottom;
				Cell caux = Mapa[paux.i][paux.j];
				int xx = a + 1;
				int yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted && estoyDentro(xx,yy)) {
					if (primero) dir_aux = Bottom;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// RIGHT
				paux = p + Right;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted && estoyDentro(xx,yy)) {
					if (primero) dir_aux = Right;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// TOP
				paux = p + Top;
				caux = Mapa[paux.i][paux.j];
				xx = a - 1;
				yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted && estoyDentro(xx,yy)) {
					if (primero) dir_aux = Top;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// LEFT
				paux = p + Left;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted && estoyDentro(xx,yy)) {
					if (primero) dir_aux = Left;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				primero = false;
			}
        }
        return None;
    }
	
	Dir caballear(int x, int y, MC& Mapa) {
		
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first;
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
          /*  Pos p2 = cola.front().first;
            Dir dir_aux2 = cola.front().second;
            cola.pop();
            int a2 = p2.i;
            int b2 = p2.j;
            Cell c2 = Mapa[p2.i][p2.j]; */
            
            if (c.id != -1 && (unit(c.id).type == Farmer || unit(c.id).type == Knight) && unit(c.id).player != 0) {
             /*   if (posiciones[a][b] < posiciones[a2][b2]) */return dir_aux;
               /* else if (posiciones[a][b] > posiciones[a2][b2]) return dir_aux2;
                else {
                    if(unit(c.id).health <= unit(c2.id).health) return dir_aux;
                    else return dir_aux2;
                }*/
            } else {
				// BOTTOM
				Pos paux = p + Bottom;
				Cell caux = Mapa[paux.i][paux.j];
				int xx = a + 1;
				int yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = Bottom;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// RIGHT
				paux = p + Right;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = Right;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// Right-Bottom
				paux = p + BR;
				caux = Mapa[paux.i][paux.j];
				xx = a + 1;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = BR;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// LEFT
				paux = p + Left;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = Left;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// Left-Bottom
				paux = p + LB;
				caux = Mapa[paux.i][paux.j];
				xx = a + 1;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = LB;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// TOP
				paux = p + Top;
				caux = Mapa[paux.i][paux.j];
				xx = a - 1;
				yy = b + 0;				
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = Top;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// Right-Top
				paux = p + RT;
				caux = Mapa[paux.i][paux.j];
				xx = a - 1;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = RT;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// Left-Top
				paux = p + TL;
				caux = Mapa[paux.i][paux.j];
				xx = a - 1;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
					if (primero) dir_aux = TL;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				primero = false;
			}
        }
        return None;
    }
	
	Dir brujear(int x, int y, MC& Mapa, int bruja) {
        
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first;
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
            
            if (c.id != -1 && (unit(c.id).type == Knight || unit(c.id).type == Farmer)
                && unit(c.id).player != 0 && tropasCerca(a,b)){ //&& bruja1 != bruja2) {
                //~ if (bruja == 1) bruja1 = c.id;
                //~ if (bruja == 2) bruja2 = c.id;
                return dir_aux;
            } else {
				// TOP
				Pos paux = p + Top;
				Cell caux = Mapa[paux.i][paux.j];
				int xx = a - 1;
				int yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
					if (primero) dir_aux = Top;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
                
				// LEFT
				paux = p + Left;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b - 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
					if (primero) dir_aux = Left;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// BOTTOM
				paux = p + Bottom;
				caux = Mapa[paux.i][paux.j];
				xx = a + 1;
				yy = b + 0;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
					if (primero) dir_aux = Bottom;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				// RIGHT
				paux = p + Right;
				caux = Mapa[paux.i][paux.j];
				xx = a + 0;
				yy = b + 1;
				if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
					if (primero) dir_aux = Right;
					cola.push(make_pair(paux, dir_aux));
					posiciones[xx][yy] = posiciones[a][b]+1;
				}
				
				primero = false;
			}
        }
        return None;
    }
	
	Dir escapar_farmer(int x, int y, MC& Mapa, Dir direccion) {
		
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias.
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first; // p es la pos de la primera que estaba en la cola.
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
            
            if (c.id == -1 && c.owner != 0) return dir_aux; // Si esta ya es buena, devuelve como llegar.
            else {
				Pos paux; Cell caux; int xx, yy;
				if (direccion != Bottom) {
					// BOTTOM
					paux = p + Bottom;
					caux = Mapa[paux.i][paux.j];
					xx = a + 1;
					yy = b + 0;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted) {
						if (primero) dir_aux = Bottom;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Right) {
					// RIGHT
					paux = p + Right;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b + 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted) {
						if (primero) dir_aux = Right;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Top) {
					// TOP
					paux = p + Top;
					caux = Mapa[paux.i][paux.j];
					xx = a - 1;
					yy = b + 0;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted) {
						if (primero) dir_aux = Top;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Left) {
					// LEFT
					paux = p + Left;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b - 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && caux.id == -1 && not caux.haunted) {
						if (primero) dir_aux = Left;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				primero = false;
			}
        }
        return None;
    }
	
	Dir escapar_knight(int x, int y, MC& Mapa, Dir direccion) {
		
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first;
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
            
            if (c.id != -1 && (unit(c.id).type == Farmer || unit(c.id).type == Knight) && unit(c.id).player != 0) return dir_aux; // Si esta ya es buena, devuelve como llegar.
            else {
				Pos paux; Cell caux; int xx, yy;
				if (direccion != Bottom) {
					// BOTTOM
					paux = p + Bottom;
					caux = Mapa[paux.i][paux.j];
					xx = a + 1;
					yy = b + 0;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = Bottom;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Right) {
					// RIGHT
					paux = p + Right;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b + 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = Right;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Bottom && direccion != Right) {
					// Right-Bottom
					paux = p + BR;
					caux = Mapa[paux.i][paux.j];
					xx = a + 1;
					yy = b + 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = BR;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Left) {
					// LEFT
					paux = p + Left;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b - 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = Left;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
					
				if (direccion != Left && direccion != Bottom) {
					// Left-Bottom
					paux = p + LB;
					caux = Mapa[paux.i][paux.j];
					xx = a + 1;
					yy = b - 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = LB;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
					
				if (direccion != Top) {
					// TOP
					paux = p + Top;
					caux = Mapa[paux.i][paux.j];
					xx = a - 1;
					yy = b + 0;				
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = Top;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Right && direccion != Top) {
					// Right-Top
					paux = p + RT;
					caux = Mapa[paux.i][paux.j];
					xx = a - 1;
					yy = b + 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = RT;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Left && direccion != Top) {					
					// Left-Top
					paux = p + TL;
					caux = Mapa[paux.i][paux.j];
					xx = a - 1;
					yy = b - 1;
					if (posiciones[xx][yy] == -1 && caux.type != Wall && not caux.haunted) {
						if (primero) dir_aux = TL;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				primero = false;
			}
        }
        return None;
    }
	
    Dir escapar_bruja(int x, int y, MC& Mapa, Dir direccion, int bruja) {
		
		MI posiciones(cols(), vector<int> (rows(), -1)); // Matriz con las distancias.
		CP cola;
		Dir dir = None;
        
        Pos p;
        p.i = x;
        p.j = y;
		bool primero = true;
        
        posiciones[x][y] = 0;
        cola.push(make_pair(p, dir));
        
        while (not cola.empty()) {
			
            p = cola.front().first; // p es la pos de la primera que estaba en la cola.
            Dir dir_aux = cola.front().second;
            cola.pop();
            int a = p.i;
            int b = p.j;
            Cell c = Mapa[p.i][p.j];
            
            if (c.id != -1 && (unit(c.id).type == Knight || unit(c.id).type == Farmer)
                && unit(c.id).player != 0 && tropasCerca(a,b) && bruja1 != bruja2) {
                if (bruja == 1) bruja1 = c.id;
                if (bruja == 2) bruja2 = c.id;
                return dir_aux;
            }
            else {
				Pos paux; Cell caux; int xx, yy;
				if (direccion != Bottom) {
					// BOTTOM
					paux = p + Bottom;
					caux = Mapa[paux.i][paux.j];
					xx = a + 1;
					yy = b + 0;
                    if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
						if (primero) dir_aux = Bottom;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Right) {
					// RIGHT
					paux = p + Right;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b + 1;
                    if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
						if (primero) dir_aux = Right;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Top) {
					// TOP
					paux = p + Top;
					caux = Mapa[paux.i][paux.j];
					xx = a - 1;
					yy = b + 0;
                    if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
						if (primero) dir_aux = Top;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				
				if (direccion != Left) {
					// LEFT
					paux = p + Left;
					caux = Mapa[paux.i][paux.j];
					xx = a + 0;
					yy = b - 1;
                    if (posiciones[xx][yy] == -1 && caux.type != Wall && tropasCerca(xx,yy)) {
						if (primero) dir_aux = Left;
						cola.push(make_pair(paux, dir_aux));
						posiciones[xx][yy] = posiciones[a][b]+1;
					}
				}
				primero = false;
			}
        }
        return None;
    }
	
	// Dice si a dist casillas de (x,y) hay una bruja, y en que direcciÃ³n.
	bool brujaCerca(int x, int y, Dir& dir) {
        // Right
        for (int i = 0; i <= MARGEN; ++i){
            if (estoyDentro(x,y+i) && cell(x,y+i).haunted) {
                dir = Right;
                return true;
            }
        }
        // Bot
        for (int i = 0; i <= MARGEN; ++i){
            if (estoyDentro(x+i,y) && cell(x+i,y).haunted) {
                dir = Bottom;
                return true;
            }
        }
        // Left
        for (int i = 0; i <= MARGEN; ++i){
            if (estoyDentro(x,y-i) && cell(x,y-i).haunted) {
                dir = Left;
                return true;
            }
        }
        // Top
        for (int i = 0; i <= MARGEN; ++i){
            if (estoyDentro(x-i,y) && cell(x-i,y).haunted) {
                dir = Top;
                return true;
            }
        }
        return false;
	}
	
    bool tropasNear(int x, int y, Dir& dir) {
        // Right
        for (int i = 0; i <= MARGEN_W; ++i){
            if (estoyDentro(x,y+i) && cell(x,y+i).id != -1 && unit(cell(x,y+i).id).player == 0) {
                dir = Right;
                return true;
            }
        }
        // Bot
        for (int i = 0; i <= MARGEN_W; ++i){
            if (estoyDentro(x+i,y) && cell(x+i,y).id != -1 && unit(cell(x+i,y).id).player == 0) {
                dir = Bottom;
                return true;
            }
        }
        // Left
        for (int i = 0; i <= MARGEN_W; ++i){
            if (estoyDentro(x,y-i) && cell(x,y-i).id != -1 && unit(cell(x,y-i).id).player == 0) {
                dir = Left;
                return true;
            }
        }
        // Top
        for (int i = 0; i <= MARGEN_W; ++i){
            if (estoyDentro(x-i,y) && cell(x-i,y).id != -1 && unit(cell(x-i,y).id).player == 0) {
                dir = Top;
                return true;
            }
        }
        return false;
	}
	
	void moverBrujas(MC& Mapa) {
		VI brujas = witches(0);
        Dir dir, direccion;
        int siguiendo;
        
        
        // Bruja arriba
        int id = brujas[0];
        int x = unit(id).pos.i;
        int y = unit(id).pos.j;
        
        //~ if (x == 20 && y == 3) llegao = false;
        //~ else if (llegao && x != 20 && y != 3)   dir = goTo(x, y, 20, 3, Mapa);
        //~ else 
        //~ if (tropasNear(x, y, direccion))   dir = escapar_bruja(x, y, Mapa, direccion, 1);
        //~ else                                    
        dir = brujear(x, y, Mapa, 1);
        command(id, dir);
        
        // Bruja abajo
        id = brujas[1];
        x = unit(id).pos.i;
        y = unit(id).pos.j;
        
        //~ if (x == 3 && y == 20) llegao = false;
        //~ else if (llegao && x != 3 && y != 20)   dir = goTo(x, y, 3, 20, Mapa);
        //~ else 
        //~ if (tropasNear(x, y, direccion))   dir = escapar_bruja(x, y, Mapa, direccion, 2);
        //~ else
                                            dir = brujear(x, y, Mapa, 2);
        command(id, dir);
	}
	
	void moverFarmers(MC& Mapa) {
		VI farm = farmers(0);
        
        for (int id : farm) {
            int x = unit(id).pos.i;
            int y = unit(id).pos.j;
            Dir direccion = None;
            MB visto (cols(), vector<bool> (rows(), false));
            
            if (not brujaCerca(x, y, direccion)) {
                Dir dir = farmear(x, y, Mapa);
				command(id, dir);
			} else {
                Dir dir = escapar_farmer(x, y, Mapa, direccion);
				command(id, dir);
			}
        }
	}
	
	void moverKnights(MC& Mapa) {
		VI caballeros = knights(0);
        
        for (int id : caballeros) {
            int x = unit(id).pos.i;
            int y = unit(id).pos.j;
            Dir direccion = None;
            
            if (not brujaCerca(x, y, direccion)) {
				Dir dir = caballear(x, y, Mapa);
				command(id, dir);
			} else {
				Dir dir = escapar_knight(x, y, Mapa, direccion);
				command(id, dir);
			}
        }
	}
	
    /* ::: Método play, se invoca una vez por cada ronda. ::: */
    void play () {
        
        MC Mapa (cols(), vector<Cell> (rows()));
        for (int i = 0; i < cols(); ++i) {
            for (int j = 0; j < rows(); ++j) {
                Mapa[i][j] = cell(i,j);
            }
        }
        
        moverBrujas(Mapa);
        moverFarmers(Mapa);
        moverKnights(Mapa);
    }
};


/* ::: No modificar! ::: */
RegisterPlayer(PLAYER_NAME);

