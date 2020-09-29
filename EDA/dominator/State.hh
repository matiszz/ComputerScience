#ifndef State_hh
#define State_hh


#include "Structs.hh"


/*! \file
 * Contains a class to store the current state of a game.
 */


/**
 * Stores the game state.
 */
class State {

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  vector< vector<Cell> > grid_;
  int round_;
  vector<Unit> unit_;
  vector<int> land_;
  vector<int> total_score_;
  vector<double> cpu_status_; // -1 -> dead, 0..1 -> % of cpu time limit
  vector< vector<int> > farmers_;
  vector< vector<int> > knights_;
  vector< vector<int> > witches_;

  /**
   * Returns whether id is a valid unit identifier.
   */
  inline bool unit_ok (int id) const {
    return id >= 0 and id < nb_units();
  }

  static void rota (int& pl, int k) {
    pl = (pl + 4 - k)%4;
  }

  void rotate (vector< vector<Cell> >& g, vector<Unit>& u, int k) const {
    int n = g.size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        Pos p;
        if (k == 1) p = Pos(n - j - 1, i);
        else if (k == 2) p = Pos(n - i - 1, n - j - 1);
        else p = Pos(j, n - i - 1);

        g[i][j] = grid_[p.i][p.j];
        int& ow = g[i][j].owner;
        if (ow != -1) rota(ow, k);
        int id = g[i][j].id;
        if (id != -1) {
          rota(u[id].player, k);
          u[id].pos = Pos(i, j);
        }
      }
  }

public:

  /**
   * Returns the current round.
   */
  inline int round () const {
    return round_;
  }

  /**
   * Returns a copy of the cell at p.
   */
  inline Cell cell (Pos p) const {
    if (p.i < 0 or p.i >= (int)grid_.size()
        or p.j < 0 or p.j >= (int)grid_[p.i].size()) {
      cerr << "warning: cell requested for position " << p << endl;
      return Cell();
    }
    return grid_[p.i][p.j];
  }

  /**
   * Returns a copy of the cell at (i, j).
   */
  inline Cell cell (int i, int j) const {
    return cell(Pos(i, j));
  }

  /**
   * Returns the total number of units in the game.
   */
  inline int nb_units () const {
    return unit_.size();
  }

  /**
   * Returns the information of the unit with identifier id.
   */
  inline Unit unit (int id) const {
    if (not unit_ok(id)) {
      cerr << "warning: unit requested for identifier " << id << endl;
      return Unit();
    }
    return unit_[id];
  }

  /**
   * Returns the current amount of land owned by a player.
   */
  inline int land (int pl) const {
    if (pl < 0 or pl >= (int)land_.size()) {
      cerr << "warning: score requested for player " << pl << endl;
      return -1;
    }
    return land_[pl];
  }

  /**
   * Returns the total score of a player.
   */
  inline int total_score (int pl) const {
    if (pl < 0 or pl >= (int)total_score_.size()) {
      cerr << "warning: total score requested for player " << pl << endl;
      return -1;
    }
    return total_score_[pl];
  }

  /**
   * Returns the percentage of cpu time used in the last round, in the
   * range [0.0 - 1.0] or a value lesser than 0 if this player is dead.
   * Note that this is only accessible if secgame() is true.
   */
  inline double status (int pl) const {
    if (pl < 0 or pl >= (int)cpu_status_.size()) {
      cerr << "warning: status requested for player " << pl << endl;
      return -2;
    }
    return cpu_status_[pl];
  }

  /**
   * Returns the ids of all the farmers of a player.
   */
  vector<int> farmers (int pl) {
    if (pl < 0 or pl >= (int)land_.size()) {
      cerr << "warning: farmers requested for player " << pl << endl;
      return vector<int>();
    }
    return farmers_[pl];
  }

  /**
   * Returns the ids of all the knights of a player.
   */
  vector<int> knights (int pl) {
    if (pl < 0 or pl >= (int)land_.size()) {
      cerr << "warning: knights requested for player " << pl << endl;
      return vector<int>();
    }
    return knights_[pl];
  }

  /**
   * Returns the ids of all the witches of a player.
   */
  vector<int> witches (int pl) {
    if (pl < 0 or pl >= (int)land_.size()) {
      cerr << "warning: witches requested for player " << pl << endl;
      return vector<int>();
    }
    return witches_[pl];
  }

  /**
   * Called to update the auxiliar redundant vectors.
   */
  void update_vectors_by_player () {
    farmers_ = knights_ = vector< vector<int> >(land_.size());
    for (const Unit& u : unit_) {
      UnitType tp = u.type;
      _my_assert(ut_ok(tp), "Wrong unit type on vectors update.");
      if (tp != Witch)
        (tp == Farmer ? farmers_ : knights_)[u.player].push_back(u.id);
    }
  }

  /**
   * Called to update the active witches and the haunted cells.
   */
  void update_haunted () {
    int r = grid_.size();
    int c = grid_[0].size();
    for (int x = 0; x < r; ++x)
      for (int y = 0; y < c; ++y) grid_[x][y].haunted = false;

    for (int pl = 0; pl < (int)land_.size(); ++pl)
      for (int id : witches_[pl]) {
        unit_[id].active = true;
        for (int x = -2; x <= 2; ++x)
          for (int y = -2; y <= 2; ++y)
            if ((x or y) and abs(x) + abs(y) <= 2) {
              Pos p = unit(id).pos + Pos(x, y);
              if (p.i >= 0 and p.i < r and p.j >= 0 and p.j < c) {
                int id2 = cell(p).id;
                if (id2 != -1 and unit(id2).type == Witch)
                  unit_[id].active = false;
              }
            }

        if (unit_[id].active)
          for (int x = -2; x <= 2; ++x)
            for (int y = -2; y <= 2; ++y)
              if (abs(x) + abs(y) <= 2) {
                Pos p = unit(id).pos + Pos(x, y);
                if (p.i >= 0 and p.i < r and p.j >= 0 and p.j < c)
                  grid_[p.i][p.j].haunted = true;
              }
      }
  }

  /**
   * Returns the state rotated for player pl.
   */
  State rotate (int pl) const {
    State res = *this;

    if (pl == 0) return res;

    rotate(res.grid_, res.unit_, pl);

    for (int i = 0; i < 4; ++i) {
      int j = (i + pl)%4;
      res.land_[i] = land_[j];
      res.total_score_[i] = total_score_[j];
      res.cpu_status_[i] = cpu_status_[j];
      res.farmers_[i] = farmers_[j];
      res.knights_[i] = knights_[j];
      res.witches_[i] = witches_[j];
    }

    return res;
  }

};


#endif
