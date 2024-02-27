#pragma once
#include "../ecs/ecs.h"

//No hacemos .cpp para este porque los otros facades no tienen xd

//clase base para los black holes
class BlackHoleFacade
{
public:
	BlackHoleFacade(){}
	virtual ~BlackHoleFacade(){}
	
	virtual void create_blackholes(int n) = 0;
	virtual void remove_all_blackholes() = 0;
};

