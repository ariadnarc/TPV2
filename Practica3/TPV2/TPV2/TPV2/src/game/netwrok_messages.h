// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"

enum MsgType : Uint8 
{
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECT,
	_CONNECT, //
	_PLAYER_STATE, //
	_PLAYER_INFO, //
	_SHOOT, //
	_RESTART, //
	_DEAD, //
	_WAIT, //
	_SYNC //
};

struct Msg 
{
	Uint8 type;

	_IMPL_SERIALIAZION_(type)
};

struct MsgWithId: Msg 
{
	Uint8 id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,id)
};

struct MsgWithMasterId: MsgWithId 
{
	Uint8 masterID;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,masterID)
};

struct PlayerStateMsg: MsgWithId 
{
	float x;
	float y;
	int w;
	int h;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,w,h,rot)
};

struct PlayerInfoMsg: MsgWithId 
{
	float x;
	float y;
	float speedX;
	float speedY;
	float speed;
	float acceleration;
	float rot;
	Uint8 state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,speedX,speedY,speed,acceleration,rot,state)
};

struct ShootMsg: MsgWithId 
{
	float x;
	float y;
	float vx;
	float vy;
	int w;
	int h;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,vx,vy,w,h,rot)
};

struct PlayerDeadMsg : MsgWithId 
{
	int id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, id)
};
