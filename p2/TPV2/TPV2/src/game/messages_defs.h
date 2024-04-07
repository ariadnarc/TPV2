// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

/*
 *
 * DO NOT USE/MODIFY THIS FILE, IT IS JUST AN EXAMPLE OF HOW YOUR
 * game/messages_defs.h SHOULD LOOK LIKE
 *
 */


#include <cstdint>
#include "../ecs/ecs.h"

using msgId_t = uint8_t;
enum msgId : msgId_t {
	_m_NEW_GAME, _m_ROUND_START, _m_ROUND_OVER, _m_GAME_OVER,
	m_PACMAN_FOOD_COLLISION, _m_PACMAN_GHOST_COLLISION,
	_m_IMMUNITY_START, _m_IMMUNITY_END
};


struct Message {
	msgId_t id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_FRUIT_EATEN
		struct {
			ecs::Entity* e;
		} fruit_eaten_data;

		// _m_CREATE_FRUITS
		struct {
			unsigned int n;
		} create_fruit_data;

	};
};
