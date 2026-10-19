#pragma once

#include <string>

// Game rules only; no dependency on FTXUI.
enum class AnimationKind {
  SwordSwing,
  SpellProjectile,
  StealthStrike
};

struct Fighter {
  std::string name;
  std::string title;
  int hit_points;
  int max_hit_points;
};

struct Move {
  std::string name;
  int damage;
  AnimationKind animation;
};

struct AttackResult {
  std::string attacker_name;
  std::string defender_name;
  std::string move_name;
  int damage_dealt;
  bool defender_defeated;
  AnimationKind animation;
};

class Battle {
 public:
  AttackResult ExecuteAttack(Fighter& attacker, Fighter& defender,
                             const Move& move) const;
};