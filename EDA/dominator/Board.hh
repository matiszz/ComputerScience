#ifndef Board_hh
#define Board_hh


#include "Info.hh"
#include "Action.hh"
#include "Random.hh"


/*! \file
 * Contains the Board class, with all the game information,
 * plus the names of the players and a random generator.
 */


/**
 * Manages a random generator and the information of the board.
 */
class Board : public Info, public Random_generator {

  friend class Game;
  friend class SecGame;

  vector<string> names_;
  string generator_;

  /**
   * Reads the generator method, and generates or reads the grid.
   */
  void read_generator_and_grid (istream& is) {
    is >> generator_;
    if (generator_ == "FIXED") read_grid(is);
    else {
      vector<int> param;
      int x;
      while (is >> x) param.push_back(x);
      if (generator_ == "GENERATOR1") generator1(param);
      else if (generator_ == "GENERATOR2") generator2(param);
      else if (generator_ == "GENERATOR3") generator3(param);
      else _my_assert(false, "Unknow grid generator.");
    }
  }

  /**
   * Fills the board with empty cells and surrounding walls.
   */
  void initial (int r, int c);

  /**
   * Computes the current lands and updates the total scores of all players.
   */
  void compute_scores ();

  /**
   * Generates a board with param[0] walls,
   * or with random(param[0], param[1]) walls.
   */
  void generator1 (vector<int> param);

  /**
   * Generates a board with random connected walls.
   */
  void generator2 (vector<int> param);

  /**
   * Used by generator2.
   */
  static Dir left (Dir d);
  static Dir right (Dir d);
  bool empty_line (Pos pos, Dir dir) const;
  bool ok_cell3 (Pos pos, Dir dir) const;
  bool ok_cell2 (Pos pos) const;
  vector<Pos> candidate_cells () const;
  bool connected () const;

  /**
   * Generates a connected, grid-like board.
   */
  void generator3 (vector<int> param);

  /**
   * Used by generator3.
   */
  typedef pair<Pos, bool> P;
  static int repre (int x, vector<int>& pare);
  void unpaint_wall (int i, int j, bool vert);
  bool ok3_vert (int i, int j) const;
  bool ok3_hori (int i, int j) const;

  /**
   * Prints some information of the unit.
   */
  inline static void print_unit (Unit u, ostream& os) {
    os << ut2char(u.type) << ' '
       << u.player << ' '
       << u.pos.i << ' '
       << u.pos.j << ' '
       << u.health << endl;
  }

  void capture (int id, int pl, vector<bool>& killed);

  void step (int id, Pos p2);

  /**
   * Kills the unit id by a spell.
   */
  void spell (int id, vector<bool>& killed);

  /**
   * Tries to apply a move. Returns true if it could. Marks killed units.
   */
  bool move (int id, Dir dir, vector<bool>& killed);

  /**
   * Computes the box to spawn units corresponding to pl.
   */
  void box (int pl, int& mini, int& maxi, int& minj, int& maxj) const;

  /**
   * Used by spawn_units.
   */
  bool available (int i, int j) const;
  int witch_team (Pos pos) const;
  bool pos_witch_ok (int i, int j) const;
  bool ok_cell (int pl, Pos pos, bool knight) const;
  void place (int id, Pos p);
  void spawn (const vector<Pos>& pos, const vector<int>& uni, int ini);

  /**
   * Places all units that could not be placed in any normal position.
   */
  void spawn_extras (const vector<int>& uni);

  /**
   * Places all knights or farmers of pl in its starting or reborn positions.
   * Adds to extra the units that could not be placed.
   */
  void spawn_units (int pl, const vector<int>& uni, vector<int>& extra);

  /**
   * Places all witches of pl in its starting positions.
   * Initializes the witches_[pl] vector, which will never change.
   */
  void spawn_witches (int pl, int& id);

  /**
   * Generate all the units of the board.
   */
  void generate_units ();

public:

  /**
   * Construct a board by reading information from a stream.
   */
  Board (istream& is, int seed);

  /**
   * Returns the name of a player.
   */
  inline string name (int player) const {
    assert(player_ok(player));
    return names_[player];
  }

  /**
   * Prints the board preamble to a stream.
   */
  void print_preamble (ostream& os) const;

  /**
   * Prints the name players to a stream.
   */
  void print_names (ostream& os) const;

  /**
   * Prints the state of the board to a stream.
   */
  void print_state (ostream& os) const;

  /**
   * Prints the results and the names of the winning players.
   */
  void print_results () const;

  /**
   * Computes the next board aplying the given actions to the current board.
   * It also prints to os the actual actions performed.
   */
  void next (const vector<Action>& act, ostream& os);

};


#endif
