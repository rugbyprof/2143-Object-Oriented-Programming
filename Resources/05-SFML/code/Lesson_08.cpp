#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

class Slider : public sf::Drawable {
   private:
    sf::RectangleShape track;  // The bar
    sf::CircleShape knob;      // The draggable circle
    float radius;
    float minValue;
    float maxValue;
    float value;
    bool isDragging;
    bool horizontal;

    // Overriding the draw method from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Draw the rectangle first
        target.draw(track, states);
        target.draw(knob, states);
    }

   public:
    Slider() {}
    Slider(float x, float y, float width, float height, float min, float max, float radius)
        : minValue(min), maxValue(max), value(min), isDragging(false) {
        // Configure the track
        track.setSize(sf::Vector2f(width, height));
        track.setFillColor(sf::Color::White);
        track.setOutlineColor(sf::Color::Black);
        track.setPosition(x, y);

        // Configure the knob
        knob.setRadius(radius);
        knob.setFillColor(sf::Color::Red);
        knob.setOrigin(knob.getRadius(), knob.getRadius());

        if (width > height) {
            horizontal = true;
        } else {
            horizontal = false;
        }

        cout << "Horizontal: " << horizontal << endl;

        if (horizontal) {
            knob.setPosition(x, y + track.getSize().y / 2);
        } else {
            knob.setPosition(x + track.getSize().x / 2, y);
        }

        // Set initial value
        setValue(50.0);
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (knob.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            isDragging = false;
        } else if (event.type == sf::Event::MouseMoved && isDragging) {
            if (horizontal) {
                float mouseX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;

                // Constrain knob to track bounds
                float left  = track.getPosition().x;
                float right = left + track.getSize().x;
                if (mouseX < left)
                    mouseX = left;
                if (mouseX > right)
                    mouseX = right;

                // Move knob and calculate value
                knob.setPosition(mouseX, knob.getPosition().y);
                value = minValue + ((mouseX - left) / track.getSize().x) * (maxValue - minValue);
            } else {
                float mouseY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;

                // Constrain knob to track bounds
                float top    = track.getPosition().y;
                float bottom = top + track.getSize().y;
                if (mouseY < top)
                    mouseY = top;
                if (mouseY > bottom)
                    mouseY = bottom;

                // Move knob and calculate value
                knob.setPosition(knob.getPosition().x, mouseY);
                value = minValue + ((mouseY - top) / track.getSize().y) * (maxValue - minValue);
            }
        }
    }

    // void draw(sf::RenderTarget& target) const {
    //     target.draw(track);
    //     target.draw(knob);
    // }

    float getValue() const { return value; }

    void setValue(float newValue) {
        if (newValue < minValue)
            newValue = minValue;
        if (newValue > maxValue)
            newValue = maxValue;

        value = newValue;

        if (horizontal) {
            // Update knob position based on value
            float left      = track.getPosition().x;
            float right     = left + track.getSize().x;
            float positionX = left + ((value - minValue) / (maxValue - minValue)) * (right - left);
            knob.setPosition(positionX, knob.getPosition().y);
        } else {
            // Update knob position based on value
            float top       = track.getPosition().y;
            float bottom    = top + track.getSize().y;
            float positionY = top + ((value - minValue) / (maxValue - minValue)) * (bottom - top);
            knob.setPosition(knob.getPosition().x, positionY);
        }
    }
};

class MusicPlayer : public sf::Drawable {
   private:
    Slider slider;
    sf::Music music;
    sf::RectangleShape border;
    sf::Texture playTexture;
    sf::Texture pauseTexture;
    sf::Texture stopTexture;
    sf::Texture nextTexture;
    // sf::Texture prevTexture;
    sf::Sprite playSprite;
    sf::Sprite pauseSprite;
    sf::Sprite stopSprite;
    sf::Sprite nextSprite;
    // sf::Sprite prevSprite(prevTexture);

