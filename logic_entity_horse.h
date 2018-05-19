#pragma once

#include "logic_entity.h"

class CLogicEntityHorse : public CLogicEntity {
public:
	CLogicEntityHorse(CGameServer* gameServer, int posX, int posY, unsigned int id) : CLogicEntity(gameServer, EHorse, posX, posY, id) {}
	virtual void update();

	//Threads
	virtual void manageMessage(const CMessage& msg);
	virtual void manageReadMessage(const CMessage& msg);
};
