#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpListener listener;
    sf::TcpSocket socket;
    sf::Packet packet;

    // Listen for incoming connections on port 53000
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cerr << "Error: Unable to bind to port 53000\n";
        return -1;
    }
    std::cout << "Server is listening on port 53000...\n";

    // Accept a client connection
    if (listener.accept(socket) != sf::Socket::Done) {
        std::cerr << "Error: Unable to accept connection\n";
        return -1;
    }
    std::cout << "Client connected!\n";

    // Main server loop
    while (true) {
        packet.clear();
        if (socket.receive(packet) == sf::Socket::Done) {
            int x, y;
            if (packet >> x >> y) {
                std::cout << "Received click at (" << x << ", " << y << ")\n";

                // Echo the position back to the client
                sf::Packet response;
                response << x << y;
                if (socket.send(response) != sf::Socket::Done) {
                    std::cerr << "Error: Unable to send response\n";
                }
            }
        }
    }

    return 0;
}