#include "sword_swing_animation.h"

#include <array>
#include <chrono>
#include <thread>

#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace {
using namespace std::chrono_literals;

bool WaitFor(std::stop_token stop, std::chrono::milliseconds duration) {
  constexpr auto tick = 10ms;
  while (duration > 0ms) {
    if (stop.stop_requested()) {
      return false;
    }
    const auto interval = std::min(duration, tick);
    std::this_thread::sleep_for(interval);
    duration -= interval;
  }
  return !stop.stop_requested();
}
}  // namespace

SwordSwingAnimation::~SwordSwingAnimation() { Stop(); }

void SwordSwingAnimation::Start(ftxui::ScreenInteractive& screen) {
  if (playing_.exchange(true)) {
    return;
  }

  Stop();
  playing_ = true;
  frame_ = static_cast<int>(Frame::Windup);

  worker_ = std::jthread([this, &screen](std::stop_token stop) {
    constexpr std::array timeline{
        std::pair{Frame::Windup, 180ms}, std::pair{Frame::Swing, 160ms},
        std::pair{Frame::Impact, 220ms}, std::pair{Frame::Recover, 160ms},
        std::pair{Frame::Idle, 0ms},
    };

    for (const auto& [next_frame, duration] : timeline) {
      frame_ = static_cast<int>(next_frame);
      screen.Post(ftxui::Event::Custom);
      if (!WaitFor(stop, duration)) {
        return;
      }
    }
    playing_ = false;
    screen.Post(ftxui::Event::Custom);
  });
}

bool SwordSwingAnimation::IsPlaying() const { return playing_; }

SwordSwingAnimation::Frame SwordSwingAnimation::CurrentFrame() const {
  return static_cast<Frame>(frame_.load());
}

void SwordSwingAnimation::Stop() {
  if (worker_.joinable()) {
    worker_.request_stop();
    worker_.join();
  }
  playing_ = false;
  frame_ = static_cast<int>(Frame::Idle);
}
