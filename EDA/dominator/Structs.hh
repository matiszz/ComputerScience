#ifndef Structs_hh
#define Structs_hh


#include "Utils.hh"


/** \file
 * Contains the Dir enumeration, the Pos struct,
 * the CellType enumeration, the Cell struct,
 * the UnitType enumeration, the Unit struct,
 * and some useful little functions.
 */


/**
 * Enum to encode directions.
 */
enum Dir {
  Bottom, BR, Right, RT, Top, TL, Left, LB,
  None,
  DirSize
};


/**
 * Returns whether dir is a valid direction.
 */
inline bool dir_ok (Dir dir) {
  return dir >= Bottom and dir <= None;
}


/**
 * Simple struct to handle positions.
 */
struct Pos {

  int i, j;

  /**
   * Default constructor (0, 0).
   */
  inline Pos () : i(0), j(0) { }

  /**
   * Given constructor.
   */
  inline Pos (int i, int j) : i(i), j(j) { }

  /**
   * Print operator.
   */
  inline friend ostream& operator<< (ostream& os, const Pos& p) {
    return os << "(" << p.i << ", " << p.j << ")";
  }

  /**
   * Comparison operator.
   */
  inline friend bool operator== (const Pos& a, const Pos& b) {
    return a.i == b.i and a.j == b.j;
  }

  /**
   * Comparison operator.
   */
  inline friend bool operator!= (const Pos& a, const Pos& b) {
    return not (a == b);
  }

  /**
   * Comparison operator, mostly needed for sorting.
   */
  inline friend bool operator< (const Pos& a, const Pos& b) {
    if (a.i != b.i) return a.i < b.i;
    return a.j < b.j;
  }

  /**
   * Increment operator: moves a position according to a direction.
   */
  inline Pos& operator+= (Dir d) {
    switch (d) {
      case Bottom: ++i;  break;
      case BR: ++i; ++j; break;
      case Right:  ++j;  break;
      case RT: --i; ++j; break;
      case Top:    --i;  break;
      case TL: --i; --j; break;
      case Left:   --j;  break;
      case LB: ++i; --j; break;
      case None:         break;
      default: ; // do nothing
    }
    return *this;
  }

  /**
   * Addition operator: Returns a position by adding a direction.
   */
  inline Pos operator+ (Dir d) const {
    Pos p = *this;
    p += d;
    return p;
  }

  /**
   * Increment operator: moves a position according to another position.
   */
  inline Pos& operator+= (Pos p) {
    this->i += p.i;
    this->j += p.j;
    return *this;
  }

  /**
   * Addition operator: Returns a position by adding another position.
   */
  inline Pos operator+ (Pos p) const {
    Pos p2 = *this;
    p2 += p;
    return p2;
  }

};


/**
 * Defines if a cell is empty or it has any special feature on it.
 */
enum CellType {
  Empty, Wall,
  CellTypeSize
};


/**
 * Describes a cell in the board, and its contents.
 */
struct Cell {

  CellType type; // The kind of cell.
  int owner;     // The player that last conquered this cell, or -1.
  int id;        // The id of a unit if present, or -1 otherwise.
  bool haunted;  // If the cell is threatened by a witch.

  /**
   * Default constructor (Empty, -1, -1).
   */
  inline Cell () : type(Empty), owner(-1), id(-1), haunted(false) { }

  /**
   * Given constructor.
   */
  inline Cell (CellType t, int pl, int id, bool h)
               : type(t), owner(pl), id(id), haunted(h) { }

};


/**
 * Defines the type of the unit.
 */
enum UnitType {
  Farmer, Knight, Witch,
  UnitTypeSize
};


/**
 * Returns whether u is a valid UnitType.
 */
inline bool ut_ok (UnitType u) {
  return u == Farmer or u == Knight or u == Witch;
}


/**
 * Returns the char corresponding to a unit type.
 */
inline char ut2char (UnitType u) {
  if (u == Farmer) return 'f';
  if (u == Knight) return 'k';
  if (u == Witch) return 'w';
  _unreachable();
}


/**
 * Returns the unit type corresponding to a char.
 */
inline UnitType char2ut (char c) {
  if (c == 'f') return Farmer;
  if (c == 'k') return Knight;
  if (c == 'w') return Witch;
  _unreachable();
}


/**
 * Describes a unit on the board and its properties.
 */
struct Unit {

  UnitType type; // The kind of unit.
  int id;        // The unique id for this unit during the game.
  int player;    // The player that owns this unit.
  int health;    // The current health of the unit. It dies if it reaches 0.
  Pos pos;       // The position inside the board.
  bool active;   // For witches.

  /**
   * Default constructor (Farmer, -1, -1, 0, (0, 0)).
   */
  inline Unit () : type(Farmer), id(-1), player(-1), health(0), pos(0, 0),
                   active(false) { }

  /**
   * Given constructor.
   */
  inline Unit (UnitType t, int id, int pl, int h, Pos p = Pos(0, 0),
               bool a = false)
               : type(t), id(id), player(pl), health(h), pos(p), active(a) { }

};


#endif
