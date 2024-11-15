Conceptually, two students connected to the same wireless network on campus should be able to play each other. Here’s why and what might need to be considered:

### How It Works

	1.	Same Network:
	  - If both students are on the same campus wireless network (e.g., Wi-Fi SSID: CampusNet), their devices are typically assigned IP addresses within the same local network (e.g., 192.168.x.x or 10.x.x.x).
	  - They should be able to communicate directly using these local IP addresses.
	2.	Direct Connection:
	  - The server player would need to share their local IP (e.g., 192.168.1.12) and the port (e.g., 53000) with the client player.
	  - The client can then connect to the server by specifying this IP and port.

Potential Challenges in a Secure Environment

Even on the same network, there may be obstacles due to campus security protocols:
	1.	Firewall Restrictions:
	  - Many campus networks implement strict firewall rules to block direct peer-to-peer (P2P) communication between devices.
	  - The server’s port (e.g., 53000) may be blocked unless explicitly allowed by the network administrators.
	2.	Client Isolation:
	  - Some networks use “client isolation” or “AP isolation” to prevent devices connected to the same Wi-Fi network from communicating with each other directly. This is a common security feature.
	3.	Dynamic IP Assignment:
	  - Campus networks often use dynamic IP addresses (via DHCP). If a player disconnects and reconnects, their IP address may change, requiring reconfiguration.

Workarounds

	1.	Check for Direct Connectivity:
	  - Both students can test connectivity using a simple tool like ping:

ping <server_local_ip>

If the client can ping the server’s local IP, direct communication is possible.

	2.	Using a Public Server (Relay):
	  - If direct connectivity isn’t possible, you can use a publicly accessible server as a relay:
	  - The server program runs on a publicly accessible machine (e.g., cloud hosting or a DigitalOcean VPS).
	  - Both students connect to this server, which handles communication between them.
	3.	Campus IT Support:
	  - If this is for educational purposes, you might ask campus IT for help in enabling direct communication between the two devices for the specific game.

Testing

	  - Local Test: Test using the same Wi-Fi network and ensure port availability.
	  - Debugging Tools:
	  - Use netcat (nc) or similar tools to test port connectivity:

nc -zv <server_local_ip> 53000


	  - Check if the client can establish a connection to the server’s port.

### Conclusion

Under ideal conditions (without client isolation or firewall blocks), students on the same wireless network should be able to play the game. If there are issues, a fallback option like using a public relay server or configuring the campus firewall for specific use cases can be explored. Let me know if you’d like help setting up such workarounds!

---

SFML provides networking capabilities through its sf::TcpSocket and sf::UdpSocket classes. For simplicity and reliability, we’ll use TCP to establish a connection between two players, as it ensures message delivery and ordering.

The basic implementation will involve: 1. A server that listens for incoming connections and forwards mouse click positions to the connected client. 2. A client that connects to the server and displays the received click positions.

## Step-by-Step Implementation

1. Server Code

The server will:
• Accept a connection from a client.
• Wait for the client’s mouse click positions.
• Print the received positions and send them back to the client.

```cpp
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
```

2. Client Code

The client will:
• Connect to the server on the specified IP address and port.
• Send the mouse click positions to the server.
• Display the click positions received from the server.

```cpp
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Player Screen");
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
```

### How It Works

1.	Server:
  - Listens for a client connection on port 53000.
  - Receives mouse click positions from the client.
  - Echoes the received positions back to the client.
2.	Client:
  - Connects to the server on 127.0.0.1 (localhost).
  - Sends mouse click positions to the server when the user clicks in the window.
  - Displays the positions received from the server.

### Running the Program

1.	Start the server program first.
2.	Run the client program, ensuring it connects to the server’s IP address.
3.	Click in the client window:
    - The server will print the received position.
    - The client will display the click position sent back from the server.

### Next Steps

- Improve Robustness: Add error handling for dropped connections or invalid packets.
- Expand to Multiplayer: Modify the server to handle multiple clients.
- Integrate Game Logic: Extend this setup to handle game-specific events, like dice rolls or player moves in Knucklebones.

Let me know if you’d like help extending this example or integrating it into your project!
