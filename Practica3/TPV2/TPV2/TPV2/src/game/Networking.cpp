// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>

#include "Game.h"
#include "netwrok_messages.h"
#include "../sdlutils/SDLNetUtils.h"
#include "LittleWolf.h"
#include "../utils/Vector2D.h"

Networking::Networking() :
		sock_(), //
		socketSet_(), //
		p_(), //
		srvadd_(), //
		clientId_(), //
		masterId_() {
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
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(p_->data);
					clientId_ = m1._client_id;
					masterId_ = m1._master_id;
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
	std::cout << "Connected with id " << (int) clientId_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = clientId_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	PlayerDeadMsg m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(p_->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			m5.deserialize(p_->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			m3.deserialize(p_->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			m4.deserialize(p_->data);
			handle_dead(m4);
			break;

		case _RESTART:
			handle_restart();
			break;

		case _SYNC:
			m5.deserialize(p_->data);
			handle_sync(m5);
			break;

		case _WAIT:
			handle_wait();
			break;

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != clientId_){
		Game::instance()->get_littlewolf().sendinfo();
	}
}

void Networking::handle_disconnet(Uint8 id) {
	Game::instance()->get_littlewolf().removePlayer(id);
}

void Networking::send_state(const Vector2D &pos, float w, float h, float rot) {
	PlayerStateMsg m;
	m._type = _PLAYER_STATE;
	m._client_id = clientId_;
	m.x = pos.getX();
	m.y = pos.getY();
	m.w = w;
	m.h = h;
	m.rot = rot;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {

	//if (m._client_id != clientId_) {
	//	Game::instance()->get_littlewolf().update_player_info(m._client_id, m.x,
	//			m.y, m.w, m.h, m.rot);
	//}
}

void Networking::send_bullet() 
{
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = clientId_;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_shoot(const ShootMsg &m) {
	if (is_master()) {
		Game::instance()->get_littlewolf().player_shoot(m._client_id);
	}
}

void Networking::send_dead(Uint8 id) 
{
	PlayerDeadMsg m;
	m._type = _DEAD;
	m._client_id = clientId_;
	m.id = id;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_dead(const PlayerDeadMsg &m) {
	if (m._client_id != clientId_) {
		Game::instance()->get_littlewolf().player_die(m.id);
	}
}

void Networking::send_my_info(const Vector2D& pos, const Vector2D& vel, float s, float a, float rot, Uint8 state) 
{
	PlayerInfoMsg m;
	m._type = _PLAYER_INFO;
	m._client_id = clientId_;
	m.x = pos.getX();
	m.y = pos.getY();
	m.speedX = vel.getX();
	m.speedY = vel.getY();
	m.speed = s;
	m.acceleration = a;
	m.rot = rot;
	m.state = state;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != clientId_) {
		Game::instance()->get_littlewolf().update_player(m._client_id, m.x,
				m.y, m.speedX, m.speedY, m.speed, m.acceleration, m.rot, (LittleWolf::PlayerState)m.state);
	}
}

void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_wait()
{
	Msg m;
	m._type = _WAIT;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_sync(Uint8 id, const Vector2D& pos)
{
	PlayerInfoMsg m;
	m._client_id = id;
	m.x = pos.getX();
	m.y = pos.getY();
	m._type = _SYNC;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_restart() {
	Game::instance()->get_littlewolf().bringAllToLife();

}

void Networking::handle_wait()
{
	Game::instance()->get_littlewolf().waiting();
}

void Networking::handle_sync(PlayerInfoMsg& m)
{
	Game::instance()->get_littlewolf().player_sync(m._client_id, Vector2D(m.x, m.y));
}
