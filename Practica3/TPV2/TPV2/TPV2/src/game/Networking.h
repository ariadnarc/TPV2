// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "../game/netwrok_messages.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {	return clientID_;}

	bool master() { return clientID_ == masterID_;}

	void send_state(const Vector2D &pos, float w, float h, float rot);
	void send_my_info(const Vector2D& pos, const Vector2D& vel, float s, float a, float rot, Uint8 state);
	
	void send_bullet();
	void send_dead(Uint8 id);
	void send_restart();
	void send_wait();

	void send_sync(Uint8 id, const Vector2D& pos);


private:

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_info(const PlayerInfoMsg &m);
	void handle_shoot(const ShootMsg &m);
	void handle_dead(const PlayerDeadMsg& m);
	void handle_restart();
	void handle_wait();
	void handle_sync(PlayerInfoMsg& m);

	UDPsocket sock_;
	SDLNet_SocketSet socketSet_;
	UDPpacket *p_;
	IPaddress srvadd_;
	Uint8 clientID_;
	Uint8 masterID_;
};

