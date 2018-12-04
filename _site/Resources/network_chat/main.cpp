#include <iostream>
#include <SFML/Network.hpp>

const unsigned short PORT = 5000;
const std::string IPADDRESS("localhost");//change to suit your needs

std::string msgSend;

sf::TcpSocket socket;
sf::Mutex globalMutex;
bool quit = false;

void DoStuff(void)
{
	static std::string oldMsg;
	while(!quit)
	{
		sf::Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		globalMutex.unlock();
		
		socket.send(packetSend);
		
		std::string msg;
		sf::Packet packetReceive;
		
		socket.receive(packetReceive);		
		if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
		{
			std::cout << msg << std::endl;
			oldMsg = msg;
		}
	}
}

void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

bool Client(void)
{
	if(socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}

void GetInput(void)
{
	std::string s;
	std::cout << "\nEnter \"exit\" to quit or message to send: ";
	getline(std::cin,s);
	if(s == "exit")
		quit = true;
	globalMutex.lock();
	msgSend = s;
	globalMutex.unlock();
}


int main(int argc, char* argv[])
{
	sf::Thread* thread = 0;
		
	char who;
	std::cout << "Do you want to be a server (s) or a client (c) ? ";
	std::cin  >> who;

	if (who == 's')
		Server();
	else
		Client();

	thread = new sf::Thread(&DoStuff);
	thread->launch();
		
	while(!quit)
	{
		GetInput();
	}

	if(thread)
	{
		thread->wait();
		delete thread;
	}
	return 0;
}