#pragma once
#include <atomic>
#include <thread>
namespace ftxui {
    class ScreenInteractive;
}
// Presentation timing only; damage is handled by the battle model.
class FireballAnimation {
public:
    enum class Frame {
        Idle,
        Cast,
        Flight,
        Impact,
        Recover
    };
    // How many steps the fireball takes to cross from caster to target.
    static constexpr int kFlightSteps = 30;

    FireballAnimation() = default;
    ~FireballAnimation();
    FireballAnimation(const FireballAnimation&) = delete;
    FireballAnimation& operator=(const FireballAnimation&) = delete;
    void Start(ftxui::ScreenInteractive& screen);
    bool IsPlaying() const;
    Frame CurrentFrame() const;
    // 0 .. kFlightSteps - 1 while the frame is Flight.
    int Position() const;

private:
    void Stop();
    std::atomic<int> frame_{static_cast<int>(Frame::Idle)};
    std::atomic<int> position_{0};
    std::atomic<bool> playing_{false};
    std::jthread worker_;
};
