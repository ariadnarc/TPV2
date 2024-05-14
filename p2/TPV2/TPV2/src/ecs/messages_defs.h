// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"

using msgId_t = uint8_t;
enum msgId : msgId_t {
	_m_NEW_GAME,
	_m_ROUND_START,
	_m_ROUND_OVER,
	_m_GAME_OVER,
	_m_PACMAN_FOOD_COLLISION,
	_m_PACMAN_GHOST_COLLISION,
	_m_KILL_PACMAN,
	_m_IMMUNITY_START,
	_m_IMMUNITY_END
};


struct Message {
	msgId_t id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_NEW_GAME
		struct
		{

		} new_game_data;

		//
		struct {
			ecs::entity_t e;
		} kill_pacman_data;

		// _m_PACMAN_FOOD_COLLISION
		struct
		{
			bool isMilagrosa;
			ecs::entity_t fruitToDelete;
		} fruit_collision_data;

		//	_m_PACMAN_GHOST_COLLISION
		struct
		{
			ecs::entity_t ghostToDelete;
			bool blue;
		} ghost_collision_data;

	};
};
