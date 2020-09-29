#ifndef Settings_hh
#define Settings_hh


#include "Structs.hh"


/** \file
 * Contains a class to store all the game settings that do not change
 * during a game, except the names of the players.
 */


/**
 * Stores most of the game settings.
 */
class Settings {

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  int nb_players_;
  int nb_rounds_;
  int nb_farmers_;
  int nb_knights_;
  int nb_witches_;
  int farmers_health_;
  int knights_health_;
  int farmers_regen_;
  int knights_regen_;
  int damage_min_;
  int damage_max_;
  int rows_;
  int cols_;

  /**
   * Reads the settings from a stream.
   */
  static Settings read_settings (istream& is);

public:

  /**
   * Returns a string with the game name and version.
   */
  inline static string version () {
    return "Dominator 4.0";
  }

  /**
   * Returns the number of players in the game.
   */
  inline int nb_players () const {
    return nb_players_;
  }

  /**
   * Returns the number of rounds for the game.
   */
  inline int nb_rounds () const {
    return nb_rounds_;
  }

  /**
   * Returns the initial number of farmers for every player.
   */
  inline int nb_farmers () const {
    return nb_farmers_;
  }

  /**
   * Returns the initial number of knights for every player.
   */
  inline int nb_knights () const {
    return nb_knights_;
  }

  /**
   * Returns the constant number of witches for every player.
   */
  inline int nb_witches () const {
    return nb_witches_;
  }

  /**
   * Returns the initial (and maximum) health of the farmers.
   */
  inline int farmers_health () const {
    return farmers_health_;
  }

  /**
   * Returns the initial (and maximum) health of the knights.
   */
  inline int knights_health () const {
    return knights_health_;
  }

  /**
   * Returns the health a farmer recovers per round when not moving.
   */
  inline int farmers_regen () const {
    return farmers_regen_;
  }

  /**
   * Returns the health a knight recovers per round when not moving.
   */
  inline int knights_regen () const {
    return knights_regen_;
  }

  /**
   * Returns the minimum damage inflicted by a knight attack.
   */
  inline int damage_min () const {
    return damage_min_;
  }

  /**
   * Returns the maximum damage inflicted by a knight attack.
   */
  inline int damage_max () const {
    return damage_max_;
  }

  /**
   * Returns the number of rows of the maze of the game.
   */
  inline int rows () const {
    return rows_;
  }

  /**
   * Returns the number of columns of the maze of the game.
   */
  inline int cols () const {
    return cols_;
  }

  /**
   * Returns whether pl is a valid player identifier.
   */
  inline bool player_ok (int pl) const {
    return pl >= 0 and pl < nb_players();
  }

  /**
   * Returns whether (i, j) is a position inside the board.
   */
  inline bool pos_ok (int i, int j) const {
    return i >= 0 and i < rows() and j >= 0 and j < cols();
  }

  /**
   * Returns whether p is a position inside the board.
   */
  inline bool pos_ok (Pos p) const {
    return pos_ok(p.i, p.j);
  }

};


#endif
