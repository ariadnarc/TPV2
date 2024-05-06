// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "../game/network_messages.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	// getters
	Uint8 client_id() {	return clientID_;}
	bool master() { return clientID_ == masterID_;}

	// sendings
	void sendState(const Vector2D &pos, float w, float h, float rot);
	void sendInfo(const Vector2D& pos, const Vector2D& vel, float s, float a, float rot, Uint8 state);
	void sendBullet();
	void sendRestart();
	void sendDead(Uint8 id);
	void sendWait();
	void sendSync(Uint8 id, const Vector2D& pos);

private:
	
	// --- handlers

	// clients
	void handClient(Uint8 id);
	void handDisconnect(Uint8 id);

	// mensajes
	void handDead(const PlayerDeadMsg& m);
	void handSync(PlayerInfoMsg& m);
	void handInfo(const PlayerInfoMsg &m);
	void handShoot(const ShootMsg &m);

	// flujo
	void handRestart();
	void handWait();


	UDPsocket sock_;
	SDLNet_SocketSet socketSet_;
	UDPpacket *p_;
	IPaddress srvadd_;

	Uint8 clientID_;
	Uint8 masterID_;
};

