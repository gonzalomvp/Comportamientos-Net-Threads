#pragma once

#include "logic_entity.h"

class CLogicEntityTurtle : public CLogicEntity {
public:
	CLogicEntityTurtle(CGameServer* gameServer, int posX, int posY, unsigned int id) : CLogicEntity(gameServer, ETurtle, posX, posY, id) {}
	virtual void update();
};
