#include "Settings.hh"


Settings Settings::read_settings (istream& is) {
  Settings r;
  string s, v;

  // Version, compared part by part.
  istringstream vs(version());
  while (!vs.eof()) {
    is >> s;
    vs >> v;
    assert(s == v);
  };

  is >> s >> r.nb_players_;
  assert(s == "nb_players");
  assert(r.nb_players_ == 4);

  is >> s >> r.nb_rounds_;
  assert(s == "nb_rounds");
  assert(r.nb_rounds_ >= 1);

  is >> s >> r.nb_farmers_;
  assert(s == "nb_farmers");
  assert(r.nb_farmers_ >= 0);

  is >> s >> r.nb_knights_;
  assert(s == "nb_knights");
  assert(r.nb_knights_ >= 0);

  is >> s >> r.nb_witches_;
  assert(s == "nb_witches");
  assert(r.nb_witches_ >= 0);

  is >> s >> r.farmers_health_;
  assert(s == "farmers_health");
  assert(r.farmers_health_ >= 1);

  is >> s >> r.knights_health_;
  assert(s == "knights_health");
  assert(r.knights_health_ >= 1);

  is >> s >> r.farmers_regen_;
  assert(s == "farmers_regen");
  assert(r.farmers_regen_ >= 0);

  is >> s >> r.knights_regen_;
  assert(s == "knights_regen");
  assert(r.knights_regen_ >= 0);

  is >> s >> r.damage_min_;
  assert(s == "damage_min");
  assert(r.damage_min_ >= 0);

  is >> s >> r.damage_max_;
  assert(s == "damage_max");
  assert(r.damage_max_ >= r.damage_min_);

  is >> s >> r.rows_;
  assert(s == "rows");
  assert(r.rows_ >= 20 and r.rows_%2 == 1);

  is >> s >> r.cols_;
  assert(s == "cols");
  assert(r.cols_ >= 20 and r.cols_%2 == 1);

  assert(r.rows_ == r.cols_);

  return r;
}
