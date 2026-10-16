#include <algorithm>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "battle.h"
#include "sword_swing_animation.h"
using namespace ftxui;
namespace {
    std::string Repeat(const std::string& glyph, int count) {
        std::string result;
        for (int i = 0; i < count; ++i) {
            result += glyph;
        }
        return result;
    }
    Element HealthBar(const Fighter& fighter) {
        constexpr int width = 18;
        const int filled = fighter.max_hit_points == 0
                               ? 0
                               : width * fighter.hit_points / fighter.max_hit_points;
        return hbox({text("HP "), text(Repeat("█", filled)) | color(Color::Green), text(Repeat("░", width - filled)) | color(Color::DarkGreen), text(" " + std::to_string(fighter.hit_points) + "/" + std::to_string(fighter.max_hit_points))});
    }
    Element ThorinSprite(SwordSwingAnimation::Frame frame) {
        switch (frame) {
            case SwordSwingAnimation::Frame::Windup:
                return vbox({text("   O   /"), text("  /|__ /"), text(R"sprite(  / \)sprite")});
            case SwordSwingAnimation::Frame::Swing:
                return vbox({text("    O"), text("   /|====>"), text(R"sprite(   / \)sprite")});
            default:
                return vbox({text("   O"), text(R"sprite(  /|\)sprite"), text(R"sprite(  / \)sprite")});
        }
    }
    Element MalakaiSprite(SwordSwingAnimation::Frame frame) {
        if (frame == SwordSwingAnimation::Frame::Impact) {
            return vbox({text("  *O*"), text(R"sprite(  /|\   -24 HP)sprite") | color(Color::Red), text(R"sprite(  / \)sprite")});
        }
        return vbox({text("   O"), text(R"sprite(  /|\)sprite"), text(R"sprite(  / \)sprite")});
    }
} // namespace
int main() {
    Fighter thorin{"THORIN", "Level 5 Warrior", 85, 100};
    Fighter malakai{"MALAKAI", "Level 5 Spellblade", 90, 90};
    const Move longsword{"Longsword", 24, AnimationKind::SwordSwing};
    Battle battle;
    SwordSwingAnimation animation;
    std::string message = "Press Space to attack. Press q or Esc to quit.";
    auto screen = ScreenInteractive::TerminalOutput();
    auto view = Renderer([&] {
        const auto frame = animation.CurrentFrame();
        const auto left = vbox({text("PLAYER 1") | bold, text(thorin.name) | bold, text(thorin.title), separator(), HealthBar(thorin), filler(), ThorinSprite(frame)});
        const auto right = vbox({text("PLAYER 2") | bold, text(malakai.name) | bold, text(malakai.title), separator(), HealthBar(malakai), filler(), MalakaiSprite(frame)});
        return vbox({
                   text("⚔  BATTLE ARENA  ⚔") | bold | center,
                   separator(),
                   hbox({left | size(WIDTH, EQUAL, 34), filler(), right | size(WIDTH, EQUAL, 34)}),
                   separator(),
                   text("⚔  BATTLE  ⚔") | bold | center,
                   text(message) | center,
                   text("[Space] Attack    [q/Esc] Quit") | dim | center,
               }) |
               border |
               size(WIDTH, EQUAL, 200);
    });
    auto app = CatchEvent(view, [&](Event event) {
        if (event == Event::Character('q') || event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == Event::Character(' ') && !animation.IsPlaying()) {
            if (malakai.hit_points == 0) {
                message = "Malakai has already been defeated.";
            } else {
                const AttackResult result = battle.ExecuteAttack(thorin, malakai, longsword);
                message = result.attacker_name + " attacks " + result.defender_name +
                          " with a " + result.move_name + "!  " +
                          std::to_string(result.damage_dealt) + " damage!";
                animation.Start(screen);
            }
            return true;
        }
        return false;
    });
    screen.Loop(app);
}
