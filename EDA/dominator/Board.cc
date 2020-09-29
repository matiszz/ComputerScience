#include "Board.hh"
#include "Action.hh"


void Board::capture (int id, int pl, vector<bool>& killed) {
  Unit& u = unit_[id];
  _my_assert(u.player != pl, "Capturing own unit.");

  u.player = pl;
  u.health = (u.type == Farmer ? farmers_health() : knights_health());
  grid_[u.pos.i][u.pos.j].id = -1;
  killed[id] = true;
}


void Board::step (int id, Pos p2) {
  Unit& u = unit_[id];
  Pos p1 = u.pos;
  Cell& c1 = grid_[p1.i][p1.j];
  Cell& c2 = grid_[p2.i][p2.j];
  c1.id = -1;
  c2.id = id;
  u.pos = p2;
}


void Board::spell (int id, vector<bool>& killed) {
  Unit u = unit(id);
  vector<int> trap;
  bool own_trap = false;
  for (int x = -2; x <= 2; ++x)
    for (int y = -2; y <= 2; ++y)
      if (abs(x) + abs(y) <= 2) {
        int wt = witch_team(u.pos + Pos(x, y));
        if (wt == u.player) own_trap = true;
        else if (wt != -1) trap.push_back(wt);
      }

  if (not trap.empty()) {
    capture(id, trap[random(0, trap.size() - 1)], killed);
    return;
  }

  _my_assert(own_trap, "Unit killed by nobody.");

  capture(id, (u.player + random(1, 3))%4, killed);
}


// id is a valid unit id, moved by its player, and d is a valid dir != None.
bool Board::move (int id, Dir dir, vector<bool>& killed) {
  Unit& u = unit_[id];
  Pos p1 = u.pos;
  assert(pos_ok(p1));

  Cell& c1 = grid_[p1.i][p1.j];
  assert(c1.type == Empty);

  Pos p2 = p1 + dir;
  if (not pos_ok(p2)) return false;

  Cell& c2 = grid_[p2.i][p2.j];
  if (c2.type == Wall) return false;

  int id2 = c2.id;
  if (id2 == -1) {
    if (u.type == Witch) {
      step(id, p2);
      update_haunted();

      for (int i = 0; i < rows(); ++i)
        for (int j = 0; j < cols(); ++j) {
          int id = cell(i, j).id;
          if (id != -1 and cell(i, j).haunted and unit(id).type != Witch)
            spell(id, killed);
        }
      return true;
    }

    step(id, p2);
    if (c2.haunted) {
      spell(id, killed);
      return false;
    }

    if (u.type == Farmer) c2.owner = u.player;
    return true;
  }

  Unit& u2 = unit_[id2];

  if (u.type == Witch) {
    _my_assert(u2.type == Witch or not u.active,
               "Active witch adjacent to a non-witch.");
    return false;
  }

  if (u.type == Farmer) {
    _my_assert(u2.type != Witch or not u2.active,
               "Farmer adjacent to an active witch.");
    return false;
  }

  if (u2.type == Witch) {
    _my_assert(not u2.active, "Knight adjacent to an active witch.");
    return false;
  }

  if (u2.player == u.player) return false;

  u2.health -= random(damage_min(), damage_max());
  if (u2.health <= 0) capture(id2, u.player, killed);
  return true;
}


void Board::box (int pl, int& mini, int& maxi, int& minj, int& maxj) const {
  if ((pl + 1)%4 < 2) {
    mini = 1;
    maxi = rows()/2 - 2; // A bit of extra space for witches.
  }
  else {
    mini = rows()/2 + 2;
    maxi = rows() - 2;
  }
  if (pl < 2) {
    minj = 1;
    maxj = cols()/2 - 2;
  }
  else {
    minj = cols()/2 + 2;
    maxj = cols() - 2;
  }
}


inline bool Board::available (int i, int j) const {
  Cell c = cell(i, j);
  return c.type == Empty and c.id == -1 and not c.haunted;
}


inline int Board::witch_team (Pos pos) const {
  if (not pos_ok(pos)) return -1;
  int id = cell(pos).id;
  if (id == -1) return -1;
  if (unit(id).type == Witch and unit(id).active) return unit(id).player;
  return -1;
}


