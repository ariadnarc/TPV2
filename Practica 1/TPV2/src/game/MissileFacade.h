#pragma once
class MissileFacade
{
public:
	MissileFacade() = default;
	virtual ~MissileFacade() = default;
	virtual void create_missiles(int n) = 0;
	virtual void remove_missiles() = 0;
};

