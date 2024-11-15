#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpSocket socket;
    sf::Packet packet;

    // Connect to the server
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done) {
        std::cerr << "Error: Unable to connect to server\n";
        return -1;
    }
    std::cout << "Connected to the server!\n";

    // Create a window for displaying clicks
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Screen");
    sf::CircleShape clickMarker(5);
    clickMarker.setFillColor(sf::Color::Red);

    std::vector<sf::Vector2f> clickPositions;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Detect mouse click and send to server
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                // Send the click position to the server
                packet.clear();
                packet << x << y;
                if (socket.send(packet) != sf::Socket::Done) {
                    std::cerr << "Error: Unable to send packet\n";
                }
            }
        }

        // Receive positions from the server
        packet.clear();
        if (socket.receive(packet) == sf::Socket::Done) {
            int x, y;
            if (packet >> x >> y) {
                clickPositions.push_back(sf::Vector2f(x, y));
                std::cout << "Received click at (" << x << ", " << y << ")\n";
            }
        }

        // Draw received clicks
        window.clear();
        for (const auto& pos : clickPositions) {
            clickMarker.setPosition(pos);
            window.draw(clickMarker);
        }
        window.display();
    }

    return 0;
}