bool Board::pos_witch_ok (int i, int j) const {
  if (not available(i, j)) return false;

  for (int x = -3; x <= 3; ++x)
    for (int y = -3; y <= 3; ++y)
      if (abs(x) + abs(y) <= 3) {
        Pos p = Pos(i, j) + Pos(x, y);
        if (pos_ok(p)) {
          int id = cell(p).id;
          if (id != -1 and unit(id).type == Witch) return false;
        }
      }
  return true;
}


inline bool Board::ok_cell (int pl, Pos pos, bool knight) const {
  if (not pos_witch_ok(pos.i, pos.j)) return false;

  if (knight) {
    for (int d = 0; d < 8; ++d) {
      int id = cell(pos + Dir(d)).id;
      if (id != -1 and unit(id).player != pl) return false;
    }
    return true;
  }

  for (int d = 0; d < 8; d += 2) {
    int id = cell(pos + Dir(d)).id;
    if (id != -1 and unit(id).player != pl and unit(id).type == Knight)
      return false;
  }
  return true;
}


void Board::place (int id, Pos p) {
  unit_[id].pos = p;
  grid_[p.i][p.j].id = id;
  if (unit(id).type == Farmer) grid_[p.i][p.j].owner = unit(id).player;
}


void Board::spawn (const vector<Pos>& pos, const vector<int>& uni, int ini) {
  int num_p = pos.size();
  vector<int> perm = random_permutation(num_p);
  int num_u = uni.size();
  for (int k = ini; k < num_u and k < num_p; ++k) place(uni[k], pos[perm[k]]);
}


void Board::spawn_extras (const vector<int>& extra) {
  vector<Pos> pos;
  for (int i = 1; i < rows() - 1; ++i)
    for (int j = 1; j < cols() - 1; ++j)
      if (available(i, j)) pos.push_back(Pos(i, j));

  _my_assert(pos.size() >= extra.size(), "Evil disposition of units.");
  vector<int> perm_p = random_permutation((int)pos.size());
  for (int k = 0; k < (int)extra.size(); ++k) place(extra[k], pos[perm_p[k]]);
}


void Board::spawn_units (int pl, const vector<int>& uni, vector<int>& extra) {
  if (uni.empty()) return;

  int mini, maxi, minj, maxj;
  box(pl, mini, maxi, minj, maxj);

  bool knight = unit(uni[0]).type == Knight;
  vector<Pos> pos;
  for (int i = mini; i <= maxi; ++i)
    for (int j = minj; j <= maxj; ++j)
      if (ok_cell(pl, Pos(i, j), knight)) pos.push_back(Pos(i, j));

  spawn(pos, uni, 0);

  int num_u = uni.size();
  int num_p = pos.size();
  if (num_u > num_p) {
    cerr << "warning: more " << (knight ? "knights" : "farmers")
         << " than good reborn positions for player " << pl << endl;

    vector<Pos> pos2;
    for (int i = mini; i <= maxi; ++i)
      for (int j = minj; j <= maxj; ++j)
        if (available(i, j)) pos2.push_back(Pos(i, j));

    spawn(pos2, uni, num_p);

    int num_p2 = pos2.size();
    if (num_u > num_p + num_p2) {
      cerr << "warning: more " << (knight ? "knights" : "farmers")
           << " than free reborn positions for player " << pl << endl;

      for (int k = num_p + num_p2; k < num_u; ++k) extra.push_back(uni[k]);
    }
  }
}


void Board::spawn_witches (int pl, int& id) {
  int mini, maxi, minj, maxj;
  box(pl, mini, maxi, minj, maxj);

  for (int rep = 0; rep < nb_witches(); ++rep) {
    unit_[id] = Unit(Witch, id, pl, -1, Pos(-1, -1), true);
    int i, j;
    do {
      i = random(mini, maxi);
      j = random(minj, maxj);
    } while (not pos_witch_ok(i, j));

    for (int x = -2; x <= 2; ++x)
      for (int y = -2; y <= 2; ++y)
        if (abs(x) + abs(y) <= 2) {
          Pos p = Pos(i, j) + Pos(x, y);
          if (pos_ok(p)) grid_[p.i][p.j].haunted = true;
        }

    place(id, Pos(i, j));
    witches_[pl].push_back(id++);
  }
}