    // Overriding the draw method from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Draw the rectangle first
        target.draw(border, states);
        target.draw(playSprite, states);
        target.draw(pauseSprite, states);
        target.draw(stopSprite, states);
        target.draw(nextSprite, states);
        // target.draw(prevSprite, states);

        target.draw(slider, states);
    }

   public:
    MusicPlayer() {
        slider = Slider(200.f, 300.f, 400.f, 3.0f, 0.f, 100.f, 10.f);

        if (!music.openFromFile("./media/music/blade-soundtrack-1-blood-rave.mp3")) {
            std::cerr << "Error loading music file!" << std::endl;
        }
        music.setLoop(true);  // Loops the sound indefinitely
        music.setVolume(20.f);
        // music.play();

        border.setSize(sf::Vector2f(400.f + 5.f, 3.f + 45.f));
        border.setFillColor(sf::Color::Black);
        border.setPosition(200.f - 5.f, 300.f - 5.f);
        border.setOutlineColor(sf::Color::White);

        if (!playTexture.loadFromFile("./media/images/play.png")) {
            std::cerr << "Error loading play button image!" << std::endl;
        }
        if (!pauseTexture.loadFromFile("./media/images/pause.png")) {
            std::cerr << "Error loading pause button image!" << std::endl;
        }
        if (!stopTexture.loadFromFile("./media/images/stop.png")) {
            std::cerr << "Error loading stop button image!" << std::endl;
        }
        if (!nextTexture.loadFromFile("./media/images/next.png")) {
            std::cerr << "Error loading next button image!" << std::endl;
        }
        // if (!prevTexture.loadFromFile("./media/images/prev.png")) {
        //     std::cerr << "Error loading prev button image!" << std::endl;
        // }

        playSprite.setTexture(playTexture);
        pauseSprite.setTexture(pauseTexture);
        stopSprite.setTexture(stopTexture);
        nextSprite.setTexture(nextTexture);
        // prevSprite.setTexture(prevTexture);

        playSprite.setPosition(200.f, 300.f);
        pauseSprite.setPosition(250.f, 300.f);
        stopSprite.setPosition(300.f, 300.f);
        nextSprite.setPosition(350.f, 300.f);
        // prevSprite.setPosition(400.f, 300.f);

        playSprite.setScale(0.4f, 0.4f);
        pauseSprite.setScale(0.4f, 0.4f);
        stopSprite.setScale(0.4f, 0.4f);
        nextSprite.setScale(0.4f, 0.4f);
        // prevSprite.setScale(0.1f, 0.1f);
    }
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        slider.handleEvent(event, window);
        int volume = slider.getValue();
        music.setVolume(volume);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (playSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                if (music.getStatus() == sf::Music::Playing) {
                    music.pause();
                } else {
                    music.play();
                }
            } else if (pauseSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                music.pause();
            } else if (stopSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                music.stop();
            } else if (nextSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                music.stop();
                music.play();
            }
        }
    }
};

int main() {
    // Load the sound buffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./media/sounds/dice_roll_01.mp3")) {
        std::cerr << "Error loading sound file!" << std::endl;
        return -1;
    }

    // sf::Music music;
    // if (!music.openFromFile("./media/music/blade-soundtrack-1-blood-rave.mp3")) {
    //     std::cerr << "Error loading music file!" << std::endl;
    //     return -1;
    // }
    // music.setLoop(true);  // Loops the sound indefinitely
    // music.setVolume(50.f);
    // music.play();

    // Create a sound and play it
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    // Wait while the sound is playing
    while (sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(100));
    }
    // Create a simple game loop
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game with Background Music");

    MusicPlayer musicPlayer;

    // Slider slider(200.f, 300.f, 400.f, 3.0f, 0.f, 100.f);
    Slider slider(50.f, 50.f, 1.f, 200.0f, 0.f, 100.f, 15.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            slider.handleEvent(event, window);
            musicPlayer.handleEvent(event, window);
        }

        // Game logic and rendering here
        window.clear();
        window.draw(slider);
        window.draw(musicPlayer);
        window.display();
    }

    return 0;
}