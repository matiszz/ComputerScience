#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Demo


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VE;

  map<int, int> kind; // For farmers: 0 -> random, 1 -> cyclical

  /**
   * Play method, invoked once per each round.
   */
  void play () {
    // Here, we have two kinds of farmers:
    // one moves at random, the other cyclically.
    VE f = farmers(0);
    for (int id : f) {
      if (kind.find(id) == kind.end()) kind[id] = random(0, 1);
      if (kind[id] == 0) command(id, Dir(2*random(0, 3)));
      else command(id, Dir(2*(round()%4)));
    }

    // At even rounds, knights move randomly, unless there is an adjacent,
    // non-witch hostile unit. At odd rounds, $1/4$ of them (rounded
    // appropriately) move in each of the diagonal directions.
    VE k = knights(0);
    if (round()%2 == 0) {
      for (int id : k) {
        VE D;
        Pos pos = unit(id).pos;
        for (int d = 0; d < 8; ++d) {
          int id2 = cell(pos + Dir(d)).id;
          if (id2 != -1) {
            Unit u = unit(id2);
            if (u.player != 0 and u.type != Witch) D.push_back(d);
          }
        }
        if (D.empty()) command(id, Dir(random(0, 7)));
        else command(id, Dir(D[random(0, D.size() - 1)]));
      }
    }
    else {
      int num = k.size();
      vector<Dir> v(num);
      for (int i = 0; i < num; ++i) v[i] = Dir(2*(i%4) + 1);
      vector<int> perm = random_permutation(num);
      for (int i = 0; i < num; ++i) command(k[i], v[perm[i]]);
    }

    // This code does several things, most of them stupid.
    // It's just to show that there are many possibilities.
    VE w = witches(0);
    if (round() < 40) command(w[0], Top);
    else if (round() < 80) command(w[0], Left);
    else if (round() < 120) command(w[0], None);
    else if (round() < 160) command(w[0], Bottom);
    else {
      set<Pos> s;
      while ((int)s.size() < 4) s.insert(Pos(random(0, 36), random(0, 36)));
      vector<Pos> v(s.begin(), s.end());
      if (v[random(0, 3)].i < 18) command(w[0], None);
      else command(w[0], Top);
    }

    int id = w[1];
    if (status(0) > 0.8) command(id, Left);
    else if (total_score(1) > 10000) command(id, Bottom);
    else if (land(3) > 100) command(id, Right);
    else if (cell(35, 35).type == Wall) command(id, None);
    else if (unit(id).health < 40) command(id, Top);
    else if (cell(10, 20).owner == 2) command(id, None);
    else if (not cell(20, 10).haunted) command(id, None);
    else if (pos_ok(unit(id).pos + Pos(20, 30))) command(id, Left);
    else if (pos_ok(unit(id).pos.i + random(-5, 5), 10)) command(id, Bottom);
    else if (not unit(id).active) command(id, Right);
    else cerr << unit(id).pos << endl; // You can print to cerr to debug.
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
