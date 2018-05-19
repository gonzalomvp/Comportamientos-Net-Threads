#pragma once

#include "view_entity.h"

class CViewEntityTurtle : public CViewEntity {
public:
	CViewEntityTurtle(int posX, int posY, unsigned int id) : CViewEntity(posX, posY, id) {}
	virtual void update();
};