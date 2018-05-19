#pragma once

#include "view_entity.h"

class CViewEntityHorse : public CViewEntity {
public :
	CViewEntityHorse(int posX, int posY, unsigned int id) : CViewEntity(posX, posY, id) {}
	virtual void update();
};