void Board::compute_scores () {
  land_ = vector<int>(nb_players(), 0);
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < cols(); ++j) {
      int ow = grid_[i][j].owner;
      assert(ow == -1 or player_ok(ow));
      if (player_ok(ow)) ++land_[ow];
    }

  for (int pl = 0; pl < nb_players(); ++pl) total_score_[pl] += land_[pl];
}


void Board::generate_units () {
  witches_ = vector< vector<int> >(nb_players());
  vector<int> extra;
  int id = 0;

  for (int pl = 0; pl < nb_players(); ++pl) {
    spawn_witches(pl, id);

    vector<int> knights;
    for (int rep = 0; rep < nb_knights(); ++rep) {
      unit_[id] = Unit(Knight, id, pl, knights_health());
      knights.push_back(id);
      ++id;
    }
    spawn_units(pl, knights, extra);
    _my_assert(extra.empty(), "Impossible to fit knights into grid.");

    vector<int> farmers;
    for (int rep = 0; rep < nb_farmers(); ++rep) {
      unit_[id] = Unit(Farmer, id, pl, farmers_health());
      farmers.push_back(id);
      ++id;
    }
    spawn_units(pl, farmers, extra);
    _my_assert(extra.empty(), "Impossible to fit farmers into grid.");
  }
}


Board::Board (istream& is, int seed) {
  set_random_seed(seed);
  *static_cast<Settings*>(this) = Settings::read_settings(is);
  names_ = vector<string>(nb_players());
  read_generator_and_grid(is);
  round_ = 0;
  land_ = vector<int>(nb_players(), 0);
  total_score_ = vector<int>(nb_players(), 0);
  cpu_status_ = vector<double>(nb_players(), 0);
  unit_ = vector<Unit>
          (nb_players()*(nb_farmers() + nb_knights() + nb_witches()));
  generate_units();
  update_vectors_by_player();
  compute_scores();
}


void Board::print_preamble (ostream& os) const {
  os << version() << endl;
  os << "nb_players     " << nb_players() << endl;
  os << "nb_rounds      " << nb_rounds() << endl;
  os << "nb_farmers     " << nb_farmers() << endl;
  os << "nb_knights     " << nb_knights() << endl;
  os << "nb_witches     " << nb_witches() << endl;
  os << "farmers_health " << farmers_health() << endl;
  os << "knights_health " << knights_health() << endl;
  os << "farmers_regen  " << farmers_regen() << endl;
  os << "knights_regen  " << knights_regen() << endl;
  os << "damage_min     " << damage_min() << endl;
  os << "damage_max     " << damage_max() << endl;
  os << "rows           " << rows() << endl;
  os << "cols           " << cols() << endl;
}


void Board::print_names (ostream& os) const {
  os << "names         ";
  for (int pl = 0; pl < nb_players(); ++pl) os << ' ' << name(pl);
  os << endl;
}


void Board::print_state (ostream& os) const {
  os << endl << endl;

  for (int i = 0; i < rows(); ++i) {
    for (int j = 0; j < cols(); ++j) {
      const Cell& c = grid_[i][j];
      if (c.type == Wall) os << 'X';
      else if (c.owner == -1) os << '.';
      else if (player_ok(c.owner)) os << c.owner;
      else assert(false);
    }
    os << endl;
  }

  os << endl;
  os << "round " << round() << endl;

  os << "land";
  for (auto la : land_) os << " " << la;
  os << endl;

  os << "total_score";
  for (auto ts : total_score_) os << " " << ts;
  os << endl;

  os << "status";
  for (auto st : cpu_status_) os << " " << st;
  os << endl;

  for (int id = 0; id < nb_units(); ++id) print_unit(unit(id), os);
  os << endl;
}


void Board::print_results () const {
  int max_score = 0;
  vector<int> v;
  for (int pl = 0; pl < nb_players(); ++pl) {
    cerr << "info: player " << name(pl)
         << " got score " << total_score(pl) << endl;
    if (total_score(pl) > max_score) {
      max_score = total_score(pl);
      v = vector<int>(1, pl);
    }
    else if (total_score(pl) == max_score) v.push_back(pl);
  }

  cerr << "info: player(s)";
  for (int pl : v) cerr << " " << name(pl);
  cerr << " got top score" << endl;
}


