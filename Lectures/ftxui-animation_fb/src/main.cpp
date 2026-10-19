#include <algorithm>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "battle.h"
#include "fireball_animation.h"
#include "sword_swing_animation.h"
using namespace ftxui;
namespace {
    // Width of the open ground between the two fighters that the fireball crosses.
    constexpr int kLaneWidth = 50;
    // "~~🔥" takes 4 columns: the emoji is double-width in a terminal.
    constexpr int kFireballWidth = 4;

    std::string Repeat(const std::string& glyph, int count) {
        std::string result;
        for (int i = 0; i < count; ++i) {
            result += glyph;
        }
        return result;
    }
    // shown_hp lets the bar keep the old value until the hit actually lands.
    Element HealthBar(const Fighter& fighter, int shown_hp) {
        constexpr int width = 18;
        const int filled = fighter.max_hit_points == 0
                               ? 0
                               : width * shown_hp / fighter.max_hit_points;
        return hbox({text("HP "), text(Repeat("█", filled)) | color(Color::Green), text(Repeat("░", width - filled)) | color(Color::DarkGreen), text(" " + std::to_string(shown_hp) + "/" + std::to_string(fighter.max_hit_points))});
    }
    Element ThorinSprite(SwordSwingAnimation::Frame sword, FireballAnimation::Frame fireball) {
        switch (sword) {
            case SwordSwingAnimation::Frame::Windup:
                return vbox({text("   O   /"), text("  /|__ /"), text(R"sprite(  / \)sprite")});
            case SwordSwingAnimation::Frame::Swing:
                return vbox({text("    O"), text("   /|====>"), text(R"sprite(   / \)sprite")});
            default:
                break;
        }
        switch (fireball) {
            case FireballAnimation::Frame::Cast:
                return vbox({hbox({text(R"sprite(  \O/)sprite"), text(" *") | color(Color::Orange1) | bold}), text("   |"), text(R"sprite(  / \)sprite")});
            case FireballAnimation::Frame::Flight:
                return vbox({text("   O"), text("  /|--"), text(R"sprite(  / \)sprite")});
            default:
                return vbox({text("   O"), text(R"sprite(  /|\)sprite"), text(R"sprite(  / \)sprite")});
        }
    }
    Element MalakaiSprite(SwordSwingAnimation::Frame sword, FireballAnimation::Frame fireball, int damage) {
        const std::string hit = "   -" + std::to_string(damage) + " HP";
        if (sword == SwordSwingAnimation::Frame::Impact) {
            return vbox({text("  *O*"), text(R"sprite(  /|\)sprite" + hit) | color(Color::Red), text(R"sprite(  / \)sprite")});
        }
        if (fireball == FireballAnimation::Frame::Impact) {
            return vbox({text("  *O*") | color(Color::Orange1) | bold, text(R"sprite(  /|\)sprite" + hit) | color(Color::Red), text(R"sprite(  / \)sprite") | color(Color::Orange1)});
        }
        return vbox({text("   O"), text(R"sprite(  /|\)sprite"), text(R"sprite(  / \)sprite")});
    }
    // The open ground between the fighters: empty, a spark, the flying fireball, or the explosion.
    Element FireballLane(FireballAnimation::Frame frame, int position) {
        switch (frame) {
            case FireballAnimation::Frame::Cast:
                return vbox({text(""), text("✨"), text("")});
            case FireballAnimation::Frame::Flight: {
                const int column = position * (kLaneWidth - kFireballWidth) / (FireballAnimation::kFlightSteps - 1);
                const std::string pad = Repeat(" ", column);
                return vbox({
                    text(""),
                    hbox({text(pad + "~~") | color(Color::Orange1), text("🔥")}),
                    text(""),
                });
            }
            case FireballAnimation::Frame::Impact: {
                const std::string pad = Repeat(" ", kLaneWidth - kFireballWidth);
                return vbox({
                    text(""),
                    text(pad + "  💥"),
                    text(""),
                });
            }
            default:
                return vbox({text(""), text(""), text("")});
        }
    }
} // namespace
int main() {
    Fighter thorin{"THORIN", "Level 5 Warrior", 85, 100};
    Fighter malakai{"MALAKAI", "Level 5 Spellblade", 90, 90};
    const Move longsword{"Longsword", 24, AnimationKind::SwordSwing};
    const Move fireball_move{"Fireball", 30, AnimationKind::SpellProjectile};
    Battle battle;
    SwordSwingAnimation sword;
    FireballAnimation fireball;
    int last_damage = 0;
    std::string message = "Press Space to swing, f to cast a fireball. Press q or Esc to quit.";
    auto screen = ScreenInteractive::TerminalOutput();
    auto view = Renderer([&] {
        const auto sword_frame = sword.CurrentFrame();
        const auto fireball_frame = fireball.CurrentFrame();
        // The battle model already subtracted the damage; until the hit lands on screen,
        // show Malakai's health as it was before the attack.
        const bool hit_pending = sword_frame == SwordSwingAnimation::Frame::Windup ||
                                 sword_frame == SwordSwingAnimation::Frame::Swing ||
                                 fireball_frame == FireballAnimation::Frame::Cast ||
                                 fireball_frame == FireballAnimation::Frame::Flight;
        const int malakai_shown_hp = hit_pending ? malakai.hit_points + last_damage : malakai.hit_points;
        const auto left = vbox({text("PLAYER 1") | bold, text(thorin.name) | bold, text(thorin.title), separator(), HealthBar(thorin, thorin.hit_points)});
        const auto right = vbox({text("PLAYER 2") | bold, text(malakai.name) | bold, text(malakai.title), separator(), HealthBar(malakai, malakai_shown_hp)});
        const auto stage = hbox({
            ThorinSprite(sword_frame, fireball_frame) | size(WIDTH, EQUAL, 12),
            FireballLane(fireball_frame, fireball.Position()) | size(WIDTH, EQUAL, kLaneWidth),
            MalakaiSprite(sword_frame, fireball_frame, last_damage) | size(WIDTH, EQUAL, 16),
        });
        return vbox({
                   text("⚔  BATTLE ARENA  ⚔") | bold | center,
                   separator(),
                   hbox({left | size(WIDTH, EQUAL, 34), filler(), right | size(WIDTH, EQUAL, 34)}),
                   text(""),
                   stage | center,
                   separator(),
                   text("⚔  BATTLE  ⚔") | bold | center,
                   text(message) | center,
                   text("[Space] Sword    [f] Fireball    [q/Esc] Quit") | dim | center,
               }) |
               border |
               size(WIDTH, EQUAL, 200);
    });
    auto attack = [&](const Move& move) {
        if (malakai.hit_points == 0) {
            message = "Malakai has already been defeated.";
            return;
        }
        const AttackResult result = battle.ExecuteAttack(thorin, malakai, move);
        last_damage = result.damage_dealt;
        if (result.animation == AnimationKind::SpellProjectile) {
            message = result.attacker_name + " hurls a " + result.move_name + " at " +
                      result.defender_name + "!  " +
                      std::to_string(result.damage_dealt) + " damage!";
            fireball.Start(screen);
        } else {
            message = result.attacker_name + " attacks " + result.defender_name +
                      " with a " + result.move_name + "!  " +
                      std::to_string(result.damage_dealt) + " damage!";
            sword.Start(screen);
        }
        if (result.defender_defeated) {
            message += "  " + result.defender_name + " is defeated!";
        }
    };
    auto app = CatchEvent(view, [&](Event event) {
        if (event == Event::Character('q') || event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        // Ignore new attacks while either animation is still playing.
        const bool busy = sword.IsPlaying() || fireball.IsPlaying();
        if (event == Event::Character(' ') && !busy) {
            attack(longsword);
            return true;
        }
        if (event == Event::Character('f') && !busy) {
            attack(fireball_move);
            return true;
        }
        return false;
    });
    screen.Loop(app);
}
