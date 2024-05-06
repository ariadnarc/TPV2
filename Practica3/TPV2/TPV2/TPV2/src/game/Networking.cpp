// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>

#include "Game.h"
#include "network_messages.h"
#include "../sdlutils/SDLNetUtils.h"
#include "LittleWolf.h"
#include "../utils/Vector2D.h"

Networking::Networking() :
		sock_(), //
		socketSet_(), //
		p_(), //
		srvadd_(), //
		clientID_(), //
		masterID_() {
}

Networking::~Networking() {
}

bool Networking::init(char *host, Uint16 port) {

	if (SDLNet_ResolveHost(&srvadd_, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sock_ = SDLNet_UDP_Open(0);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet_, sock_);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0.type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0.type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(p_->data);
					clientID_ = m1.id;
					masterID_ = m1.masterID;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int) clientID_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m.type = _DISCONNECT;
	m.id = clientID_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	PlayerDeadMsg m3;
	ShootMsg m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) 
	{
		switch (m0.type) 
		{
		case _CONNECT:
			m1.deserialize(p_->data);
			masterID_ = m1.masterID;
			handClient(m1.id);
			break;

		case _DISCONNECT:
			m1.deserialize(p_->data);
			masterID_ = m1.masterID;
			handDisconnect(m1.id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(p_->data);
			break;

		case _DEAD:
			m3.deserialize(p_->data);			//!!!!!!!!!!
			handDead(m3);
			break;

		case _SHOOT:
			m4.deserialize(p_->data);			//!!!!!!!!!!
			handShoot(m4);

			break;
		case _PLAYER_INFO:
			m5.deserialize(p_->data);
			handInfo(m5);
			break;

		case _RESTART:
			handRestart();
			break;

		case _SYNC:
			m5.deserialize(p_->data);
			handSync(m5);
			break;

		case _WAIT:
			handWait();
			break;

		default:
			break;
		}
	}
}

#pragma region sendings

void Networking::sendState(const Vector2D &pos, float w, float h, float rot) 
{
	PlayerStateMsg m;

	m.type = _PLAYER_STATE;
	m.id = clientID_;
	m.x = pos.getX();
	m.y = pos.getY();
	m.w = w;
	m.h = h;
	m.rot = rot;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::sendBullet() 
{
	ShootMsg m;

	m.type = _SHOOT;
	m.id = clientID_;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::sendDead(Uint8 id) 
{
	PlayerDeadMsg msg;

	msg.type = _DEAD;
	msg.id = clientID_;
	msg.id = id;

	SDLNetUtils::serializedSend(msg, p_, sock_, srvadd_);
}

void Networking::sendInfo(const Vector2D& pos, const Vector2D& vel, float s, float a, float rot, Uint8 state) 
{
	PlayerInfoMsg msg;

	msg.type = _PLAYER_INFO;
	msg.id = clientID_;
	msg.x = pos.getX();
	msg.y = pos.getY();
	msg.speed = s;
	msg.speedX = vel.getX();
	msg.speedY = vel.getY();
	msg.acceleration = a;
	msg.rot = rot;
	msg.state = state;

	SDLNetUtils::serializedSend(msg, p_, sock_, srvadd_);
}


void Networking::sendRestart()
{
	Msg msg;

	msg.type = _RESTART;

	SDLNetUtils::serializedSend(msg, p_, sock_, srvadd_);
}

void Networking::sendWait()
{
	Msg msg;

	msg.type = _WAIT;

	SDLNetUtils::serializedSend(msg, p_, sock_, srvadd_);
}

void Networking::sendSync(Uint8 id, const Vector2D& pos)
{
	PlayerInfoMsg msg;

	msg.id = id;
	msg.x = pos.getX();
	msg.y = pos.getY();
	msg.type = _SYNC;

	SDLNetUtils::serializedSend(msg, p_, sock_, srvadd_);
}

#pragma endregion

#pragma region handlers

void Networking::handClient(Uint8 id)
{
	if (clientID_ != id)
	{
		Game::instance()->getLW().send_info();
	}
}

void Networking::handDisconnect(Uint8 id)
{
	Game::instance()->getLW().removePlayer(id);
}
void Networking::handDead(const PlayerDeadMsg& msg)
{
	if (clientID_ != msg.id)
	{
		Game::instance()->getLW().setDead(msg.id);
	}
}

void Networking::handSync(PlayerInfoMsg& msg)
{
	Game::instance()->getLW().playerSync(msg.id, Vector2D(msg.x, msg.y));
}

void Networking::handInfo(const PlayerInfoMsg& msg) 
{
	if (clientID_ != msg.id) 
	{
		Game::instance()->getLW().update_player(msg.id, msg.x,
				msg.y, msg.speedX, msg.speedY, msg.speed, msg.acceleration, msg.rot, (LittleWolf::PlayerState)msg.state);
	}
}

void Networking::handShoot(const ShootMsg& msg)
{
	if (master())
	{
		Game::instance()->getLW().playerShoot(msg.id);
	}
}

// FLUJO 

void Networking::handRestart()
{
	Game::instance()->getLW().bringAllToLife();
}

void Networking::handWait()
{
	Game::instance()->getLW().waiting();
}

#pragma endregion