void Board::next (const vector<Action>& act, ostream& os) {
  ++round_;

  int np = nb_players();
  int nu = nb_units();

  // chooses (at most) one movement per unit
  vector<bool> seen(nu, false);
  vector<Movement> v;
  for (int pl = 0; pl < np; ++pl)
    for (const Movement& m : act[pl].v_) {
      int id = m.id;
      Dir dir = m.dir;
      if (not unit_ok(id)) cerr << "warning: id out of range :" << id << endl;
      else if (unit(id).player != pl)
        cerr << "warning: not own unit: " << id << ' ' << unit(id).player
             << ' ' << pl << endl;
      else {
        _my_assert(not seen[id], "More than one command for the same unit.");
        seen[id] = true;
        if (not dir_ok(dir))
          cerr << "warning: direction not valid: " << dir << endl;
        else if (dir%2 and unit(id).type != Knight)
          cerr << "warning: not horizontal or vertical dir: " << dir << endl;
        else if (dir != None) {
          dir = Dir((dir + 2*pl)%8);
          v.push_back(Movement(id, dir));
        }
      }
    }
  int num = v.size();

  // makes all movements using a random order
  vector<int> perm = random_permutation(num);
  vector<bool> moved(nu, false);
  vector<bool> killed(nu, false);
  vector<Movement> actions_done;
  for (int i = 0; i < num; ++i) {
    Movement m = v[perm[i]];
    moved[m.id] = true;
    if (not killed[m.id] and move(m.id, m.dir, killed))
      actions_done.push_back(m);
  }
  os << "movements" << endl;
  Action::print_actions(actions_done, os);

  // heals alive units that have not moved
  for (int id = 0; id < nu; ++id)
    if (not killed[id] and not moved[id]) {
      Unit& u = unit_[id];
      assert(ut_ok(u.type));
      if (u.type != Witch)
        u.health = (u.type == Farmer ?
                    min(u.health + farmers_regen(), farmers_health()) :
                    min(u.health + knights_regen(), knights_health()));
    }

  // spawns units
  vector< vector<int> > dead_f(nb_players());
  vector< vector<int> > dead_k(nb_players());
  for (int id = 0; id < nu; ++id)
    if (killed[id]) {
      UnitType t = unit(id).type;
      assert(ut_ok(t));
      _my_assert(t != Witch, "Witch killed.")
      (t == Farmer ? dead_f : dead_k)[unit(id).player].push_back(id);
    }

  vector<int> extra;
  for (int pl = 0; pl < np; ++pl) spawn_units(pl, dead_k[pl], extra);
  for (int pl = 0; pl < np; ++pl) spawn_units(pl, dead_f[pl], extra);

  // spawn extra units (for evil situations)
  spawn_extras(extra);

  update_vectors_by_player();

  compute_scores();
}


// ***************************************************************************


void Board::initial (int r, int c) {
  grid_ = vector< vector<Cell> >(r, vector<Cell>(c, char2cell('.')));
  for (int i = 0; i < r; ++i) grid_[i][0].type = grid_[i][c-1].type = Wall;
  for (int j = 0; j < c; ++j) grid_[0][j].type = grid_[r-1][j].type = Wall;
}


void Board::generator1 (vector<int> param) {
  int num = param.size();
  _my_assert(num >= 1 and num <= 2,
             "GENERATOR1 requires one or two parameters.");

  int r = rows();
  int c = cols();
  int q = param[0];
  _my_assert(q >= 0 and q <= r*c/10, "Wrong parameter of GENERATOR1.");

  if (num == 2) {
    int q2 = param[1];
    _my_assert(q2 >= q and q2 <= r*c/10, "Wrong parameter of GENERATOR1.");

    q = random(q, q2);
  }

  initial(r, c);

  while (q) {
    cerr << q << endl;
    int i = random(2, r - 3);
    int j = random(2, c - 3);
    bool ok = true;
    for (int x = -1; x <= 1; ++x)
      for (int y = -1; y <= 1; ++y)
        if (grid_[i+x][j+y].type == Wall) ok = false;
    if (ok) {
      grid_[i][j].type = Wall;
      --q;
    }
  }
}


