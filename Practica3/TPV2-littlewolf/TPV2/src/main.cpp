// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <fstream>

#include "game/Game.h"
#include "game/UDPServer.h"

#include "sdlutils/SDLNetUtils.h"


void server(Uint16 port) {
	UDPServer s(port, 10);
	s.listen();
}

void client(const char* host, Uint16 port) {
	Game g;

	if (g.init(host, port)) {
		g.start();
	}
}

int main(int, char**) {

	try {

		SDLNetUtils::initSDLNet();

		const char* host;

		host = "localhost";
		int port = 2000;

		std::cout << "Client(c)/Server(s)" << std::endl;

		char answer;

		std::cin >> answer;

		if (answer == 's') {
			server(port);
		}
		else if (answer == 'c') {
			client(host, port);
		}
		else {
			std::cout << "Must write s/c, try again" << std::endl;
		}

	}
	catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}