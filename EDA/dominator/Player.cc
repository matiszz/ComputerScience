#include "Player.hh"


void Player::reset (ifstream& is) {
  *(Action*)this = Action();

  read_grid(is);

  string s;
  is >> s >> round_;
  assert(s == "round");
  assert(round_ >= 0 and round_ < nb_rounds());

  is >> s;
  assert(s == "land");
  land_ = vector<int>(nb_players(), 0);
  for (auto& la : land_) {
    is >> la;
    assert(la >= 0);
  }

  is >> s;
  assert(s == "total_score");
  total_score_ = vector<int>(nb_players(), 0);
  for (auto& ts : total_score_) {
    is >> ts;
    assert(ts >= 0);
  }

  is >> s;
  assert(s == "status");
  cpu_status_ = vector<double>(nb_players(), 0);
  for (auto& st : cpu_status_) {
    is >> st;
    assert(st == -1 or (st >= 0 and st <= 1));
  }

  unit_ = vector<Unit>
          (nb_players()*(nb_farmers() + nb_knights() + nb_witches()));
  witches_ = vector< vector<int> >(nb_players());

  for (int id = 0; id < nb_units(); ++id) {
    char type;
    int player, i, j, health;
    _my_assert(is >> type >> player >> i >> j >> health,
               "Could not read info for unit " + to_string(id) + ".");

    assert(type == 'f' or type == 'k' or type == 'w');
    assert(player >= 0 and player < nb_players());
    assert(health > 0 or type == 'w');
    assert(i >= 0 and i < rows());
    assert(j >= 0 and j < cols());
    assert(grid_[i][j].type == Empty);
    if (type == 'f') assert(grid_[i][j].owner == player);
    assert(grid_[i][j].id == -1);

    grid_[i][j].id = id;
    unit_[id] = Unit(char2ut(type), id, player, health, Pos(i, j));
    if (type == 'f') assert(health <= farmers_health());
    else if (type == 'k') assert(health <= knights_health());
    else witches_[player].push_back(id);
  }

  update_vectors_by_player();
  update_haunted();

  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < cols(); ++j) {
      int id = cell(i, j).id;
      if (id != -1 and cell(i, j).haunted)
        _my_assert(unit(id).type == Witch, "Non-witch in haunted cell.");
    }

  *static_cast<State*>(this) = static_cast<State*>(this)->rotate(me_);
}
