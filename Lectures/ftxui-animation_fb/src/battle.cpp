#include "battle.h"
#include <algorithm>
AttackResult Battle::ExecuteAttack(Fighter& attacker, Fighter& defender, const Move& move) const {
    const int damage = std::clamp(move.damage, 0, defender.hit_points);
    defender.hit_points -= damage;
    return {
        .attacker_name = attacker.name,
        .defender_name = defender.name,
        .move_name = move.name,
        .damage_dealt = damage,
        .defender_defeated = defender.hit_points == 0,
        .animation = move.animation,
    };
}