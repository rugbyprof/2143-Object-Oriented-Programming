#include "fireball_animation.h"

#include <algorithm>
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
} // namespace

FireballAnimation::~FireballAnimation() {
    Stop();
}

void FireballAnimation::Start(ftxui::ScreenInteractive& screen) {
    if (playing_.exchange(true)) {
        return;
    }

    Stop();
    playing_ = true;
    position_ = 0;
    frame_ = static_cast<int>(Frame::Cast);

    worker_ = std::jthread([this, &screen](std::stop_token stop) {
        // Show one frame, ask FTXUI to redraw, then hold it for `duration`.
        auto show = [&](Frame next_frame, std::chrono::milliseconds duration) {
            frame_ = static_cast<int>(next_frame);
            screen.Post(ftxui::Event::Custom);
            return WaitFor(stop, duration);
        };

        if (!show(Frame::Cast, 300ms)) {
            return;
        }

        // The fireball moves one step per redraw until it reaches the target.
        for (int step = 0; step < kFlightSteps; ++step) {
            position_ = step;
            if (!show(Frame::Flight, 35ms)) {
                return;
            }
        }

        if (!show(Frame::Impact, 400ms)) {
            return;
        }
        if (!show(Frame::Recover, 200ms)) {
            return;
        }
        frame_ = static_cast<int>(Frame::Idle);
        playing_ = false;
        screen.Post(ftxui::Event::Custom);
    });
}

bool FireballAnimation::IsPlaying() const {
    return playing_;
}

FireballAnimation::Frame FireballAnimation::CurrentFrame() const {
    return static_cast<Frame>(frame_.load());
}

int FireballAnimation::Position() const {
    return position_;
}

void FireballAnimation::Stop() {
    if (worker_.joinable()) {
        worker_.request_stop();
        worker_.join();
    }
    playing_ = false;
    position_ = 0;
    frame_ = static_cast<int>(Frame::Idle);
}