Dir Board::left (Dir d) {
  return Dir((d + 2)%8);
}


Dir Board::right (Dir d) {
  return Dir((d + 6)%8);
}


bool Board::empty_line (Pos pos, Dir dir) const {
  for (int r = 0; r < 5; ++r) {
    if (not pos_ok(pos) or cell(pos).type == Wall) return false;
    pos += dir;
  }
  return true;
}


bool Board::ok_cell3 (Pos pos, Dir dir) const {
  pos += dir;
  if (not empty_line(pos, dir)) return false;
  if (not empty_line(pos, left(dir))) return false;
  if (not empty_line(pos, right(dir))) return false;
  Pos p1 = pos + dir + right(dir);
  if (not pos_ok(p1) or cell(p1).type == Wall) return false;
  Pos p2 = pos + dir + left(dir);
  if (not pos_ok(p2) or cell(p2).type == Wall) return false;
  return true;
}


bool Board::ok_cell2 (Pos pos) const {
  for (int i = -4; i <= 4; ++i)
    for (int j = -4; j <= 4; ++j) {
      Pos p = pos + Pos(i, j);
      if (pos_ok(p) and cell(p).type == Wall) return false;
    }
  return true;
}


vector<Pos> Board::candidate_cells () const {
  vector<Pos> r;
  for (int i = 4; i < rows() - 4; ++i)
    for (int j = 4; j < cols() - 4; ++j)
      if (ok_cell2(Pos(i, j))) r.push_back(Pos(i, j));
  return r;
}


bool Board::connected () const {
  vector< vector<int> > M(rows(), vector<int>(cols()));
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < cols(); ++j) M[i][j] = (grid_[i][j].type == Wall);

  queue<Pos> Q;
  M[1][1] = true;
  Q.push(Pos(1, 1));
  while (not Q.empty()) {
    Pos pos = Q.front(); Q.pop();
    for (int d = 0; d < 8; d += 2) {
      Pos p = pos + Dir(d);
      if (not M[p.i][p.j]) {
        M[p.i][p.j] = true;
        Q.push(p);
      }
    }
  }

  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < cols(); ++j)
      if (not M[i][j]) return false;
  return true;
}


void Board::generator2 (vector<int> param) {
  _my_assert(param.empty(), "GENERATOR2 requires no parameter.");

  int r = rows();
  int c = cols();

  initial(r, c);

  vector<Pos> vp;
  while (vp = candidate_cells(), not vp.empty()) {
    set<Pos> S;
    Pos pos = vp[random(0, vp.size() - 1)];
    S.insert(pos);
    grid_[pos.i][pos.j].type = Wall;
    Dir dir = Dir(2*random(0, 4));
    int steps = 0;
    while (++steps <= 15) {
      vector<Dir> v;
      if (ok_cell3(pos, dir)) v.push_back(dir);
      if (ok_cell3(pos, left(dir))) v.push_back(left(dir));
      if (ok_cell3(pos, right(dir))) v.push_back(right(dir));
      if (v.empty()) break;

      dir = v[random(0, v.size() - 1)];
      pos += dir;
      S.insert(pos);
      grid_[pos.i][pos.j].type = Wall;
    }

    for (Pos p : S) {
      bool ok = true;
      for (int i = -3; i <= 3; ++i)
        for (int j = -3; j <= 3; ++j) {
          Pos p2 = p + Pos(i, j);
          if (pos_ok(p2) and cell(p2).type == Wall and S.find(p2) == S.end())
            ok = false;
        }
      cerr << p << ' ' << ok << endl;
      if (not ok) grid_[p.i][p.j].type = Empty;
    }
  }

  for (int i = 1; i < rows() - 3; ++i)
    for (int j = 1; j < cols() - 3; ++j) {
      int i2 = i + 1;
      int j2 = j + 1;
      if (cell(i, j).type == Wall and cell(i, j2).type == Empty
          and cell(i2, j).type == Empty and cell(i2, j2).type == Wall) {
        if (random(0, 1)) grid_[i][j2].type = Wall;
        else grid_[i2][j].type = Wall;
      }
      if (cell(i, j).type == Empty and cell(i, j2).type == Wall
          and cell(i2, j).type == Wall and cell(i2, j2).type == Empty) {
        if (random(0, 1)) grid_[i][j].type = Wall;
        else grid_[i2][j2].type = Wall;
      }
    }

  if (not connected()) {
    cerr << "warning: unconected board discarted" << endl;
    generator2(param);
  }
}


