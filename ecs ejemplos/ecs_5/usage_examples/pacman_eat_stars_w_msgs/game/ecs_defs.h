// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
#include "../components/all_components_fwd.h"
#define _CMPS_LIST_ \
	Transform, \
	Image, \
	StarMotion, \
	Points

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	STARS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
#include "../systems/all_systems_fwd.h"
#define _SYS_LIST_ \
    CollisionsSystem, \
    GameCtrlSystem, \
    PacManSystem, \
    RenderSystem, \
    StarsSystem

