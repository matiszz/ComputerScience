#ifndef Info_hh
#define Info_hh


#include "Settings.hh"
#include "State.hh"


/*! \file
 * Contains a class to store most of the information of the game.
 */


/**
 * Stores all the information of the game,
 * except the names of the vectors and the random generator of the board.
 */
class Info : public Settings, public State {

  friend class Game;
  friend class SecGame;

public:

  /**
   * Returns the cell defined by the char c.
   */
  inline static Cell char2cell (char c) {
    Cell cell;
    switch (c) {
      case '0' ... '4':
        cell.owner = c - '0';
        break;
      case '.':
        break; // empty cell
      case 'X':
        cell.type = Wall;
        break;
      default:
        _my_assert(false, string(1, c) + " in grid definition.");
    }
    return cell;
  }

  /**
   * Reads the grid of the board.
   */
  void read_grid (istream& is) {
    grid_ = vector< vector<Cell> >(rows(), vector<Cell>(cols()));
    for (int i = 0; i < rows(); ++i) {
      string s;
      is >> s;
      _my_assert((int)s.size() == cols(),
                 "The read map has a line with incorrect lenght.");
      for (int j = 0; j < cols(); ++j) grid_[i][j] = char2cell(s[j]);
    }
  }

};


#endif