int Board::repre (int x, vector<int>& pare) {
  return (pare[x] < 0 ? x : pare[x] = repre(pare[x], pare));
}


void Board::unpaint_wall (int i, int j, bool vert) {
  if (vert)
    for (int jj = 6*j + 1; jj < 6*j + 6; ++jj)
      grid_[6*i+6][jj].type = Empty;
  else
    for (int ii = 6*i + 1; ii < 6*i + 6; ++ii)
      grid_[ii][6*j+6].type = Empty;
}


bool Board::ok3_vert (int i, int j) const {
  int j1 = 6*j;
  int j2 = j1 + 6;
  int ii = 6*i + 6;
  bool ok1 = false;
  if (j1 > 0 and grid_[ii][j1-1].type == Wall) ok1 = true;
  if (grid_[ii-1][j1].type == Wall) ok1 = true;
  if (grid_[ii+1][j1].type == Wall) ok1 = true;
  bool ok2 = false;
  if (j2 + 1 < cols() and grid_[ii][j2+1].type == Wall) ok2 = true;
  if (grid_[ii-1][j2].type == Wall) ok2 = true;
  if (grid_[ii+1][j2].type == Wall) ok2 = true;
  return ok1 and ok2;
}


bool Board::ok3_hori (int i, int j) const {
  int i1 = 6*i;
  int i2 = i1 + 6;
  int jj = 6*j + 6;
  bool ok1 = false;
  if (i1 > 0 and grid_[i1-1][jj].type == Wall) ok1 = true;
  if (grid_[i1][jj-1].type == Wall) ok1 = true;
  if (grid_[i1][jj+1].type == Wall) ok1 = true;
  bool ok2 = false;
  if (i2 + 1 < rows() and grid_[i2+1][jj].type == Wall) ok2 = true;
  if (grid_[i2][jj-1].type == Wall) ok2 = true;
  if (grid_[i2][jj+1].type == Wall) ok2 = true;
  return ok1 and ok2;
}


void Board::generator3 (vector<int> param) {
  _my_assert(param.empty(), "GENERATOR3 requires no parameter.");

  int r = rows();
  int c = cols();
  _my_assert(r%6 == 1 and c%6 == 1, "GENERATOR3 needs dimensions 1 mod 6.");

  initial(r, c);

  for (int i = 6; i < r; i += 6)
    for (int j = 1; j < c; ++j) grid_[i][j].type = Wall;
  for (int i = 1; i < r; ++i)
    for (int j = 6; j < c; j += 6) grid_[i][j].type = Wall;

  int rr = r/6;
  int cc = c/6;
  vector<int> pare(rr*cc, -1);

  vector<P> v;
  for (int i = 0; i < rr; ++i)
    for (int j = 0; j < cc - 1; ++j)
      v.push_back(P(Pos(i, j), false));
  for (int i = 0; i < rr - 1; ++i)
    for (int j = 0; j < cc; ++j)
      v.push_back(P(Pos(i, j), true));
  int num = v.size();
  vector<int> perm = random_permutation(num);

  vector<P> rest;
  for (int k = 0; k < num; ++k) {
    P a = v[perm[k]];
    int i = a.first.i;
    int j = a.first.j;
    bool vert = a.second;
    int x = i*cc + j;
    int y = x + (vert ? cc : 1);
    int rx = repre(x, pare);
    int ry = repre(y, pare);
    if (rx != ry) {
      pare[ry] = rx;
      unpaint_wall(i, j, vert);
    }
    else rest.push_back(a);
  }

  _my_assert((int)rest.size() >= rr + cc, "GENERATOR3 needs bigger board.");
  for (int k = 0; k < rr + cc; ++k) {
    P a = rest[k];
    int i = a.first.i;
    int j = a.first.j;
    bool vert = a.second;
    if (vert) {
      if (ok3_vert(i, j)) unpaint_wall(i, j, vert);
    }
    else {
      if (ok3_hori(i, j)) unpaint_wall(i, j, vert);
    }
  }
}
