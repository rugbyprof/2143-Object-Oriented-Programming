#pragma once
#include <atomic>
#include <thread>
namespace ftxui {
    class ScreenInteractive;
}
// Presentation timing only; damage is handled by the battle model.
class SwordSwingAnimation {
public:
    enum class Frame {
        Idle,
        Windup,
        Swing,
        Impact,
        Recover
    };
    SwordSwingAnimation() = default;
    ~SwordSwingAnimation();
    SwordSwingAnimation(const SwordSwingAnimation&) = delete;
    SwordSwingAnimation& operator=(const SwordSwingAnimation&) = delete;
    void Start(ftxui::ScreenInteractive& screen);
    bool IsPlaying() const;
    Frame CurrentFrame() const;

private:
    void Stop();
    std::atomic<int> frame_{static_cast<int>(Frame::Idle)};
    std::atomic<bool> playing_{false};
    std::jthread worker_;
};